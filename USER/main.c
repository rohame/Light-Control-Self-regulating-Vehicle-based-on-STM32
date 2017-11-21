#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "usmart.h" 
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"	
#include "touch.h"		
#include "usart3.h"
#include "common.h" 
#include "stm32f10x.h"
#include "interface.h"
#include "IRCtrol.h"
#include "motor.h"
#include "delay.h"
#include "SpeedCtrol.h"
#include "light.h"
#include "24cxx.h"
#include "UltrasonicCtrol.h"
#include "rundistance.h"
#include "pidcontroller.h"
#include "pidmotor.h"
//ȫ�ֱ�������
unsigned int speed_count=0;//ռ�ձȼ����� 50��һ����
int front_left_speed_duty=SPEED_DUTY;
int front_right_speed_duty=SPEED_DUTY;
int behind_left_speed_duty=SPEED_DUTY;
int behind_right_speed_duty=SPEED_DUTY;


unsigned char tick_5ms = 0;//5ms����������Ϊ�������Ļ�������
unsigned char tick_1ms = 0;//1ms����������Ϊ����Ļ���������
int mea_1ms = 0;
unsigned char tick_200ms = 0;//ˢ����ʾ

char ctrl_comm = COMM_STOP;//����ָ��
char ctrl_comm_last = COMM_STOP;//��һ�ε�ָ��
unsigned char continue_time=0;

