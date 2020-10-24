#include "show.h"
  /**************************************************************************
作者：Pang Yatian
*
**************************************************************************/
unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数
float Vol;
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void oled_show(void)
{
//	  //=============第1行显示3轴角度===============//	
//  	OLED_ShowString(0,0,"X:");
//		if(Angle_Zero_X<0)		OLED_ShowNumber(15,0,Angle_Zero_X+360,3,12);
//		else					          OLED_ShowNumber(15,0,Angle_Zero_X,3,12);	
//       
//  	OLED_ShowString(40,0,"Y:");
//		if(Angle_Zero_Y<0)		OLED_ShowNumber(55,0,Angle_Zero_Y+360,3,12);
//		else					          OLED_ShowNumber(55,0,Angle_Zero_Y,3,12);	

//		//=============显示电机A的状态=======================//	
//	  if( Encoder_A<0)		    OLED_ShowString(00,10,"-"),
//		                      OLED_ShowNumber(15,10,-Encoder_A,5,12);
//		else                 	OLED_ShowString(0,10,"+"),
//		                      OLED_ShowNumber(15,10, Encoder_A,5,12); 
//		
//		if( Encoder_X<0)		  OLED_ShowString(80,10,"-"),
//		                      OLED_ShowNumber(95,10,-Encoder_X,4,12);
//		else                 	OLED_ShowString(80,10,"+"),
//		                      OLED_ShowNumber(95,10, Encoder_X,4,12);
//		//=============显示电机B的状态=======================//	
//		  if( Encoder_B<0)		  OLED_ShowString(00,20,"-"),
//		                      OLED_ShowNumber(15,20,-Encoder_B,5,12);
//		else                 	OLED_ShowString(0,20,"+"),
//		                      OLED_ShowNumber(15,20, Encoder_B,5,12); 
//		  
//		if( Encoder_Y<0)		  OLED_ShowString(80,20,"-"),
//		                      OLED_ShowNumber(95,20,-Encoder_Y,4,12);
//		else                 	OLED_ShowString(80,20,"+"),
//		                      OLED_ShowNumber(95,20, Encoder_Y,4,12);
// 		//=============显示电机C的状态=======================//	
//		if( Encoder_C<0)		    OLED_ShowString(00,30,"-"),
//		                      OLED_ShowNumber(15,30,-Encoder_C,5,12);
//		else                 	OLED_ShowString(0,30,"+"),
//		                      OLED_ShowNumber(15,30, Encoder_C,5,12); 
//		  
//		if( Encoder_Z<0)		  OLED_ShowString(80,30,"-"),
//		                      OLED_ShowNumber(95,30,-Encoder_Z,4,12);
//		else                 	OLED_ShowString(80,30,"+"),
//		                      OLED_ShowNumber(95,30, Encoder_Z,4,12);	
//		//=============显示电机D的状态=======================//	
//  	OLED_ShowString(0,40,"X:");
//		if(Angle_Balance_X<0)		OLED_ShowNumber(15,40,Angle_Balance_X+360,3,12);
//		else					          OLED_ShowNumber(15,40,Angle_Balance_X,3,12);	
//       
//  	OLED_ShowString(40,40,"Y:");
//		if(Angle_Balance_Y<0)		OLED_ShowNumber(55,40,Angle_Balance_Y+360,3,12);
//		else					          OLED_ShowNumber(55,40,Angle_Balance_Y,3,12);	

//		//=============第五行显示电压=======================//
//													OLED_ShowString(00,50,"VOLTAGE");
// 
//		                      OLED_ShowString(88,50,".");
//		                      OLED_ShowString(110,50,"V");
//		                      OLED_ShowNumber(75,50,Voltage/100,2,12);
//		                      OLED_ShowNumber(98,50,Voltage%100,2,12);
//		 if(Voltage%100<10) 	OLED_ShowNumber(92,50,0,2,12);
//		//=============刷新=======================//
//		OLED_Refresh_Gram();	

	   OLED_ShowString(80,0,"Z:");
		if(Angle_Balance_Z<0)		OLED_ShowNumber(95,0,Angle_Balance_Z+360,3,12);
		else					OLED_ShowNumber(95,0,Angle_Balance_Z,3,12);		

	  //=============第1行显示3轴角度===============//	
		OLED_ShowString(0,0,"X:");
		if(Angle_Bias_X<0)		OLED_ShowNumber(15,0,Angle_Bias_X+360,3,12);
		else					      OLED_ShowNumber(15,0,Angle_Bias_X,3,12);	
       
		OLED_ShowString(40,0,"Y:");
		if(Angle_Bias_Y<0)		OLED_ShowNumber(55,0,Angle_Bias_Y+360,3,12);
		else					    OLED_ShowNumber(55,0,Angle_Bias_Y,3,12);	
	
 

		//=============显示电机A的状态=======================//	
										      OLED_ShowString(00,10,"A");
	  if( Encoder_A<0)		  OLED_ShowString(15,10,"-"),
		                      OLED_ShowNumber(25,10,-Encoder_A,4,12);
		else                 	OLED_ShowString(15,10,"+"),
		                      OLED_ShowNumber(25,10, Encoder_A,4,12); 
													OLED_ShowString(70,10,"X");
		if( Encoder_X<0)		  OLED_ShowString(85,10,"-"),
		                      OLED_ShowNumber(95,10,-Encoder_X,4,12);
		else                 	OLED_ShowString(85,10,"+"),
		                      OLED_ShowNumber(95,10, Encoder_X,4,12);
		//=============显示电机B的状态=======================//	
										      OLED_ShowString(00,20,"B");
		  if( Encoder_B<0)		OLED_ShowString(15,20,"-"),
		                      OLED_ShowNumber(25,20,-Encoder_B,4,12);
		else                 	OLED_ShowString(15,20,"+"),
		                      OLED_ShowNumber(25,20, Encoder_B,4,12);
		
													OLED_ShowString(70,20,"Y");
		if( Encoder_Y<0)		  OLED_ShowString(85,20,"-"),
		                      OLED_ShowNumber(95,20,-Encoder_Y,4,12);
		else                 	OLED_ShowString(85,20,"+"),
		                      OLED_ShowNumber(95,20, Encoder_Y,4,12);
 		//=============显示电机C的状态=======================//	
												  OLED_ShowString(00,30,"C");
		  if( Encoder_C<0)		OLED_ShowString(15,30,"-"),
		                      OLED_ShowNumber(25,30,-Encoder_C,4,12);
		else                 	OLED_ShowString(15,30,"+"),
		                      OLED_ShowNumber(25,30, Encoder_C,4,12); 
													
		                      OLED_ShowString(70,30,"Z");
		if( Encoder_Z<0)		  OLED_ShowString(85,30,"-"),
		                      OLED_ShowNumber(95,30,-Encoder_Z,4,12);
		else                 	OLED_ShowString(85,30,"+"),
		                      OLED_ShowNumber(95,30, Encoder_Z,4,12);	
		//=============显示电机D的状态=======================//
  	OLED_ShowString(0,40,"XR:");
		if(Angle_Balance_X<0)		      OLED_ShowNumber(20,40,Angle_Balance_X+360,3,12);
		else					      OLED_ShowNumber(20,40,Angle_Balance_X,3,12);	
       
  	OLED_ShowString(45,40,"YR:");
		if(Angle_Balance_Y<0)		   OLED_ShowNumber(65,40,Angle_Balance_Y+360,3,12);
		else					    OLED_ShowNumber(65,40,Angle_Balance_Y,3,12);	
		
				 if(Flag_Stop==0) OLED_ShowString(100,40,"O-N");
			   else             OLED_ShowString(100,40,"OFF");
		//=============第6行显示模式和电压=======================//
													OLED_ShowString(00,50,"VOLTAGE");
 
		                      OLED_ShowString(88,50,".");
		                      OLED_ShowString(110,50,"V");
		                      OLED_ShowNumber(75,50,Voltage/100,2,12);
		                      OLED_ShowNumber(98,50,Voltage%100,2,12);
		 if(Voltage%100<10) 	OLED_ShowNumber(92,50,0,2,12);
		//=============刷新=======================//
		OLED_Refresh_Gram();	


	}
