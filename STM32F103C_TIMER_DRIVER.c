

#include "STM32F103C_TIMER_DRIVER.h"


/************************************************************************************************************************************/
/***************************************  TIMER PERIPHERIAL CLOCK ENABLE AND DISABLE  ***********************************************/
/************************************************************************************************************************************/





void TIMER_periclockcontrol(TIM_TypeDef *pTIMx , uint8_t enordi)
{
		if(enordi == ENABLE)
		{
				if(pTIMx == TIM1)
				{
						TIMER1_PCLK_EN();
				}
				else if (pTIMx == TIM2)
				{
						TIMER2_PCLK_EN();
				}
				else if (pTIMx == TIM3)
				{
						TIMER3_PCLK_EN();
				}
				else if (pTIMx == TIM4)
				{
						TIMER4_PCLK_EN();
				}
				
		}
		else
		{
				if(pTIMx == TIM1)
				{
						TIMER1_PCLK_DI();
				}
				else if (pTIMx == TIM2)
				{
						TIMER2_PCLK_DI();
				}
				else if (pTIMx == TIM3)
				{
						TIMER3_PCLK_DI();
				}
				else if (pTIMx == TIM4)
				{
						TIMER4_PCLK_DI();
				}
		}
}




	
/*************************************************************************************************************************/
/******************************************  USART STATUS FLAG FUNCTION DEFINATION  **************************************/
/*************************************************************************************************************************/
	
	



uint8_t TIMER_getflagstatus(TIM_TypeDef *pTIMx , uint16_t flagname)
{
			if((pTIMx->SR) & (flagname))
			{
					return FLAG_SET;
			}
					return FLAG_RESET ;
}




/*************************************************************************************************************************/
/***********************************************  TIMER DELAY FUNCTION  **************************************************/
/*************************************************************************************************************************/




	
void delay(TIM_TypeDef *pTIMa , uint32_t sec)
{
	
     TIMER_handle_t  timer; 
	
		 timer.pTIMx = pTIMa ;
		 timer.TIMERconfig.PRESCALAR = (36000-1) ;
	   timer.TIMERconfig.ARR_VALUE = (2*sec-1);
	   TIMER_delay_init(&timer);
	 
			TIMER_countercontrol(pTIMa,ENABLE);
	 
	  	while(TIMER_getflagstatus(pTIMa,TIMER_UIF_FLAG) == RESET)
				{}
					pTIMa->SR = 0 ;
	 
			TIMER_countercontrol(pTIMa,DISABLE);
		 // TIMER_periclockcontrol(pTIMa , DISABLE);
					
 }
	
 
 
 
 	
/*************************************************************************************************************************/
/************************************************  TIMER PWM FUNCTION  ***************************************************/
/*************************************************************************************************************************/
	
 
 
 

void PWM_CH1(TIM_TypeDef *pTIMa ,uint16_t fre , uint16_t DC)
{
		TIMER_handle_t  PWM;
	
		PWM.pTIMx = pTIMa;
	
		PWM.TIMERconfig.CCER_REGISTER.CC1EN = ENABLE;
		PWM.TIMERconfig.CH1_MODE.CH1_IPOPorMAPPING = CC_OP ;
		PWM.TIMERconfig.CH1_MODE.CH1_OP_MODE = PWM_MODE_1;
		PWM.TIMERconfig.PRESCALAR = (72-1);
		PWM.TIMERconfig.ARR_VALUE = ((1000000)/(fre));
		PWM.TIMERconfig.CCRx_REG.CCregister1 = ((PWM.TIMERconfig.ARR_VALUE*DC)/100);
		PWM.TIMERconfig.BDTR_MO = ENABLE;
		
		TIMER_init(&PWM);
	
		TIMER_countercontrol(pTIMa,ENABLE);
}
	

	
void PWM_CH3(TIM_TypeDef *pTIMa ,uint16_t fre , uint16_t DC )
{
		TIMER_handle_t  PWM;
	
		PWM.pTIMx = pTIMa;
	
		PWM.TIMERconfig.CCER_REGISTER.CC3EN = ENABLE;
		PWM.TIMERconfig.CH3_MODE.CH3_IPOPorMAPPING = CC_OP ;
		PWM.TIMERconfig.CH3_MODE.CH3_OP_MODE = PWM_MODE_1;
		PWM.TIMERconfig.PRESCALAR = (72-1);
		PWM.TIMERconfig.ARR_VALUE = ((1000000)/(fre));
		PWM.TIMERconfig.CCRx_REG.CCregister3 = ((PWM.TIMERconfig.ARR_VALUE*DC)/100);
		PWM.TIMERconfig.BDTR_MO = ENABLE;
	
		TIMER_init(&PWM);
	
		TIMER_countercontrol(pTIMa,ENABLE);
}
	






/*************************************************************************************************************************/
/********************************************  TIMER COUNTER CONTROL FUNCTION  *******************************************/
/*************************************************************************************************************************/
	







void TIMER_countercontrol(TIM_TypeDef *pTIMx , uint8_t enordi)
{
			if(enordi == ENABLE)
			{
					pTIMx->CR1 |= (1<<0);
			}
			else
			{
					pTIMx->CR1 &=~(1<<0);
			}
}







/*************************************************************************************************************************/
/*************************************************  TIMER INIT FUNCTION  ************************************************/
/*************************************************************************************************************************/






