#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import math

class SpiralMover(Node):
    def __init__(self):
        super().__init__('spiral_mover')

        self.publisher = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        self.timer_period = 0.1  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        self.angular_speed = 1.0      # rad/s (constant angular velocity)
        self.linear_speed = 3.0       # initial linear speed
        self.linear_decrease = 0.003  # reduce linear speed slowly to last longer

        self.twist = Twist()

        self.time_elapsed = 0.0       # track time elapsed
        self.total_run_time = 10 * (2 * math.pi) / self.angular_speed  # time for 10 full rotations

    def timer_callback(self):
        if self.time_elapsed >= self.total_run_time or self.linear_speed <= 0:
            self.twist.linear.x = 0.0
            self.twist.angular.z = 0.0
            self.publisher.publish(self.twist)
            self.get_logger().info('Completed ~10 spiral rounds, turtle stopped.')
            return

        self.twist.linear.x = self.linear_speed
        self.twist.angular.z = self.angular_speed
        self.publisher.publish(self.twist)

        self.linear_speed -= self.linear_decrease
        if self.linear_speed < 0:
            self.linear_speed = 0

        self.time_elapsed += self.timer_period

def main(args=None):
    rclpy.init(args=args)
    node = SpiralMover()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
