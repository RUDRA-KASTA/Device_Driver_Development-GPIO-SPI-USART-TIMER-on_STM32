/************************************************************* NECESSARY HEADER FILES  *****************************************************/

#include "STM32F103C_TIMER_DRIVER.h"
#include "STM32F103C_USART_DRIVER.h"
#include "STM32F103C_SPI_DRIVER.h"
#include <math.h>

/////////////////////////////////////////////////////////   PID   //////////////////////////////////////////////////////////////////////////

#define target     1620     //1770
#define kp   0.01    //0.1
#define ki   0 
#define kd   0 
#define speed_limit   50
#define Encoder_count  		  (signed)(TIM2->CNT)

double preverror , rate , speed , integrator , error , proportional , integral , derivative;
int  stop;


/****************************************************** MAIN FILES FUNCTIONS ***************************************************/

void PID_controller_speed(double setpoint);
void GPIOasTIMinit(void);
void ENCODERinit(void);
void CaptureorCompare_ENABLE(void);
void USART2config_send(void);
uint8_t ENCODER_DIR_read(void);

/****************************************************** PID FUNCTIONS ***************************************************/
void PID_controller_speed(double setpoint)
{
		//error signal
	  error = setpoint - Encoder_count*(1);
		stop = 0;
	
		while(stop ==0)
		{
				////////////////////////////////  proportional  ////////////////////////////////
				proportional = kp * error ;
				
				//////////////////////////////////  integral  ////////////////////////////////
				integrator += error ;
				integral = (integrator) * ki;
			
				/////////////////////////////////  derivative  ////////////////////////////////
				rate = (error - preverror);
				derivative = kd * (rate); 

				////////////////////////////////  output  ////////////////////////////////
				speed = proportional + derivative + integral ;
				
				if(speed > speed_limit)
				{   speed = speed_limit;  }
				
				else if(speed < (0 - speed_limit))
				{ 	speed = (0 - speed_limit);	}
				
				preverror = error ;
				USART_SendData(64+speed);
				//}
		}

}

/**********************************************  CONFIGURING GPIO PIN AS USART  ************************************************/	

void USART2config_send(void)
{
		GPIO_handle_t  GPIOhandle;
	
		GPIOhandle.pGPIOx = GPIOA;
		GPIOhandle.GPIO_pinconfig.GPIO_pin_mode = OUT_MODE_SPEED_10MHZ;
		GPIOhandle.GPIO_pinconfig.GPIO_op_type = OT_AF_PP;
		GPIOhandle.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO2 ;
		GPIO_init(&GPIOhandle);
	
		USART_handle_t  USART2_handle;
	
		USART2_handle.pUSARTx = USART2;
		USART2_handle.USARTconfig.USART_MODE = USART_MODE_TX;
		USART2_handle.USARTconfig.USART_NUM_OF_STOP_BIT = USART_1_STOP_BIT;
		USART2_handle.USARTconfig.USART_PARITY_BIT = USART_PARITY_DISABLE;
		USART2_handle.USARTconfig.USART_WORD_LENGTH = USART_8_BIT_DATA;
		USART2_handle.USARTconfig.USART_BAUDRATE = USART_STD_BAUD_19200	;
		USART2_handle.USARTconfig.USART_HW_FLOW_CONTROL = USART_HW_FLOW_CONTROL_NONE;
		USART_init(&USART2_handle);
	
	
			/****************** USART peripherial control **********************/
								USART_peripherialcontrol(USART2_handle.pUSARTx,ENABLE);
			/*******************************************************************/
}

/**********************************************  CONFIGURING TIMER REGISTER ************************************************/	

void ENCODERinit(void)
{
		TIMER_periclockcontrol(TIM2,ENABLE);
	
		GPIO_handle_t  ABC  ;
		ABC.pGPIOx = GPIOA;
		ABC.GPIO_pinconfig.GPIO_pin_mode = GPIO_INPUT;
		ABC.GPIO_pinconfig.GPIO_ip_type = IT_FLOATING;
		ABC.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO0;
		GPIO_init(&ABC);
	  ABC.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO1;
		GPIO_init(&ABC);
	
		CaptureorCompare_ENABLE(); 
	
		TIMER_handle_t  TIMhandle;
		TIMhandle.pTIMx = TIM2;
		TIMhandle.TIMERconfig.ARR_VALUE = 0xFFFF;
		TIMhandle.TIMERconfig.CH1_MODE.CH1_IPOPorMAPPING = TIMER_CC1_IP_IC1onTI1;
		TIMhandle.TIMERconfig.CH2_MODE.CH2_IPOPorMAPPING = TIMER_CC2_IP_IC2onTI2;
		TIMhandle.TIMERconfig.CCER_REGISTER.CC1POLARITY = NONINVERTED ;
		TIMhandle.TIMERconfig.CCER_REGISTER.CC2POLARITY = NONINVERTED ;
	  TIMhandle.TIMERconfig.SLAVEMODESELECT = TIMER_SMS_COUNTonBOTH ;
		TIMER_init(&TIMhandle);
	
		TIMER_countercontrol(TIM2,ENABLE);
}

/***************************************************************************************************************************/	
/***************************************************  MAIN FUNCTION ********************************************************/	
/***************************************************************************************************************************/	


int main()
{
		ENCODERinit();
		USART2config_send();

		USART_SendData(64);

		while(1)
		{	
				error = target - Encoder_count;
				if((error !=0) && (Encoder_count <5000))
				{
						PID_controller_speed(target) ;
				}
				else
				{
						USART_SendData(64);
				}
		}
		
}


//int main(void)
//{
//		ENCODERinit();
//		USART2config_send();
//		while(1)
//		{
//			USART_SendData(170);
//		}
//}

