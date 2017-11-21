/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "interface.h"
#include "IRCtrol.h"
#include "pidcontroller.h"
#include "motor.h"
#include "rundistance.h"
#include "SpeedCtrol.h"

static unsigned char front_right_io=0;
unsigned char front_right_speed_temp=0;
 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
void EXTI15_10_IRQHandler()	 //中断服务函数，函数定义在启动文件里
{
//	if(EXTI_GetITStatus(IRIN_EXITLINE) != RESET)	//红外中断
//	{
//		EXTI_ClearITPendingBit(IRIN_EXITLINE);//清除中断标志
//		IRIntIsr();
//	}
	
	if(EXTI_GetITStatus(IRIN_EXITLINE) != RESET)	//超声波中断
	{
		EXTI_ClearITPendingBit(IRIN_EXITLINE);//清除中断标志
	}
}

/**-------------------------------------------------------
  * @函数名 TIM5_IRQHandler
  * @功能   TIM5中断处理函数，每0.1ms中断一次 
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/
void TIM2_IRQHandler(void)
{
    /* www.armjishu.com ARM技术论坛 */

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        tick_1ms++;		
        if(FRONT_RIGHT_S_IO != front_right_io)//发生电平变化
	      {
		       front_right_speed_temp++;
              front_run_temp++;
		       front_right_io = FRONT_RIGHT_S_IO;
	      }
				if(tick_1ms >= 10)
				{
					tick_1ms = 0;
					 mea_1ms++;
					speed_count++;
					tick_5ms++;
					if(speed_count >= 50)
					{
						speed_count = 0;
					}
					CarMove();
				}
				
				if(mea_1ms>=500)
				{	
					mea_1ms=0;					
					front_right_speed = front_right_speed_temp*4;//获取1s经过的孔数	       
		      front_right_speed_temp = 0;
				}
    }
}


//void TIM6_IRQHandler(void)			//每5ms一次
//{
//	if(speedmode==1)
//	{
//  MeasureSpeed();
//  User_PidSpeedControl(150);//PID速度环控制（脉冲每周期）
//  TIM_ClearITPendingBit(TIM6,TIM_FLAG_Update);
//	}
//}


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
