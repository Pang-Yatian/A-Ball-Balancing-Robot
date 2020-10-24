#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
×÷Õß£ºPang Yatian
*
**************************************************************************/
#define PI 3.14159265
#define ZHONGZHI 0 
#define DIFFERENCE 100
extern	int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
int EXTI15_10_IRQHandler(void);
void Set_Pwm(int motor_a,int motor_b,int motor_c);
void Kinematic_Analysis(float Vx,float Vy,float Vz);
 
void Encoder_Analysis(float Vx,float Vy,float Vz);
void Key(void);
void Xianfu_Pwm(int amplitude);
void Xianfu_Velocity(int amplitude_A,int amplitude_B,int amplitude_C,int amplitude_D);
u8 Turn_Off( int voltage);
u32 myabs(long int a);
int balance_Z(float Velocity,float Gyro);
int balance_X(float Angle,float Gyro);
int balance_Y(float Angle,float Gyro);
int velocity_X(int velocity);
int velocity_Y(int velocity);
#endif
