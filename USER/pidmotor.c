#include "stm32f10x.h"
#include "motor.h"
#include "interface.h"
#include "stm32f10x.h"
#include "pidcontroller.h"
#include "pidmotor.h"
#include "delay.h"

void Carpid(int control)
{
	float MotorSpeed,PwmOne_Set=0;
	
	MotorSpeed = control;//��ȡPID������ֵ
											   
	if(MotorSpeed > 50)  MotorSpeed =   50-1 ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
	if(MotorSpeed <-50)  MotorSpeed = -(50-1);//���� 

	if(MotorSpeed<0) { PwmOne_Set = -MotorSpeed; }
	else { PwmOne_Set = MotorSpeed; }
//	PwmOne_Set = MotorSpeed;
	front_left_speed_duty=PwmOne_Set;
	front_right_speed_duty=PwmOne_Set;
	behind_left_speed_duty=PwmOne_Set;
	behind_right_speed_duty=PwmOne_Set;
	
}
void CarSpeed(int speed)
{
  front_left_speed_duty=speed;
	front_right_speed_duty=speed;
	behind_left_speed_duty=speed;
	behind_right_speed_duty=speed;
	delay_ms(1500);	
	User_PidSpeedControl(speed);
}








