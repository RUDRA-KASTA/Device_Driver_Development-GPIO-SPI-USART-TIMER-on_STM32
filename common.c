
#include "common.h"
#include "STM32F103C8T6_GPIO_DRIVER.h"



void PID_controller_update(float setpoint , float measurement)
{

		//error signal
		float error = setpoint - measurement;
	
	if(error != 0)
	{
		////////////////////////////////  proportional  ////////////////////////////////
		float proportional = kp * error ;
		
		////////////////////////////////  integral  ////////////////////////////////
//		PID->integrator += error ;
//		float integral = (PID->integrator) * ki;
	
		////////////////////////////////  derivative  ////////////////////////////////
		double rate = (error - preverror);
		float derivative = kd * (rate); 

		////////////////////////////////  output  ////////////////////////////////
		double control = proportional + derivative; //  + integral ;
		
		if(control > limit_control)
		{   control = limit_control;  }
		
		else if(control < (0 - limit_control))
		{ 	control = (0 - limit_control);	}
		
		speed = control;
		
		preverror = error ;
		USART_send(USART2,speed);
		return;
	}
}
	

