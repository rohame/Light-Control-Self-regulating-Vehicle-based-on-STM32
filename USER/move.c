//���ӷ�ʽ ����ο�interface.h�ļ�
//����Դ����Դ����--������24Сʱ��ɾ��
#include "stm32f10x.h"
#include "interface.h"
#include "IRCtrol.h"
#include "motor.h"
#include "delay.h"

////ȫ�ֱ�������
//unsigned int speed_count=0;//ռ�ձȼ����� 50��һ����
//char front_left_speed_duty=SPEED_DUTY;
//char front_right_speed_duty=SPEED_DUTY;
//char behind_left_speed_duty=SPEED_DUTY;
//char behind_right_speed_duty=SPEED_DUTY;

//unsigned char tick_5ms = 0;//5ms����������Ϊ�������Ļ�������
//unsigned char tick_1ms = 0;//1ms����������Ϊ����Ļ���������
//unsigned char tick_200ms = 0;//ˢ����ʾ

//char ctrl_comm = COMM_STOP;//����ָ��
//char ctrl_comm_last = COMM_STOP;//��һ�ε�ָ��
//unsigned char continue_time=0;

//void BarrierProc(void)
//{
//		if(VOID_L_IO == BARRIER_N && VOID_R_IO == BARRIER_Y)//��ת
//	{
//		CarRight();
//		Delayms(30);
//		return;
//	}
//	else if(VOID_L_IO == BARRIER_Y && VOID_R_IO == BARRIER_N)//��ת
//	{
//		CarLeft();
//		Delayms(30);
//		return;
//	}	
//	
//	if((distance_cm >= 5 && distance_cm <= 7) || distance_cm > 50) //
//	{
//		CarStop();//����
//		return;
//	}
//	
//	if(VOID_L_IO == VOID_R_IO)
//	{
//		if(distance_cm < 5) CarBack();
//		if(distance_cm > 7) CarGo();	
//	}
//}

int move(void)
{
//	delay_init();
//	GPIOCLKInit();
//	UserLEDInit();
//	IRCtrolInit();
//	TIM2_Init();
//	MotorInit();
////	UltraSoundInit();
//	RedRayInit();
//	ServoInit();

 while(1)
 {	 
//	 		if(tick_5ms >= 5)
//		{
//			tick_5ms = 0;
//			tick_200ms++;
//			if(tick_200ms >= 40)
//			{
//				tick_200ms = 0;
//				LEDToggle(LED_PIN);
//			}
//			continue_time--;//200ms �޽���ָ���ͣ��
//			if(continue_time == 0)
//			{
//				continue_time = 1;
//				CarStop();
//			}
			//do something
//			Distance();//�������
//			BarrierProc();
//			if(ctrl_comm_last != ctrl_comm)//���յ������ź�
//			{
//				ctrl_comm_last = ctrl_comm;
//				switch(ctrl_comm)
//				{
//					case COMM_UP:    CarGo();break;
//					case COMM_DOWN:  CarBack();break;
//					case COMM_LEFT:  CarLeft();break;
//					case COMM_RIGHT: CarRight();break;
//					case COMM_STOP:  CarStop();break;
//					default : break;
//				}
//				LCD1602WriteCommand(ctrl_comm);
//			}
//		}
		
 }
}

