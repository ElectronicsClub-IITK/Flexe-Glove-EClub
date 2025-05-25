import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import time


class SpiralRectangle(Node):
    def __init__(self):
        super().__init__('spiral_rectangle')
        self.publisher_ = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        time.sleep(2)  # Allow time for turtlesim_node to start
        self.draw_rectangle()
        self.draw_spiral()

    def draw_rectangle(self):
        twist = Twist()

        for _ in range(4):  # 4 sides
            # Move forward
            twist.linear.x = 2.0
            twist.angular.z = 0.0
            self.publisher_.publish(twist)
            time.sleep(2)

            # Turn 90 degrees
            twist.linear.x = 0.0
            twist.angular.z = 1.5707  # ~90 degrees/sec
            self.publisher_.publish(twist)
            time.sleep(1)

        # Stop motion
        twist.linear.x = 0.0
        twist.angular.z = 0.0
        self.publisher_.publish(twist)
        time.sleep(1)

    def draw_spiral(self):
        twist = Twist()
        radius = 1.0

        # One loop = ~2π radians; 10 loops = ~62.8 radians
        total_angle = 0.0
        while total_angle < 62.8:  # 10 full loops
            twist.linear.x = radius
            twist.angular.z = 2.0 / radius
            self.publisher_.publish(twist)
            time.sleep(0.3)
            radius += 0.02
            total_angle += twist.angular.z * 0.3  # angle = ω × time

        # Stop motion
        twist.linear.x = 0.0
        twist.angular.z = 0.0
        self.publisher_.publish(twist)


def main(args=None):
    rclpy.init(args=args)
    node = SpiralRectangle()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
