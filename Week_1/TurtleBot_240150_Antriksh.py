#1/usr/bin/env python3
import rclpy 
from rclpy.node import Node
from geometry_msgs.msg import Twist
class DrawSpiralNode(Node):

    def __init__(self):
        super().__init__("draw_spiral")
        self.cmd_vel_pub_ = self.create_publisher(Twist, "/turtle1/cmd_vel", 10)
        self.linear_speed = 0.0  # initial speed
        self.timer_ = self.create_timer(0.5, self.send_velocity_command)
        self.get_logger().info("Draw spiral node has been started")

    def send_velocity_command(self):
        msg = Twist()
        self.linear_speed += 0.1  # increment linear speed
        msg.linear.x = self.linear_speed
        msg.angular.z = 1.0       # constant angular speed
        self.cmd_vel_pub_.publish(msg)


    
def main(args=None):
    rclpy.init(args=args)
    node = DrawSpiralNode()
    rclpy.spin(node)
    rclpy.shutdown()