/************************************************
 ALIENTEK STM32F103������ ��չʵ��5
 ATK-RM04 WIFIģ�����ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

void BarrierProc(void)
{
    if(distance_cm ==0)
    {
        return;
    }
    if(bh_data_read()/1.2>500)
    {
        CarStop();
        return;
    }
    if(distance_cm < 8)
    {
        CarBack();
        return;
    }
    

    
	if(VOID_L_IO == BARRIER_N && VOID_R_IO == BARRIER_Y)//��ת
	{
		CarRight();
//		Delayms(30);
		return;
	}
	else if(VOID_L_IO == BARRIER_Y && VOID_R_IO == BARRIER_N)//��ת
	{
		CarLeft();
//		Delayms(30);
		return;
	}	
    
    if(distance_cm >= 8 && distance_cm <= 13) //
	{
		CarStop();//����
		return;
	}
    
	if(distance_cm > 13)
	{
        CarGo();
	}
    
    return;
}

void send_data(void)
{   		  
 	u8 *p; 	
	
	float datalx=0;
  char show_datalx[60];
  char show_distance[20];
	char show_speed[20];	
	unsigned int speed_send;
	  speed_send=front_right_speed*0.75/2;
	sprintf(show_distance,"%d",distance_cm);

	    datalx =bh_data_read()/1.2;
      sprintf(show_datalx,"%g",datalx);
      strcat(show_datalx,"lx ");
      strcat(show_datalx,show_distance);
      strcat(show_datalx,"cm ");
	     sprintf(show_speed,"%d",speed_send);
      strcat(show_datalx,show_speed);
      strcat(show_datalx,"cm/s");
      strcat(show_datalx,"             ");
		     p=show_datalx;
						atk_8266_send_cmd("AT+CIPSEND=25","OK",200);  //����ָ�����ȵ�����
						delay_ms(200);
						atk_8266_send_data(p,"OK",100);  //����ָ�����ȵ�����
}
void send_mode(void)
{   		  
 	u8 *p; 	

  char show_datalx[60];

	  sprintf(show_datalx,"%s","ѡ��mode dis speed stop     ");
	    printf("%s","����");
	     p=show_datalx;
						atk_8266_send_cmd("AT+CIPSEND=25","OK",200);  //����ָ�����ȵ�����
						delay_ms(200);
						atk_8266_send_data(p,"OK",100);  //����ָ�����ȵ�����
	    printf("%s","����wifi");
}

 int main(void)
 {	 
	  u8 key,fontok=0; 	 
	 	u8 *q;
	  u8 *s;
	  u16 rlen=0;
	 
	 long int dis=0;
	 int spd=0;

	   

	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	usmart_dev.init(72);		//��ʼ��USMART		
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   		//��ʼ��LCD   
	W25QXX_Init();				//��ʼ��W25Q128
	tp_dev.init();				//��ʼ��������
	usart3_init(115200);		//��ʼ������3 
 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
 	f_mount(fs[0],"0:",1); 		//����SD�� 
 	f_mount(fs[1],"1:",1); 		//����FLASH.
	GPIOCLKInit();
	UserLEDInit();
	IRCtrolInit();
	TIM2_Init();
	MotorInit();
	UltraSoundInit();
	RedRayInit();
	ServoInit();
	IIC_Init();
	LED_Init();
	
		
	key=KEY_Scan(0);  
	if(0)//ǿ��У׼
	{
		LCD_Clear(WHITE);		//����0
		TP_Adjust();  			//��ĻУ׼ 
		TP_Save_Adjdata();	  
		LCD_Clear(WHITE);		//����
	}
	fontok=font_init();			//����ֿ��Ƿ�OK
	if(0)	//��Ҫ�����ֿ�				 
	{
		LCD_Clear(WHITE);		//����
 		POINT_COLOR=RED;		//��������Ϊ��ɫ	   	   	  
		LCD_ShowString(60,50,200,16,16,"ALIENTEK STM32");
		while(SD_Init())		//���SD��
		{
			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(60,70,200+60,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(60,70,200,16,16,"SD Card OK");
		LCD_ShowString(60,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,"0:");//��SD������
		while(0)//����ʧ��		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����	       
	}  
    
	atk_8266_test();		//����ATK_ESP8266����	
    	bh_data_send(BHPowOn);    //??????
	    bh_data_send(BHReset);    //???????
	    bh_data_send(BHModeH2);   //????????2
		  delay_ms(180); 
	
	while(1)
	{ 	 
		send_mode();
		
	   if(USART3_RX_STA&0X8000)		//���յ�һ��������
    	{ 
		    rlen=USART3_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
		     USART3_RX_BUF[rlen]=0;		//��ӽ����� 
						if(atk_8266_check_cmd("mymode"))
						{
						 while(1)  
						{
							GetDistanceDelay();
						  printf("%s","jvli ");
							BarrierProc();
             	printf("%s","bizhang ");					
							if(atk_8266_check_cmd("mystop"))
							{
								   CarStop();
									 break;
							}
							printf("%d",front_right_speed);	
							 send_data(); 	
						}
						  printf("%s","����mode");
						  USART3_RX_STA=0;			
					  }
				if(atk_8266_check_cmd("myspeed"))
					{
							s=atk_8266_check_cmd("myspeed");
							s=s+7;
							spd=atoi(s);	
							printf("%d",spd);
							CarSpeed(spd);
						printf("%s","pidhou ");
						  send_data();
                        
						  USART3_RX_STA=0;	
					}	 
				if(atk_8266_check_cmd("mydis"))
					{	
							q=atk_8266_check_cmd("mydis");
							q=q+5;
							dis=atoi(q)*2;
                            printf("%d",atoi(q));
							printf("%d",dis);
							Rundistance(dis);
							dis=0;		
							USART3_RX_STA=0;	
					}
                    
                //��ת
                    if(atk_8266_check_cmd("left"))
                    {
                        CarRight();
                        front_run_temp=0;
                        while(1)
                        {        
                        if(front_run_temp>=30)
                        {   
                            CarStop();
                            front_run_temp=0;	
                            break;
                        }	
                        }
                    }
                    
                    //��ת
                    if(atk_8266_check_cmd("right"))
                    {
                        CarLeft();
                        front_run_temp=0;
                        while(1)
                        {        
                        if(front_run_temp>=30)
                        {   
                            CarStop();
                            front_run_temp=0;	
                            break;
                        }	
                        }
                    }
                    
                    //����
                    if(atk_8266_check_cmd("back"))
                    {
                        CarBack();
                        front_run_temp=0;
                        while(1)
                        {        
                        if(front_run_temp>=30)
                        {   
                            CarStop();
                            front_run_temp=0;	
                            break;
                        }	
                        }
                    }
			}  
  }

}


















