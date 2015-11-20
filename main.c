#include <30f5015.h>
#include "Config.h"
#include "Global_Variables.c"
#include <stdlib.h>
#include "Functions.h"

void main(void)
{	
	printf("System enabled\n\r");
	Motor_Init(PWM_PERIOD);
    enable_interrupts(INT_RDA);		
	//enable_interrupts(INT_EXT0);
	//ext_int_edge(L_TO_H);
    while(true)
	{
		Set_Motor_Duty(0,0);
		while(!input_state(PIN_F6)&&!RUN )//&& !RUN)   //While loop used for waiting an input high  in D8 to start
   		{
			output_toggle(PIN_E2);
      		delay_ms(15);
			Read_Sensors_Digital(sensors_BIN);
			Get_Average_Center_Digital(sensors_BIN,2,12,&center); 
			printf("%c\n\r",(center+65));
   		}
		output_high(PIN_E2);
		delay_ms(2000);
		if(!RUN) RUN=0xFF;
		while(RUN){
			//output_toggle(PIN_E2); 
         	Read_Sensors_Digital(sensors_BIN);
         	Get_Average_Center_Digital(sensors_BIN,2,12,&center); 
         	if(center==-1)	center=last_center;
			Print_Center(center);
		 	last_center=center;
      	 	error=SET_POINT-center;
		 	derivative=error-last_error;
			//if(derivative<-6||derivative>6) {derivative=0; error=last_error;}
		 	if(error>4 || error<-4) integral=integral+error;
			else integral=0;
			if(integral>100) integral=100;
			if(integral*(-1)>100) integral=-100;
	     	correction=error*(KP)+derivative*(KD)+integral*(KI);
		 	last_error=error;

		   	if(center>13 && center<19 && BoostCounter<24) 
			{
				BoostCounter++;
				if(BoostCounter>3) base_speed=1400; //set_motor_pwm_duty(3,3,2500);correction=0 ;//Boost=499-BaseSpeed;
			}	
		    else
			{
				BoostCounter=0; base_speed=1000;//set_motor_pwm_duty(3,3,2650);}
			}

         	left_correction=(base_speed)-correction;
     	 	right_correction=(base_speed)+correction;      
			Set_Motor_Duty(left_correction,right_correction);
	  		delay_us(delay_time);
			printf("%c\n\r",(center+65));
			//for(i=2;i<=12;i++)printf("%d",Sensors_BIN[i]);
			//printf("%c\n",(center+65));
		}
   }
}

