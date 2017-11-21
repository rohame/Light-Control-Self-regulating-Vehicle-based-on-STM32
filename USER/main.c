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
//全局变量定义
unsigned int speed_count=0;//占空比计数器 50次一周期
int front_left_speed_duty=SPEED_DUTY;
int front_right_speed_duty=SPEED_DUTY;
int behind_left_speed_duty=SPEED_DUTY;
int behind_right_speed_duty=SPEED_DUTY;


unsigned char tick_5ms = 0;//5ms计数器，作为主函数的基本周期
unsigned char tick_1ms = 0;//1ms计数器，作为电机的基本计数器
int mea_1ms = 0;
unsigned char tick_200ms = 0;//刷新显示

char ctrl_comm = COMM_STOP;//控制指令
char ctrl_comm_last = COMM_STOP;//上一次的指令
unsigned char continue_time=0;

/************************************************
 ALIENTEK STM32F103开发板 扩展实验5
 ATK-RM04 WIFI模块测试实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
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
    

    
	if(VOID_L_IO == BARRIER_N && VOID_R_IO == BARRIER_Y)//右转
	{
		CarRight();
//		Delayms(30);
		return;
	}
	else if(VOID_L_IO == BARRIER_Y && VOID_R_IO == BARRIER_N)//左转
	{
		CarLeft();
//		Delayms(30);
		return;
	}	
    
    if(distance_cm >= 8 && distance_cm <= 13) //
	{
		CarStop();//防震荡
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
						atk_8266_send_cmd("AT+CIPSEND=25","OK",200);  //发送指定长度的数据
						delay_ms(200);
						atk_8266_send_data(p,"OK",100);  //发送指定长度的数据
}
void send_mode(void)
{   		  
 	u8 *p; 	

  char show_datalx[60];

	  sprintf(show_datalx,"%s","选择：mode dis speed stop     ");
	    printf("%s","发完");
	     p=show_datalx;
						atk_8266_send_cmd("AT+CIPSEND=25","OK",200);  //发送指定长度的数据
						delay_ms(200);
						atk_8266_send_data(p,"OK",100);  //发送指定长度的数据
	    printf("%s","发完wifi");
}

 int main(void)
 {	 
	  u8 key,fontok=0; 	 
	 	u8 *q;
	  u8 *s;
	  u16 rlen=0;
	 
	 long int dis=0;
	 int spd=0;

	   

	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	usmart_dev.init(72);		//初始化USMART		
 	LED_Init();		  			//初始化与LED连接的硬件接口
	LCD_Init();			   		//初始化LCD   
	W25QXX_Init();				//初始化W25Q128
	tp_dev.init();				//初始化触摸屏
	usart3_init(115200);		//初始化串口3 
 	my_mem_init(SRAMIN);		//初始化内部内存池
	exfuns_init();				//为fatfs相关变量申请内存  
 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
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
	if(0)//强制校准
	{
		LCD_Clear(WHITE);		//清屏0
		TP_Adjust();  			//屏幕校准 
		TP_Save_Adjdata();	  
		LCD_Clear(WHITE);		//清屏
	}
	fontok=font_init();			//检查字库是否OK
	if(0)	//需要更新字库				 
	{
		LCD_Clear(WHITE);		//清屏
 		POINT_COLOR=RED;		//设置字体为红色	   	   	  
		LCD_ShowString(60,50,200,16,16,"ALIENTEK STM32");
		while(SD_Init())		//检测SD卡
		{
			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(60,70,200+60,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(60,70,200,16,16,"SD Card OK");
		LCD_ShowString(60,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,"0:");//从SD卡更新
		while(0)//更新失败		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(WHITE);//清屏	       
	}  
    
	atk_8266_test();		//进入ATK_ESP8266测试	
    	bh_data_send(BHPowOn);    //??????
	    bh_data_send(BHReset);    //???????
	    bh_data_send(BHModeH2);   //????????2
		  delay_ms(180); 
	
	while(1)
	{ 	 
		send_mode();
		
	   if(USART3_RX_STA&0X8000)		//接收到一次数据了
    	{ 
		    rlen=USART3_RX_STA&0X7FFF;	//得到本次接收到的数据长度
		     USART3_RX_BUF[rlen]=0;		//添加结束符 
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
						  printf("%s","做完mode");
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
                    
                //左转
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
                    
                    //右转
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
                    
                    //后退
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


















