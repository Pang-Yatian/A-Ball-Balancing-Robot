#include "control.h"	
#include "filter.h"	
  /**************************************************************************
作者：Pang Yatian
*
**************************************************************************/

u8 Flag_Target,Flag_Target2,Flag_Change;                             //相关标志位
u8 temp1;                                               //临时变量
float Voltage_Count,Voltage_All; 											 //电压采样相关变量
int Balance_Pwm_X,Velocity_Pwm_X,Balance_Pwm_Y,Velocity_Pwm_Y,Balance_Pwm_Z;
#define X_PARAMETER          (0.5f)               
#define Y_PARAMETER           (sqrt(3)/2.f)      
#define L_PARAMETER            (1.0f)    
/**************************************************************************
函数功能：小车运动数学模型
入口参数：X Y Z 三轴速度或者位置
返回  值：无
**************************************************************************/
void Kinematic_Analysis(float Vx,float Vy,float Vz)
{
	      Target_A   = -Vx + L_PARAMETER*Vz;
        Target_B   = X_PARAMETER*Vx - Y_PARAMETER*Vy + L_PARAMETER*Vz;
	      Target_C   = X_PARAMETER*Vx + Y_PARAMETER*Vy + L_PARAMETER*Vz;
}
/**************************************************************************
函数功能：小车运动 正运动学分析 注：实际注释掉的是理想的运动学分析，实际使用放大了3倍，对计算结果没影响，主要是避免舍去误差
入口参数：A B C三个电机的速度
返回  值：无
**************************************************************************/
void Encoder_Analysis(float Va,float Vb,float Vc)
{
		Encoder_X=Va*2-Vb-Vc;
		Encoder_Y=(Vc-Vb)*sqrt(3);
		Encoder_Z=Va+Vb+Vc;
}
/**************************************************************************
函数功能：所有的控制代码都在这里面
         5ms定时中断由MPU6050的INT引脚触发
         严格保证采样和数据处理的时间同步				 
**************************************************************************/
int EXTI15_10_IRQHandler(void) 
{    
	 if(INT==0)		
	{     
		  EXTI->PR=1<<15;                                                      //清除LINE5上的中断标志位  	        		
		  if(delay_flag==1)
			 {
				 if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //给主函数提供50ms的精准延时
			 }             
       Flag_Target2=!Flag_Target2;  //角度采集分频标志位
			 if(Flag_Target2==1)
			 {
			 	Read_DMP();  //采集角度
				Key();//扫描按键变化	
		    if(Flag_Show==0)Led_Flash(100);  //===LED闪烁;常规模式 1s改变一次指示灯的状态	
				else Led_Flash(0); //上位机模式常亮
				Voltage_All+=Get_battery_volt();   //多次采样累积采集电池电压
			  if(++Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//求平均值 获取电池电压	 
         return 0;				 
			 }
			Encoder_A=-Read_Encoder(2);  //===读取编码器的值 为了保证M法测速的时间基准，首先读取编码器数据
			Encoder_B=-Read_Encoder(3);  //===读取编码器的值  
			Encoder_C=-Read_Encoder(4);  //===读取编码器的值+=Encoder_A/20;
				
			Angle_Bias_X =Angle_Balance_X-Angle_Zero_X;		//获取Y方向的偏差
		  Angle_Bias_Y =Angle_Balance_Y-Angle_Zero_Y;		//获取Y方向的偏差
			Encoder_Analysis(Encoder_A,Encoder_B,Encoder_C);//对编码器的数据进行正运动学分析
			  Position_X+=Encoder_X;
			  Position_Y+=Encoder_Y;
	  	Read_DMP();   //读取角度 
			Balance_Pwm_X= balance_X(Angle_Bias_X,Gyro_Balance_X);//X方向的倾角控制
			Balance_Pwm_Y= balance_Y(Angle_Bias_Y,Gyro_Balance_Y);	//Y方向的倾角控制
			Balance_Pwm_Z= -balance_Z(Encoder_Z,Gyro_Balance_Z);		//Z方向倾角控制
       if(++Flag_Target==4)			//速度控制分频标志位 
			  {
				Velocity_Pwm_X=velocity_X(Encoder_X);  //X方向的速度控制  
				Velocity_Pwm_Y=velocity_Y(Encoder_Y);  //Y方向的速度控制
					Flag_Target=0;				 
			  }
			  Move_X =Balance_Pwm_X+Velocity_Pwm_X;   //===X方向控制量累加					
			  Move_Y =Balance_Pwm_Y+Velocity_Pwm_Y;   //===Y方向控制量累加					
			  Move_Z=Balance_Pwm_Z;				 //===Z方向控制量累加	
 				Kinematic_Analysis(Move_X,Move_Y,Move_Z);//逆运动学分析，得到A B C电机控制量
			  Xianfu_Pwm(3000);//===PWM频率限幅
				Motor_A=Target_A;//直接调节PWM占空比 
				Motor_B=Target_B;//直接调节PWM占空比
				Motor_C=Target_C;//直接调节PWM占空比
		    if(Turn_Off(Voltage)==0)  //===如果电池电压不存在异常
				Set_Pwm(Motor_A,Motor_B,Motor_C);    //赋值给PWM寄存器	
					 if(Flag_Zero)  // //这是人为更新零点值
				 {
						 Angle_Zero_Y=Angle_Balance_Y;//Y方向角度更新
						 Angle_Zero_X=Angle_Balance_X;//X方向角度更新
						 Flag_Zero=0;//清零过程仅执行一次 等待下一次指令
				 }		 				 
 }
	 return 0;			
} 
/**************************************************************************
函数功能：Z轴控制
入口参数：Z轴速度、Z轴角速度
返回  值：Z轴控制控制PWM
作    者：Pang Yatian
**************************************************************************/
int balance_Z(float Velocity,float Gyro)
{  
   float Bias,Target;   //偏差和目标值
	 static float Target_Velocity=600;//遥控的速度
	 int balance,turn_kd;
	 if(Turn_Left==1)Target=Target_Velocity/sudu,turn_kd=0;   //控制自转
	 else if(Turn_Right==1)Target=-Target_Velocity/sudu,turn_kd=0;
	 else Target=0,turn_kd=Turn_Kd;
	 Bias=Velocity-Target;        //===求出平衡的角度中值 和机械相关
	 balance=Turn_Kp*Bias/10+Gyro*turn_kd/100;   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数  
	 return balance;
}
/**************************************************************************
函数功能：直立PD控制Y
入口参数：角度、角速度
返回  值：直立控制PWM
作    者：Pang Yatian
**************************************************************************/
int balance_Y(float Angle,float Gyro)
{  
   float Bias;
	 int balance;
	 Bias=Angle;        //===求出平衡的角度中值 和机械相关
	 balance=Balance_Kp1*Bias+Gyro*Balance_Kd1/100;   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	 return balance;
}
/**************************************************************************
函数功能：直立PD控制
入口参数：角度、角速度
返回  值：直立控制PWM
作    者：Pang Yatian
**************************************************************************/
int balance_X(float Angle,float Gyro)
{  
   float Bias;
	 int balance;
	 Bias=Angle;        //===求出平衡的角度中值 和机械相关
	 balance=Balance_Kp*Bias+Gyro*Balance_Kd/100;   //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	 return balance;
}

/**************************************************************************
函数功能：速度PI控制 修改前进后退速度，请修Target_Velocity
入口参数：左轮速度、右轮速度
返回  值：速度控制PWM
作    者：Pang Yatian
**************************************************************************/
int velocity_X(int velocity)
{  
    static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Target_Velocity=1200;//遥控的速度
	  static float Encoder_Integral;  //积分变量
			if(1==Flag_Left)    	Movement=Target_Velocity/sudu;	           //===前进标志位置1 
		else if(1==Flag_Right)	Movement=-Target_Velocity/sudu;           //===后退标志位置1
  	else  Movement=0;
//   //=============速度PI控制器=======================//	
		Encoder_Least=velocity;          //速度采集  
		Encoder *= 0.7;		                                                //===一阶低通滤波器       
		Encoder += Encoder_Least*0.3;	                                    //===一阶低通滤波器    
		Encoder_Integral +=Encoder;                                       //===积分出位移 
		Encoder_Integral +=Movement;                                      //===接收遥控器数据，控制前进后退
		if(Encoder_Integral>550000)  	Encoder_Integral=550000;             //===积分限幅
		if(Encoder_Integral<-550000)	Encoder_Integral=-550000;              //===积分限幅	
	  Velocity=Encoder*Velocity_Kp/100+Encoder_Integral*Velocity_Ki/5000;        //===速度控制	
  	if(Flag_Stop)   Encoder_Integral=0,Encoder=0;      //===电机关闭后清除积分
	  return Velocity;
}
/**************************************************************************
函数功能：速度PI控制 修改前进后退速度，请修Target_Velocity
入口参数：左轮速度、右轮速度
返回  值：速度控制PWM
作    者：Pang Yatian
**************************************************************************/
int velocity_Y(int velocity)
{  
    static float Velocity,Encoder_Least,Encoder,Movement;
	  static float Target_Velocity=1200;
	  static float Encoder_Integral;  
		if(1==Flag_Qian)    	Movement=-Target_Velocity/sudu;	         //===前进标志位置1 
		else if(1==Flag_Hou)	Movement=Target_Velocity/sudu;           //===后退标志位置1
  	else  Movement=0;
//   //=============速度PI控制器=======================//	
		Encoder_Least=velocity;          //速度采集 
		Encoder *= 0.7;		                                                //===一阶低通滤波器       
		Encoder += Encoder_Least*0.3;	                                    //===一阶低通滤波器    
		Encoder_Integral +=Encoder;                                       //===积分出位移 
		Encoder_Integral +=Movement;                                      //===接收遥控器数据，控制运动
		if(Encoder_Integral>550000)  	Encoder_Integral=550000;            //===积分限幅
		if(Encoder_Integral<-550000)	Encoder_Integral=-550000;           //===积分限幅	
	  Velocity=Encoder*Velocity_Kp1/100+Encoder_Integral*Velocity_Ki1/5000;  //===速度控制	
  	if(Flag_Stop)   Encoder_Integral=0,Encoder=0;      //===电机关闭后清除积分
	  return Velocity;
}


/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int motor_a,int motor_b,int motor_c)
{
	    int siqua=350, siqub=350, siquc=350;
    	if(motor_a>0)			PWMA=motor_a+siqua, INA=0;
			else  	            PWMA=7200+motor_a-siqua,INA=1;
		
		  if(motor_b>0)			PWMB=7200-motor_b-siqub,INB=1;
			else 	            PWMB=-motor_b+siqub,INB=0;
	
	    if(motor_c>0)			PWMC=motor_c+siquc,INC=0;
			else 	            PWMC=7200+motor_c-siquc,INC=1;
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：幅值
返回  值：无
**************************************************************************/
void Xianfu_Pwm(int amplitude)
{	
    if(Target_A<-amplitude) Target_A=-amplitude;	//限幅
		if(Target_A>amplitude)  Target_A=amplitude;	
	  if(Target_B<-amplitude) Target_B=-amplitude;	
		if(Target_B>amplitude)  Target_B=amplitude;		
	  if(Target_C<-amplitude) Target_C=-amplitude;	
		if(Target_C>amplitude)  Target_C=amplitude;		
}
/**************************************************************************
函数功能：位置PID控制过程中速度的设置
入口参数：无、幅值
返回  值：无
**************************************************************************/
void Xianfu_Velocity(int amplitude_A,int amplitude_B,int amplitude_C,int amplitude_D)
{	
    if(Motor_A<-amplitude_A) Motor_A=-amplitude_A;	//位置控制模式中，A电机的运行速度
		if(Motor_A>amplitude_A)  Motor_A=amplitude_A;	  //位置控制模式中，A电机的运行速度
	  if(Motor_B<-amplitude_B) Motor_B=-amplitude_B;	//位置控制模式中，B电机的运行速度
		if(Motor_B>amplitude_B)  Motor_B=amplitude_B;		//位置控制模式中，B电机的运行速度
	  if(Motor_C<-amplitude_C) Motor_C=-amplitude_C;	//位置控制模式中，C电机的运行速度
		if(Motor_C>amplitude_C)  Motor_C=amplitude_C;		//位置控制模式中，C电机的运行速度
}
/**************************************************************************
函数功能：按键修改小车运行状态 
入口参数：无
返回  值：无
**************************************************************************/
void Key(void)
{	
	u8 tmp,tmp2;
	tmp=click_N_Double(75);    //读取按键信息
  tmp2=Long_Press();
	if(tmp==1)Flag_Stop=!Flag_Stop;//单击开机/关闭电机   
	if(tmp==2)Flag_Zero=!Flag_Zero;//双击读取零点 

	if(tmp2==1)Flag_Show=!Flag_Show;//长按切换显示模式 	               
}

/**************************************************************************
函数功能：异常关闭电机
入口参数：电压
返回  值：1：异常  0：正常
**************************************************************************/
u8 Turn_Off( int voltage)
{
	    u8 temp;
			if(voltage<2220||Flag_Stop||Angle_Balance_X<-40||Angle_Balance_X>40||Angle_Balance_Y<-40||Angle_Balance_Y>40)//电池电压过低关闭电机
			{	                                                
      temp=1;      
      PWMA=0;
      PWMB=0;
      PWMC=0;
      INA=0;
      INB=0;
      INC=0;			
      Flag_Stop=1;				
      }
			else
      temp=0;
      return temp;			
}

/**************************************************************************
函数功能：绝对值函数
入口参数：long int
返回  值：unsigned int
**************************************************************************/
u32 myabs(long int a)
{ 		   
	  u32 temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

