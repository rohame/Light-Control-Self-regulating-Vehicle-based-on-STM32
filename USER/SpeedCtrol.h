#ifndef __SPEEDCTROL_H_
#define __SPEEDCTROL_H_

#define FOSC 48000000L //�������ã�ʹ��24M Hz 6T˫�ٱ�ģʽ

//�ٶȷ���IO�ڶ���
//sbit FRONT_LEFT_S_IO =  P1^3; //��ǰǰ��IO
//sbit FRONT_RIGHT_S_IO =  P1^2; //��ǰǰ��IO

extern unsigned int front_right_speed;

void MeasureSpeed(void);

#endif
