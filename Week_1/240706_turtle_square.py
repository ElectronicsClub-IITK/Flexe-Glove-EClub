import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
import math

class TurtleSquare(Node):
    def __init__(self):
        super().__init__('turtle_square_closed_loop')
        self.publisher = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        self.subscriber = self.create_subscription(Pose, '/turtle1/pose', self.pose_callback, 10)
        self.pose = None
        self.square_corners = [
            (5.0, 5.0),
            (8.0, 5.0),
            (8.0, 8.0),
            (5.0, 8.0)
        ]
        self.goal_index = 0
        self.state = 'move'
        self.timer = self.create_timer(0.05, self.control_loop)
        self.linear_k = 1.5
        self.angular_k = 6.0
        self.tolerance = 0.05

    def pose_callback(self, msg):
        self.pose = msg

    def control_loop(self):
        if self.pose is None:
            return
        goal_x, goal_y = self.square_corners[self.goal_index]
        dx = goal_x - self.pose.x
        dy = goal_y - self.pose.y
        distance = math.hypot(dx, dy)
        angle_to_goal = math.atan2(dy, dx)
        heading_error = self.normalize_angle(angle_to_goal - self.pose.theta)

        msg = Twist()
        if abs(heading_error) > 0.05:
            msg.angular.z = self.angular_k * heading_error
            msg.linear.x = 0.0
        elif distance > self.tolerance:
            msg.linear.x = self.linear_k * distance
            msg.angular.z = self.angular_k * heading_error
        else:
            # Arrived at corner, go to next
            self.goal_index = (self.goal_index + 1) % len(self.square_corners)

        self.publisher.publish(msg)

    @staticmethod
    def normalize_angle(angle):
        while angle > math.pi:
            angle -= 2*math.pi
        while angle < -math.pi:
            angle += 2*math.pi
        return angle

def main(args=None):
    rclpy.init(args=args)
    node = TurtleSquare()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
