#include "sys.h"
  /**************************************************************************
作者：Pang Yatian
*
**************************************************************************/ 
u8 Flag_Stop=1,Flag_Show,Flag_Zero;      //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_A,Encoder_B,Encoder_C;          //编码器的脉冲计数
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Turn_Left,Turn_Right;                  
long int Motor_A,Motor_B,Motor_C;        //电机PWM变量
long int Target_A,Target_B,Target_C;     //电机目标值
float Encoder_X,Encoder_Y,Encoder_Z,Position_X,Position_Y;;
int Voltage;                             //电池电压采样相关的变量                       
u8 delay_50,delay_flag,sudu=1;                          //延时相关变量
u8 Turn_Flag,PID_Send;  //CAN和串口控制相关变量
float Angle_Balance_X,Angle_Balance_Y,Angle_Balance_Z,Gyro_Balance_X,Gyro_Balance_Z,Gyro_Balance_Y,Move_X,Move_Y,Move_Z;   //三轴角度和XYZ轴目标速度
float	Balance_Kp=255,Balance_Kd=120,Balance_Kp1=265,Balance_Kd1=120,Velocity_Kp=78,Velocity_Ki=50,Velocity_Kp1=123,Velocity_Ki1=60,Turn_Kp=25,Turn_Kd=87;  //控制PID参数 151 88
int Angle_Zero_X, Angle_Zero_Y,Angle_Bias_X, Angle_Bias_Y;
int main(void)
{ 
	Stm32_Clock_Init(9);            //=====系统时钟设置
	delay_init(72);                 //=====延时初始化
	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
	LED_Init();                     //=====初始化与 LED 连接的硬件接口
	KEY_Init();                     //=====按键初始化
	OLED_Init();                    //=====OLED初始化
	uart_init(72,128000);           //=====串口1初始化
	uart2_init(36,9600);            //=====串口2初始化
 // uart3_init(36,115200);          //=====串口3初始化 
	Encoder_Init_TIM2();            //=====编码器接口
	Encoder_Init_TIM3();            //=====编码器接口
	Encoder_Init_TIM4();            //=====初始化编码器C
	Encoder_Init_TIM5();            //=====初始化编码器D
	Adc_Init();                     //=====adc初始化
	IIC_Init();                     //=====IIC初始化
  MPU6050_initialize();           //=====MPU6050初始化	
  DMP_Init();                     //=====初始化DMP     
	MiniBalance_PWM_Init(7199,0);   //=====初始化PWM 10KHZ，用于驱动电机
  EXTI_Init();                    //=====MPU6050 5ms定时中断初始化
	while(1)
		{		
	    if(Flag_Show==0)           //使用MiniBalance APP和OLED显示屏
			{
				APP_Show();	              
				oled_show();             //===显示屏打开
	    }
    	else                       //使用MiniBalance上位机 上位机使用的时候需要严格的时序，故此时关闭app监控部分和OLED显示屏
  		{
				DataScope();              //开启MiniBalance上位机
			}
			delay_flag=1;	
			delay_50=0;
			while(delay_flag);	       //通过MPU6050的INT中断实现的50ms精准延时				
		} 
}
