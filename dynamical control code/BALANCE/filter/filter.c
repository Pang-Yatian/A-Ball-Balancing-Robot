#include "filter.h"
#include "sys.h"
  /**************************************************************************
���ߣ�Pang Yatian
*
**************************************************************************/
float K1 =0.02; 

/**************************************************************************
�������ܣ����׿������˲�
��ڲ��������ٶȡ����ٶ�
����  ֵ����
**************************************************************************/
void Kalman_Filter_X(float Accel,float Gyro)		
{
  static float Q_angle=0.001;// ����������Э����
	static float Q_gyro=0.003;//0.003 ����������Э���� ����������Э����Ϊһ��һ�����о���
	static float R_angle=0.5;// ����������Э���� �Ȳ���ƫ��
	static float dt=0.01;//                 
	static char  C_0 = 1;
	static float Q_bias, Angle_err;
	static float PCt_0, PCt_1, E;
	static float K_0, K_1, t_0, t_1;
	static float Pdot[4] ={0,0,0,0};
	static float PP[2][2] = { { 1, 0 },{ 0, 1 } };
	Angle_Balance_X+=(Gyro - Q_bias) * dt; //�������
	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��

	Pdot[1]=-PP[1][1];
	Pdot[2]=-PP[1][1];
	Pdot[3]=Q_gyro;
	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
	PP[0][1] += Pdot[1] * dt;   // =����������Э����
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - Angle_Balance_X;	//zk-�������
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //����������Э����
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle_Balance_X	+= K_0 * Angle_err;	 //�������
	Q_bias	+= K_1 * Angle_err;	 //�������
	//angle_dot   = Gyro - Q_bias;	 //���ֵ(�������)��΢��=���ٶ�
}
/**************************************************************************
�������ܣ����׿������˲�
��ڲ��������ٶȡ����ٶ�
����  ֵ����
**************************************************************************/
void Kalman_Filter_Y(float Accel,float Gyro)		
{
  static float Q_angle=0.001;// ����������Э����
	static float Q_gyro=0.003;//0.003 ����������Э���� ����������Э����Ϊһ��һ�����о���
	static float R_angle=0.5;// ����������Э���� �Ȳ���ƫ��
	static float dt=0.01;//                 
	static char  C_0 = 1;
	static float Q_bias, Angle_err;
	static float PCt_0, PCt_1, E;
	static float K_0, K_1, t_0, t_1;
	static float Pdot[4] ={0,0,0,0};
	static float PP[2][2] = { { 1, 0 },{ 0, 1 } };
	Angle_Balance_Y+=(Gyro - Q_bias) * dt; //�������
	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��

	Pdot[1]=-PP[1][1];
	Pdot[2]=-PP[1][1];
	Pdot[3]=Q_gyro;
	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
	PP[0][1] += Pdot[1] * dt;   // =����������Э����
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - Angle_Balance_Y;	//zk-�������
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //����������Э����
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	Angle_Balance_Y	+= K_0 * Angle_err;	 //�������
	Q_bias	+= K_1 * Angle_err;	 //�������
	//angle_dot   = Gyro - Q_bias;	 //���ֵ(�������)��΢��=���ٶ�
}

///**************************************************************************
//�������ܣ�һ�׻����˲�
//��ڲ��������ٶȡ����ٶ�
//����  ֵ����
//**************************************************************************/
//void Yijielvbo_X(float angle_m, float gyro_m)
//{
//   Angle_Balance_X = K1 * angle_m+ (1-K1) * (Angle_Balance_X + gyro_m * 0.005);
//}
///**************************************************************************
//�������ܣ�һ�׻����˲�
//��ڲ��������ٶȡ����ٶ�
//����  ֵ����
//**************************************************************************/
//void Yijielvbo_Y(float angle_m, float gyro_m)
//{
//   Angle_Balance_Y = K1 * angle_m+ (1-K1) * (Angle_Balance_Y + gyro_m * 0.005);
//}