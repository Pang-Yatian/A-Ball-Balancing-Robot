# A-Ball-Balancing-Robot
## Brief introduction
A ball balancing robot is a kind of dynamical stable robot, which is designed to balance on a ball by itself, while the ball can move in any direction under the control of the robot. Actuation is realized by using DC motors to drive three omnidirectional wheels rotating, making the robot body reach its equilibrium point. An inertial measurement unit is used to detect the change in attitude angles. Based on kinematic analysis, Proportional-Integral-Derivative controllers are implemented to stabilize and control the robot.


video:  https://youtu.be/On0e1YCgcag

https://www.bilibili.com/video/BV1TJ411x7tR?p=3

![image](https://github.com/Pang-Yatian/A-Ball-Balacicng-Robot/blob/master/image/ballbot.png)

## Run
The code needs Keil uvison5 IDE to open.

--->dynamical control code\USER\Minibalance.uvprojx

## Hardware composition

![image](https://github.com/Pang-Yatian/A-Ball-Balancing-Robot/blob/master/image/hardware%20composition.png)

## Hardware list

MCU:STM32F103 module

DC motor: MD36NP51 with photoelectric encoder (24V)

Motor driver: BTN7971 module

Omniwheel: diameter 100mm

Battery: 5AH 24V 5000mah

Ball: v1-v2 standard football, final version 3kg medicine ball (225mm)

IMU: MPU-6050 module

## Performance 

![image](https://github.com/Pang-Yatian/A-Ball-Balancing-Robot/blob/master/image/performance.png)
