#include "UltrasonicCtrol.h"
#include "interface.h"
#include "stm32f10x.h"
#include "text.h"

volatile unsigned char status = 0;//����ǰ״̬��0,���� 1 ���ʹ����źţ�2 �ȴ��źŷ���,3 
unsigned int dis_count = 0;//������ʱ
volatile unsigned int distance_cm = 0;//��ǰ����
unsigned char t2_full_count = 0;//������������������
static unsigned int ultick_5ms = 0;//5ms������

void Time4Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);//72M / 72 = 1us
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
}

//�ⲿ�ж����� ������,����û�õ��жϼ�����ʽ
void UltraSoundInit(void)	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef 	EXTI_InitStructure;//����һ���ⲿ�ж���صĽṹ��
	NVIC_InitTypeDef NVIC_InitStructure; //����һ���жϵĽṹ��
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = Echo_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(Echo_GPIO , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Trig_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(Trig_GPIO , &GPIO_InitStructure);

	GPIO_EXTILineConfig(Echo_PORTSOURCE , Echo_PINSOURCE);//��GPIO�����ó��ⲿ�ж� 
	EXTI_InitStructure.EXTI_Line = Echo_EXITLINE;//����Ӧ��GPIO�����ӵ��ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�ж��¼����ͣ��½���
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//ѡ��ģʽ���ж���
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;//ʹ�ܸ��ж�
	EXTI_Init(&EXTI_InitStructure);//�����úõĲ���д��Ĵ���
			
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	 //�׼�Ϊ0������Ƕ��
	NVIC_InitStructure.NVIC_IRQChannel = 	Echo_IRQCH;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//�����ȼ�0�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	//�����ȼ������
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ�ܸ�ģ���ж�
	NVIC_Init(&NVIC_InitStructure);	//�жϳ�ʼ�������ṹ�嶨�������ִ��
	
	Time4Init();
	Trig_RESET;
}

void Distance(void)
{
	ultick_5ms++;
	if(ultick_5ms >= 15)
	{
		ultick_5ms = 0;
		GetDistanceDelay();
	}
}

//��ʱ�ķ�ʽ��ȡ����ֵ
void GetDistanceDelay(void)
{
//   char show_dis[50];
		//���ʹ����ź�
		Trig_SET;
		status = 1;
	TIM_SetCounter(TIM5, 0);
	TIM_Cmd(TIM5, ENABLE);//�򿪶�ʱ��
		while(TIM_GetCounter(TIM5) < 11);//��ʱ����10us
		status = 2;
		Trig_RESET;
		TIM_SetCounter(TIM5, 0);
	
		while(Echo == 0)//�ȴ������ź���ʼλ��
		{
			if(TIM_GetCounter(TIM5) > 60000)//��Ӧʱ�䳬��������Χ 
			{
				status = 0;
				distance_cm = 0;//ʧ�ܺ�ͺ���
				TIM_Cmd(TIM5, DISABLE);//�رն�ʱ��
				return;//����ʧ��
			}
		}
		TIM_SetCounter(TIM5, 0);
		while(Echo == 1)//��ʼ���㳤��
		{
			int count = TIM_GetCounter(TIM5);
			if(count > 60000)//��Ӧʱ�䳬��������Χ 
			{
				status = 0;
				distance_cm = 0;//ʧ�ܺ�ͺ���
				TIM_Cmd(TIM5, DISABLE);//�رն�ʱ��
				return;//����ʧ��
			}
		}
		dis_count = TIM_GetCounter(TIM5);
		TIM_Cmd(TIM5, DISABLE);//�رն�ʱ��
		distance_cm = (unsigned int)(((long)(dis_count) * 34)/2000);//����340m/s
//        sprintf(show_dis,"%d",dis_count);
//        Show_Str(30,50,200,12,show_dis,12,0);
		status = 0;//׼���´η���		
}



