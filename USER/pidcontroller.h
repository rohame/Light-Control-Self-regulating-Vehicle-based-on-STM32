#ifndef __PIDCONTROLLER_H
#define __PIDCONTROLLER_H

#include "stm32f10x.h"
typedef enum {Speed = 0, Position = !Speed} PidControlMode;//ѡ���ٶ�ģʽ��λ��ģʽ

/*����ʽPID�㷨���ӿڲ����ṹ����*/
typedef struct 
{
 /*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
 float kp;     //����ϵ��
 float ki;     //����ϵ��
 float kd;     //΢��ϵ��
 float errILim;//����������
 
 float errNow;//��ǰ�����
 float ctrOut;//���������
 
 /*PID�㷨�ڲ���������ֵ�����޸�*/
 float errOld;
 float errP;
 float errI;
 float errD;
 
}PID_AbsoluteType;

extern int speedmode;

/*����ʽPID�㷨���ӿڲ����ṹ����*/
typedef struct 
{
 /*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
 float kp;     //����ϵ��
 float ki;     //����ϵ��
 float kd;     //΢��ϵ��
 
 float errNow; //��ǰ�����
 float dCtrOut;//�����������
 float  ctrOut;//�������
 
 /*PID�㷨�ڲ���������ֵ�����޸�*/
 float errOld1;
 float errOld2;
 
}PID_IncrementType;


extern void User_PidSpeedControl(s32 SpeedTag);

//extern void User_PidPositionControl(s32 Position,s32 SpeedTag);

#endif

