#include "interface.h"
#include "motor.h"
#include "rundistance.h"
#include "common.h" 
#include "UltrasonicCtrol.h"

unsigned char front_run_count=0;

long int front_run_temp=0;

static unsigned char front_run_io=0;



void  Rundistance(long int dis)
{  


	 float disf=dis;
	
	while(dis)
	{	
    CarGo();			
		GetDistanceDelay();
	if(distance_cm!=0&&distance_cm < 8)
    {
        CarStop();
        break;
    }
	if(front_run_temp>=(disf/0.75))
	{   
	   CarStop();
     front_run_temp=0;
  	 disf=0;
		break;
	}
//	if(atk_8266_check_cmd("mystop"))
//		{
//		 CarStop();
//		 break;
//		}
//	   send_data();	
  }
	
}
	


