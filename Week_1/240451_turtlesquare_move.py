#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import math

class SquareMover(Node):
    def __init__(self):
        super().__init__('square_mover')

        self.publisher = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        self.timer_period = 0.1  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        self.state = 'move'  # 'move' or 'turn'
        self.time_elapsed = 0.0

        self.linear_speed = 2.0       # turtle forward speed (m/s)
        self.angular_speed = 1.0      # rad/s, turtle turn speed

        self.move_time = 2.0          # time to move forward (seconds)

        # Calculate turn time needed to turn 90 degrees (pi/2 radians)
        self.turn_angle = math.pi / 2  # 90 degrees in radians
        self.turn_time = self.turn_angle / self.angular_speed

        self.side_count = 0

        self.twist = Twist()

    def timer_callback(self):
        if self.side_count >= 4:
            self.side_count = 0  # reset to keep moving square forever

        if self.state == 'move':
            self.twist.linear.x = self.linear_speed
            self.twist.angular.z = 0.0
            self.publisher.publish(self.twist)

            self.time_elapsed += self.timer_period
            if self.time_elapsed >= self.move_time:
                self.state = 'turn'
                self.time_elapsed = 0.0

        elif self.state == 'turn':
            self.twist.linear.x = 0.0
            self.twist.angular.z = self.angular_speed
            self.publisher.publish(self.twist)

            self.time_elapsed += self.timer_period
            if self.time_elapsed >= self.turn_time:
                self.state = 'move'
                self.time_elapsed = 0.0
                self.side_count += 1


def main(args=None):
    rclpy.init(args=args)
    node = SquareMover()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