/**************************************************************************
函数功能：向APP发送数据
入口参数：无
返回  值：无
作    者：Pang Yatian
**************************************************************************/
void APP_Show(void)
{    
	  static u8 flag;
	  int app_2,app_3,app_4;
	  app_4=(Voltage-2220)*2/3;	
	  if(app_4>100)app_4=100;   //对电压数据进行处理
	  app_2=Encoder_X*0.2;  if(app_2<0)app_2=-app_2;			                   //对编码器数据就行数据处理便于图形化
		app_3=Encoder_Y*0.2;  if(app_3<0)app_3=-app_3;
	  flag=!flag;
	 	if(PID_Send==1)//发送PID参数
	{
		printf("{C%d:%d:%d:%d:%d:%d}$",(int)Balance_Kp,(int)Balance_Kd,(int)Velocity_Kp,(int)Velocity_Ki,(int)Turn_Kp,(int)Turn_Kd);//打印到APP上面	
		PID_Send=0;	
	}	
   else	if(flag==0)// 
   printf("{A%d:%d:%d:%d}$",(u8)app_2,(u8)app_3,app_4,0); //打印到APP上面
	 else
	 printf("{B%d:%d:%d:%d}$",(int)Angle_Balance_X,(int)Angle_Balance_Y,(int)Encoder_X,(int)Encoder_Y);//打印到APP上面 显示波形
}
/**************************************************************************
函数功能：虚拟示波器往上位机发送数据 关闭显示屏
入口参数：无
返回  值：无
作    者：Pang Yatian
**************************************************************************/
void DataScope(void)
{   
		DataScope_Get_Channel_Data( Angle_Balance_X, 1 );       //显示目标值
		DataScope_Get_Channel_Data(Angle_Balance_Y, 2 );       //显示实际值，便于PID参数调节  
		DataScope_Get_Channel_Data(Position_X/50000, 3 );                
  	DataScope_Get_Channel_Data(Position_Y/50000, 4 );      
		Send_Count = DataScope_Data_Generate(4);
		for( i = 0 ; i < Send_Count; i++) 
		{
		while((USART1->SR&0X40)==0);  
		USART1->DR = DataScope_OutPut_Buffer[i]; 
		}
}
