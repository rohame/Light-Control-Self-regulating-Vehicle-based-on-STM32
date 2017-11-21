#ifndef __MOTOR_H_
#define __MOTOR_H_
#define PWMPeriod   10000

extern unsigned int speed_count;//ռ�ձȼ����� 50��һ����
extern int front_left_speed_duty;
extern int front_right_speed_duty;
extern int behind_left_speed_duty;
extern int behind_right_speed_duty;



void CarMove(void);
void CarGo(void);
void CarBack(void);
void CarLeft(void);
void CarRight(void);
void CarStop(void);
void MotorInit(void);
#endif

