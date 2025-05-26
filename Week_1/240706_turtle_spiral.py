import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import time


class SpiralRectangle(Node):
    def __init__(self):
        super().__init__('spiral_rectangle')
        self.publisher_ = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        time.sleep(2)   
        self.draw_spiral()

    def draw_spiral(self):
        twist = Twist()
        radius = 1.0

         
        total_angle = 0.0
        while total_angle < 62.8:  
            twist.linear.x = radius
            twist.angular.z = 2.0 / radius
            self.publisher_.publish(twist)
            time.sleep(0.3)
            radius += 0.02
            total_angle += twist.angular.z * 0.3   
        
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

