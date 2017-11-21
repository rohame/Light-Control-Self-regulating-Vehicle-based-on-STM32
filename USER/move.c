//连接方式 ：请参考interface.h文件
//部份源码来源网络--请试用24小时后删除
#include "stm32f10x.h"
#include "interface.h"
#include "IRCtrol.h"
#include "motor.h"
#include "delay.h"

////全局变量定义
//unsigned int speed_count=0;//占空比计数器 50次一周期
//char front_left_speed_duty=SPEED_DUTY;
//char front_right_speed_duty=SPEED_DUTY;
//char behind_left_speed_duty=SPEED_DUTY;
//char behind_right_speed_duty=SPEED_DUTY;

//unsigned char tick_5ms = 0;//5ms计数器，作为主函数的基本周期
//unsigned char tick_1ms = 0;//1ms计数器，作为电机的基本计数器
//unsigned char tick_200ms = 0;//刷新显示

//char ctrl_comm = COMM_STOP;//控制指令
//char ctrl_comm_last = COMM_STOP;//上一次的指令
//unsigned char continue_time=0;

//void BarrierProc(void)
//{
//		if(VOID_L_IO == BARRIER_N && VOID_R_IO == BARRIER_Y)//右转
//	{
//		CarRight();
//		Delayms(30);
//		return;
//	}
//	else if(VOID_L_IO == BARRIER_Y && VOID_R_IO == BARRIER_N)//左转
//	{
//		CarLeft();
//		Delayms(30);
//		return;
//	}	
//	
//	if((distance_cm >= 5 && distance_cm <= 7) || distance_cm > 50) //
//	{
//		CarStop();//防震荡
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
//			continue_time--;//200ms 无接收指令就停车
//			if(continue_time == 0)
//			{
//				continue_time = 1;
//				CarStop();
//			}
			//do something
//			Distance();//计算距离
//			BarrierProc();
//			if(ctrl_comm_last != ctrl_comm)//接收到红外信号
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

