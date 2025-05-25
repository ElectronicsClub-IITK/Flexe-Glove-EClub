import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import time

class SpiralTurtle(Node):
    def __init__(self):
        super().__init__('spiral_turtle')
        self.publisher = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        time.sleep(2.0)  # Wait for publisher setup
        self.move_in_spiral()

    def move_in_spiral(self):
        twist = Twist()
        linear_speed = 0.5
        angular_speed = 1.0
        rate = self.create_rate(10)  # 10 Hz loop

        for i in range(10000):  # Increase speed slowly to form spiral
            twist.linear.x = linear_speed
            twist.angular.z = angular_speed
            self.publisher.publish(twist)
            self.get_logger().info(f"Spiral step {i+1}: speed = {linear_speed:.2f}")
            linear_speed += 0.005  # Slowly increase linear speed
            time.sleep(0.1)

        twist.linear.x = 0.0
        twist.angular.z = 0.0
        self.publisher.publish(twist)
        self.get_logger().info("Spiral motion complete.")
        self.destroy_node()

def main(args=None):
    rclpy.init(args=args)
    spiral = SpiralTurtle()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

