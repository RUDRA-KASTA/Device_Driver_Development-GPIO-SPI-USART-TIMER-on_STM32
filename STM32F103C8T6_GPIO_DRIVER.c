/*
   GPIO HEADER FILE
*/

#include "STM32F103C8T6_GPIO_DRIVER.h"


/********************************************************************************************************************************************/
/***********************************************  GPIO	PERIPHERIAL CLOCK ENABLE AND DISABLE  ***********************************************/
/********************************************************************************************************************************************/



void GPIO_periclockcontrol(GPIO_TypeDef *pGPIOx, uint8_t enordi)
{
	if(enordi == ENABLE)
	{
			if(pGPIOx == GPIOA)
			{
					GPIOA_PCLK_EN();
			}
			else if(pGPIOx == GPIOB)
			{
					GPIOB_PCLK_EN();
			 }
			else if(pGPIOx == GPIOC)
			{
					GPIOC_PCLK_EN();
			}
			else if(pGPIOx == GPIOD)
			{
					GPIOD_PCLK_EN();	
			}
			else if(pGPIOx == GPIOE)
			{
					GPIOE_PCLK_EN();
			}
			else if(pGPIOx == GPIOF)
			{
					GPIOF_PCLK_EN();
			}
			else if(pGPIOx == GPIOG)
			{
					GPIOG_PCLK_EN();
			}
	}
	else
	{
		  if(pGPIOx == GPIOA)
			{
					GPIOA_PCLK_DI();
			}
			else if(pGPIOx == GPIOB)
			{
					GPIOB_PCLK_DI();
			}
			else if(pGPIOx == GPIOC)
			{
					GPIOC_PCLK_DI();
			}
			else if(pGPIOx == GPIOD)
			{
					GPIOD_PCLK_DI();
			}
			else if(pGPIOx == GPIOE)
			{
					GPIOE_PCLK_DI();
			}
			else if(pGPIOx == GPIOF)
			{
					GPIOF_PCLK_DI();
			}
			else if(pGPIOx == GPIOG)
			{
					GPIOG_PCLK_DI();
			}
	}

}



/*******************************************************************************************************************************************/
/*******************************************************  GPIO INT AND DEINT FUNCTIONS  ****************************************************/
/*******************************************************************************************************************************************/



void GPIO_init(GPIO_handle_t *pGPIOhandle)
{
	
				/**************** GPIO CLOCK ENABLE **************************/
						GPIO_periclockcontrol(pGPIOhandle->pGPIOx,ENABLE);
				/*************************************************************/
					
				uint32_t CRLorCRH , pin_no , mode , ip_type , op_type , var =0;
			
	
				pin_no = pGPIOhandle->GPIO_pinconfig.GPIO_pin_number % 8;
				mode = pGPIOhandle->GPIO_pinconfig.GPIO_pin_mode ;
				ip_type = pGPIOhandle->GPIO_pinconfig.GPIO_ip_type ;
				op_type = pGPIOhandle->GPIO_pinconfig.GPIO_op_type ;
			
				CRLorCRH = (pGPIOhandle->GPIO_pinconfig.GPIO_pin_number)/(8);
			
			if(mode <= 3)
			{
					if(CRLorCRH == CRL_R)
					{
							/*************************** clearing the bits *****************************/
												 pGPIOhandle->pGPIOx->CRL &= ~(0x0F<<(pin_no*4));
							/***************************************************************************/
					
								if(mode == GPIO_INPUT)
								{
										var |= (mode << (pin_no*4));
										var |= (ip_type << ((pin_no*4)+2));
								}
								else
								{
										var |= (mode << (pin_no*4));
										var |= (op_type << ((pin_no*4)+2));
								}
							
								/****************** programing the CRL registor *******************/
																pGPIOhandle->pGPIOx->CRL |= var ;
								/******************************************************************/    
								
					}
					else
					{		
							/*************************** clearing the bits *****************************/
												 pGPIOhandle->pGPIOx->CRH &= ~(0x0F<<(pin_no*4));
							/***************************************************************************/
						
								if(mode == GPIO_INPUT)
								{
										var |= (mode << (pin_no*4));
										var |= (ip_type << ((pin_no*4)+2));
								}
								else
								{
										var |= (mode << (pin_no*4));
										var |= (op_type << ((pin_no*4)+2));
								}
				
								/****************** programing the CRH registor *******************/
																pGPIOhandle->pGPIOx->CRH |= var ;
								/******************************************************************/
						}
			}
}



/************************************************************************************************************************************/
/****************************************************  GPIO EXTI INT  FUNCTIONS  ****************************************************/
/************************************************************************************************************************************/



void GPIO_interrupt_init(GPIO_handle_t *pGPIOhandle)
{
	
			/*******************  CLOCK ENABLE **************************/
						GPIO_periclockcontrol(pGPIOhandle->pGPIOx,ENABLE);
						AFIO_EN();
			/************************************************************/
				
					uint32_t pin_no , mode , ip_type , op_type , port_no ;
				
				
					pin_no = pGPIOhandle->GPIO_pinconfig.GPIO_pin_number ;
					mode = pGPIOhandle->GPIO_pinconfig.GPIO_pin_mode ;
					ip_type = pGPIOhandle->GPIO_pinconfig.GPIO_ip_type ;
					op_type = pGPIOhandle->GPIO_pinconfig.GPIO_op_type ;
//					port_no = pGPIOhandle->GPIO_pinconfig.GPIO_port_no ;
	
/*********************************************** rising and falling edge detection *******************************************************/	
	
	
					if(mode == GPIO_IT_MODE_FT)
					{
							EXTI->FTSR |= (1 << pin_no);
							EXTI->RTSR &= ~(1 << pin_no);
					}
					else if(mode == GPIO_IT_MODE_RT)
					{
							EXTI->RTSR |= (1 << pin_no);
							EXTI->FTSR &= ~(1 << pin_no);
					}
					else if(mode == GPIO_IT_MODE_FRT)
					{
							EXTI->RTSR |= (1 << pin_no);
							EXTI->FTSR |= (1 << pin_no);
					}
	
					
/********************************************************* configuring the GPIO port **************************************************/					
					
			
					uint32_t  exti_reg = (pin_no / 4) ;
					uint32_t  temp = (pin_no % 4) ;
					
					AFIO->EXTICR[exti_reg] |= ( port_no << (4*temp));			
					
	
/********************************************************** ENABLE the EXTI interrupt **************************************************/			
					
					EXTI->IMR |= (1 << pGPIOhandle->GPIO_pinconfig.GPIO_pin_number);
					
}