void TIMER_delay_init(TIMER_handle_t *pTIMERhandle)
{
	
				pTIMERhandle->pTIMx->ARR &=~(0xFFFF);
				pTIMERhandle->pTIMx->PSC &=~(0xFFFF);
	
			/********************** TIMER peripherial clock enable *************************/
								 TIMER_periclockcontrol(pTIMERhandle->pTIMx,ENABLE);
			/*******************************************************************************/
	
			
			/************************ for prescalar ***********************/
			pTIMERhandle->pTIMx->PSC = (pTIMERhandle->TIMERconfig.PRESCALAR);
	
			/************************** for AREF **************************/
			pTIMERhandle->pTIMx->ARR = (pTIMERhandle->TIMERconfig.ARR_VALUE);

}











void TIMER_init(TIMER_handle_t *pTIMERhandle)
{

			/********************** TIMER peripherial clock enable *************************/
								 TIMER_periclockcontrol(pTIMERhandle->pTIMx,ENABLE);
			/*******************************************************************************/
	
			pTIMERhandle->pTIMx->CR1 &=~(0xFFFF);
			pTIMERhandle->pTIMx->CR1 &=~(0xFFFF);
			pTIMERhandle->pTIMx->CCMR1 &=~(0xFFFF);
			pTIMERhandle->pTIMx->CCMR2 &=~(0xFFFF);
			pTIMERhandle->pTIMx->CCER &=~(0xFFFF);
			pTIMERhandle->pTIMx->SMCR &=~(0xFFFF); 
			pTIMERhandle->pTIMx->EGR &=~(0xFFFF); 
			pTIMERhandle->pTIMx->SMCR &=~(0xFFFF); 
			pTIMERhandle->pTIMx->CCR1 &=~(0xFFFF);
			pTIMERhandle->pTIMx->CCR3 &=~(0xFFFF);
			pTIMERhandle->pTIMx->ARR &=~(0xFFFF);
			pTIMERhandle->pTIMx->PSC &=~(0xFFFF);
	
	
			TIM1->CCER |=(1<<2);
	
			/*************************  for CR1 register  ***************************/
			pTIMERhandle->pTIMx->CR1 |= (pTIMERhandle->TIMERconfig.CR1_REG.ARPE << 7);
			pTIMERhandle->pTIMx->CR1 |= (pTIMERhandle->TIMERconfig.CMS);
			
	
			/***************************  for CCMR1 register  *************************************/
			pTIMERhandle->pTIMx->CCMR1 |= (pTIMERhandle->TIMERconfig.CH1_MODE.CH1_IPOPorMAPPING<<0);
			pTIMERhandle->pTIMx->CCMR1 |= (pTIMERhandle->TIMERconfig.CH2_MODE.CH2_IPOPorMAPPING<<8);
				
			pTIMERhandle->pTIMx->CCMR1 |= (pTIMERhandle->TIMERconfig.CH1_MODE.CH1_OP_MODE << 4);
			pTIMERhandle->pTIMx->CCMR1 |= (pTIMERhandle->TIMERconfig.CH1_MODE.CH1_OP_PRELOADEN << 3);
			
	
			pTIMERhandle->pTIMx->CCMR2 |= (pTIMERhandle->TIMERconfig.CH3_MODE.CH3_IPOPorMAPPING << 0);
			pTIMERhandle->pTIMx->CCMR2 |= (pTIMERhandle->TIMERconfig.CH3_MODE.CH3_OP_MODE << 4);
			

			/***************************  for CC polarity register  *******************************/
			pTIMERhandle->pTIMx->CCER |= (pTIMERhandle->TIMERconfig.CCER_REGISTER.CC1POLARITY << 1);
			pTIMERhandle->pTIMx->CCER |= (pTIMERhandle->TIMERconfig.CCER_REGISTER.CC2POLARITY << 5);
			pTIMERhandle->pTIMx->CCER |= (pTIMERhandle->TIMERconfig.CCER_REGISTER.CC1EN << 0);
			pTIMERhandle->pTIMx->CCER |= (pTIMERhandle->TIMERconfig.CCER_REGISTER.CC3EN << 8);
				
			/******************  for slave mode select register  *******************/
			pTIMERhandle->pTIMx->SMCR |= (pTIMERhandle->TIMERconfig.SLAVEMODESELECT);
			
			/********************* for EGR register *****************/
			pTIMERhandle->pTIMx->EGR |= (pTIMERhandle->TIMERconfig.EGR << 0);
			
			/******************************  for CCR1 register  ************************/
			pTIMERhandle->pTIMx->CCR1 = (pTIMERhandle->TIMERconfig.CCRx_REG.CCregister1);
			pTIMERhandle->pTIMx->CCR3 = (pTIMERhandle->TIMERconfig.CCRx_REG.CCregister3);
			
			/************************ for prescalar ***********************/
			pTIMERhandle->pTIMx->PSC = (pTIMERhandle->TIMERconfig.PRESCALAR);
	
			/************************** for AREF **************************/
			pTIMERhandle->pTIMx->ARR = (pTIMERhandle->TIMERconfig.ARR_VALUE);
			
			/**************************** for BDTR *******************************/
			pTIMERhandle->pTIMx->BDTR  = (pTIMERhandle->TIMERconfig.BDTR_MO << 15);
			
}


void CaptureorCompare_ENABLE(void)
{
		TIM2->CCER |= ((1<<0) | (1<<4));
}

/********************************************  ENCODER DIRECTION READ FUNCTION ************************************************/	

uint8_t ENCODER_DIR_read(void)
{
	uint8_t val;
	
	val =	(uint8_t)((TIM4->CR1 >> 4) & 0x00000001);
  
	return val;
}
