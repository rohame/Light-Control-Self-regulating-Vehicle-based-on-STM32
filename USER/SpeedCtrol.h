#ifndef __SPEEDCTROL_H_
#define __SPEEDCTROL_H_

#define FOSC 48000000L //晶振设置，使用24M Hz 6T双速倍模式

//速度反馈IO口定义
//sbit FRONT_LEFT_S_IO =  P1^3; //左前前进IO
//sbit FRONT_RIGHT_S_IO =  P1^2; //右前前进IO

extern unsigned int front_right_speed;

void MeasureSpeed(void);

#endif