/************************************************************************************************************************************/
/************************************************  GPIO READ INPUT FUNCTION (PIN)  **************************************************/
/************************************************************************************************************************************/



uint8_t  GPIO_Read(GPIO_TypeDef *pGPIOx, uint8_t pinnumber)
{
		uint8_t value;
	
		value = (uint8_t)((pGPIOx->IDR  >> pinnumber) & 0x00000001);
	
	  return value;
}



/************************************************************************************************************************************/
/************************************************  GPIO READ INPUT FUNCTION (PORT) **************************************************/
/************************************************************************************************************************************/



uint8_t GPIO_ReadPort(GPIO_TypeDef *pGPIOx)
{
		uint8_t value;
	
		value = (uint8_t)(pGPIOx->IDR);
	
	  return value;
}



/************************************************************************************************************************************/
/************************************************  GPIO WRITE OUTPUT FUNCTION (PIN)  ************************************************/
/************************************************************************************************************************************/



void GPIO_Write(GPIO_TypeDef *pGPIOx, uint8_t pinnumber, uint8_t value)
{
   if(value==SET)
	 {		 
			pGPIOx->ODR |= (1<<pinnumber);
	 }
	 else
	 {
			pGPIOx->ODR &= ~(1<<pinnumber);
	 
	 }
}	

/************************************************************************************************************************************/
/************************************************  GPIO TOGGLE OUTPUT PIN FUNCTION  *************************************************/
/************************************************************************************************************************************/



void GPIO_Toggle(GPIO_TypeDef *pGPIOx , uint8_t pin_number)
{
			pGPIOx->ODR ^= ( 1<<(pin_number));		
}



/************************************************************************************************************************************/
/************************************************  GPIO IRQ CONFIGURATION FUNCTION  *************************************************/
/************************************************************************************************************************************/


/*
void GPIO_IRQinterruptConfig(uint8_t IRQnumber ,uint8_t ENorDI)
{
		if(ENorDI == ENABLE)
		{
				if(IRQnumber <= 31)
				{
						*NVIC_ISER0 |= (1 << IRQnumber);
				}
				else if(IRQnumber > 31 && IRQnumber < 64 )
				{
						*NVIC_ISER1 |= (1 << (IRQnumber % 32));
				}             
				else if(IRQnumber >= 64 && IRQnumber < 96 )
				{
						*NVIC_ISER2 |= (1 << (IRQnumber % 64));
				}
		}
		else 
		{		
				if(IRQnumber <= 31)
				{
						*NVIC_ICER0 |= (1 << IRQnumber);
				}
				else if(IRQnumber > 31 && IRQnumber < 64 )
				{
						*NVIC_ICER1 |= (1 << (IRQnumber % 32));
				}             
				else if(IRQnumber >= 64 && IRQnumber < 96 )
				{
						*NVIC_ICER2 |= (1 << (IRQnumber % 64));
				}
		}
}
*/


/****************************************************************************************************************************************/
/**********************************************************  GPIO IRQ PRIROTY FUNCTION  *************************************************/
/****************************************************************************************************************************************/


/*
void GPIO_IRQPriorityConfig(uint8_t IRQnumber ,uint8_t IRQPriority)
{
		 uint8_t iprx = (IRQnumber / 4);
		 uint8_t iprx_section = (IRQnumber % 4);

		 *(NVIC_PR_BASE_ADDR + (iprx * 4)) |= (IRQPriority << ((iprx_section * 8)+4) );
}
*/


/***************************************************************************************************************************************/
/********************************************************  GPIO IRQ HANDLING FUNCTION  *************************************************/
/***************************************************************************************************************************************/



void GPIO_IRQhandling(uint8_t pinnumber)
{
    if(EXTI->PR & (1 << pinnumber))
		{
				EXTI->PR |= (1 << pinnumber);
		}
} 



/*************************************************************************************************************************************/
/***********************************************************  AFIO FUNCTIONS  ********************************************************/
/*************************************************************************************************************************************/



//void AFIO_TIM3_init(AFIO_handle_t *pAFIOhandle)
//{
//	    	 AFIO_EN();
//		pAFIOhandle->pAFIO->EVCR |= (1<<7);
//		pAFIOhandle->pAFIO->MAPR |= (pAFIOhandle->AFIO_pinconfig.TIM3_REMAP << 10);
//}

// 

//void AFIO_SPI1_init(AFIO_handle_t *pAFIOhandle)
//{
//	    	 AFIO_EN();
//		pAFIOhandle->pAFIO->EVCR |= (1<<7);
//		pAFIOhandle->pAFIO->MAPR |= (pAFIOhandle->AFIO_pinconfig.SPI1_REMAP << 0);
//}


