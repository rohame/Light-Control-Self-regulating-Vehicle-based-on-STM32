#include "SpeedCtrol.h"
#include "interface.h"


//����ֱ��66mm��������̳���Ϊ20�������ܳ� 207mm = 20.7cm 
//��������жϸߵ͵�ƽ�仯����������Ҳ����˵����תһ�ܼ�������Ϊ40
//һ�������仯��ʾ�����ܹ��ľ���Ϊ 20.7/40 = 0.5175cm


unsigned int front_right_speed=0;


void MeasureInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_S_PIN;//����ʹ��GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//����GPIOģʽ,��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(FRONT_RIGHT_S_GPIO , &GPIO_InitStructure); 
}

/*******************************************************************************
* �� �� �� ��MeasureSpeed
* �������� ���ٶȲ���������IO�仯�������ú�������ÿ5ms����һ��
* ��    �� ����
* ��    �� ����
*******************************************************************************/


