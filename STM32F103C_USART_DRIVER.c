
#include "STM32F103C_USART_DRIVER.h"


/************************************************************************************************************************************/
/****************************************  USASRT	PERIPHERIAL CLOCK ENABLE AND DISABLE  **********************************************/
/**************************************************************************************************************************************/


void USART_periclockcontrol(USART_TypeDef *pUSARTx , uint16_t enordi)
{
		if(enordi == ENABLE)
		{
				if(pUSARTx == USART1)
				{
						USART1_PCLK_EN();
				}
				else if(pUSARTx == USART2)
				{
						USART2_PCLK_EN();
				}
				else if(pUSARTx == USART3)
				{
						USART3_PCLK_EN();
				}
		}
    else
		{
				if(pUSARTx == USART1)
				{
					  USART1_PCLK_DI();
				}
				else if(pUSARTx == USART2)
				{
						USART2_PCLK_DI();
				}
				else if(pUSARTx == USART3)
				{
						USART3_PCLK_DI();
				}
		}
}





/***************************************************************************************************************************/
/********************************************  USART INIT FUNCTION DEFINATION  *********************************************/
/***************************************************************************************************************************/



void USART_init(USART_handle_t  *USARThandle)
{
	uint16_t var=0;
	
	USARThandle->pUSARTx->CR1 &=~(0xFFFFFFFF);
	USARThandle->pUSARTx->CR2 &=~(0xFFFFFFFF);
	USARThandle->pUSARTx->CR3 &=~(0xFFFFFFFF);
  
	
	////////// usart peripherial clock enable ////////
	        USART_periclockcontrol(USARThandle->pUSARTx,ENABLE);
	//*************************************************
	
																					////////////////////////////////////
																					//////////////USART_CR1_////////////
																					////////////////////////////////////
	
////////////////////////////////////////////////////// USART MODE SELECTION /////////////////////////////////////////////////////////
			
			if(USARThandle->USARTconfig.USART_MODE == USART_MODE_RX)
			{
					var |= (1<<2);		
			}
			else if(USARThandle->USARTconfig.USART_MODE == USART_MODE_TX)
			{
					var |= (1<<3);
			}
			else if(USARThandle->USARTconfig.USART_MODE == USART_MODE_RXTX)
			{
					var |=((1<<2) | (1<<3));
			}

////////////////////////////////////////////////////// USART PARITY SELECTION /////////////////////////////////////////////////////
	
			if(USARThandle->USARTconfig.USART_PARITY_BIT == USART_EVEN_PARITY_EN)
			{
					var |= (1<<10);
					var &= ~(1<<9);
			}
			else if(USARThandle->USARTconfig.USART_PARITY_BIT == USART_ODD_PARITY_EN)
			{
					var |= (1<<10);
					var |= (1<<9);
			}
			else if(USARThandle->USARTconfig.USART_PARITY_BIT == USART_PARITY_DISABLE)
			{
					var &= ~(1<<10);
			}
		
///////////////////////////////////////////////// USART WORD LENGTH SELECTION /////////////////////////////////////////////////////
	
			if(USARThandle->USARTconfig.USART_WORD_LENGTH == USART_8_BIT_DATA)
			{
					var &=~(1<<12);
			}
			else if(USARThandle->USARTconfig.USART_WORD_LENGTH == USART_9_BIT_DATA)
			{
					var |=(1<<12);
			}
							
			///////////////PROGRAMING THE CR1///////////////
								USARThandle->pUSARTx->CR1 |= var;
			////////////////////////////////////////////////
			
			
			
																				 /////////////////////////////////////////
																				 ///////////////USART_CR2/////////////////
																				 /////////////////////////////////////////
			
			var = 0;
/////////////////////////////////////////////// USART NUMBER OF STOP BITS /////////////////////////////////////////////////
			
			if(USARThandle->USARTconfig.USART_NUM_OF_STOP_BIT == USART_1_STOP_BIT)
			{ 	
					var &=~(1<<12);
			}
			else if(USARThandle->USARTconfig.USART_NUM_OF_STOP_BIT == USART_005_STOP_BIT)
			{
					var |=(1<<12);
			}
			else if(USARThandle->USARTconfig.USART_NUM_OF_STOP_BIT == USART_2_STOP_BIT)
			{
					var |=(2<<12);
			}
			else if(USARThandle->USARTconfig.USART_NUM_OF_STOP_BIT == USART_105_STOP_BIT)
			{
					var |=(3<<12);
			}
			
			///////////////PROGRAMING THE CR2///////////////
								USARThandle->pUSARTx->CR2 |= var;
			////////////////////////////////////////////////
			
			

																				 /////////////////////////////////////////
																				 ///////////////USART_CR3/////////////////
																				 /////////////////////////////////////////

				var=0;
////////////////////////////////////////////// USART HW FLOW CONTROL ///////////////////////////////////////////////////
			
			if(USARThandle->USARTconfig.USART_HW_FLOW_CONTROL == USART_HW_FLOW_CONTROL_NONE)
			{
					var &= ~((1<<8) | (1<<9));
			}
			else if(USARThandle->USARTconfig.USART_HW_FLOW_CONTROL == USART_HW_FLOW_CONTROL_CTS)
			{
					var |= (1<<9);
			}
			else if(USARThandle->USARTconfig.USART_HW_FLOW_CONTROL == USART_HW_FLOW_CONTROL_RTS)
			{
					var |= (1<<8);
			}
			else if(USARThandle->USARTconfig.USART_HW_FLOW_CONTROL == USART_HW_FLOW_CONTROL_CTS_RTS)
			{
					var |= ((1<<8) | (1<<9));
			}
				
			///////////////PROGRAMING THE CR3///////////////
								USARThandle->pUSARTx->CR3 |= var;
			////////////////////////////////////////////////
		
			
			USART_peripherialcontrol(USARThandle->pUSARTx,ENABLE);
			//************  CONFIGURATION OF BAUD RATE REGISTER  *************
							USART_set_baudrate(USARThandle->pUSARTx , USARThandle->USARTconfig.USART_BAUDRATE);
			//*****************************************************************						
			
}
			
			
			
/*************************************************************************************************************************/
/***************************************  USART PERIPHERIAL CONTROL FUNCTION DEFINATION  *********************************/
/*************************************************************************************************************************/

			
void USART_peripherialcontrol(USART_TypeDef *pUSARTx ,uint16_t enordi)
{
			if(enordi == ENABLE)
			{
					pUSARTx->CR1 |= (1<<13);
			}
			else
			{
					pUSARTx->CR1 &=~(1<<13);
			}
	}	
	
	
/*************************************************************************************************************************/
/******************************************  USART STATUS FLAG FUNCTION DEFINATION  **************************************/
/*************************************************************************************************************************/
	
	



uint8_t USART_getflagstatus(USART_TypeDef *pUSARTx, uint8_t flagname)
{
		if(pUSARTx->SR & flagname)
		{
				return FLAG_SET;
		}
				return FLAG_RESET;	
}





/**************************************************************************************************************************/
/*********************************************  USART SET BAUDRATE FUNCTION  ******************************************/
/***********************************************************************************************************************/




void USART_set_baudrate(USART_TypeDef *pUSARTx , uint32_t baud_rate)
{
			uint32_t USARTDIV,M_PART, F_PART;
			uint16_t var = 0;
			uint32_t pclk1 = 36000000 ,pclk2 = 72000000 ;
			
			if(pUSARTx ==  (USART2))
			{
					USARTDIV=((pclk1*100)/(16*baud_rate));		    
			}
			else if(pUSARTx == (USART3))
			{
					USARTDIV=((pclk1*100)/(16*baud_rate));		    
			}
			else
			{
					USARTDIV = ((pclk2*100)/(16*baud_rate));
			}
			
			/***************** mantissa part ****************/
									M_PART = (USARTDIV/100) ; 
			/************************************************/
	
			
			/***************** fraction part ****************/
							F_PART = (USARTDIV - (100*M_PART));
							F_PART = (((F_PART*16)+50) / 100);			
			/************************************************/
			
			var |= (M_PART << 4);
			var |= (F_PART);
			
			/************ PROGRAMING THE BRR REGISTER **********/
										pUSARTx->BRR |= var;												
			/***************************************************/
	
}





/*************************************************************************************************************************/
/******************************************  USART TRANSMIT DATA FUNCTION DEFINATION  ************************************/
/*************************************************************************************************************************/
	
	
																											/***********/
																											/***********/
																											/***  1  ***/
																											/***********/
																											/***********/


void USART_transmitdata(USART_handle_t *pUSARThandle , uint8_t *pTXbuffer , uint32_t len)
{
			uint32_t i;
	
	    for(i=0;i<len;i++)
	 		{
													    /***************  CHECKING THE FLAG STATUS  ******************/
					while(USART_getflagstatus(pUSARThandle->pUSARTx,USART_TXE_FLAG) == FLAG_RESET)
					{}
				
						
																	/*****************************************************/
																	/***************** FOR 8 BIT DATA ********************/
																	/*****************************************************/
						
						
						if(pUSARThandle->USARTconfig.USART_WORD_LENGTH == USART_8_BIT_DATA)
						{
									pUSARThandle->pUSARTx->DR |= (*(uint8_t*)pTXbuffer);
							
								(pTXbuffer++);
						}
						
						
						
																	/*****************************************************/
																	/***************** FOR 9 BIT DATA ********************/
																	/*****************************************************/
						else
						{
								pUSARThandle->pUSARTx->DR |= ((*(uint16_t*)pTXbuffer)& (uint16_t)0x01FF);
									
							
									if(pUSARThandle->USARTconfig.USART_PARITY_BIT == USART_PARITY_DISABLE)
									{
												pTXbuffer++;
												pTXbuffer++;
									}
									else
									{
												pTXbuffer++;
									}
							
						}
			}
			
																/***************  CHECKING THE FLAG STATUS  ******************/
			while(USART_getflagstatus(pUSARThandle->pUSARTx,USART_TC_FLAG) == FLAG_RESET);
}



																											/***********/
																											/***********/
																											/***  2  ***/
																											/***********/
																											/***********/




void USART_transmitdata9bitstring(USART_handle_t *pUSARThandle , uint8_t *pTXbuffer , uint32_t len)
{
			
			uint32_t i;
	
	    for(i=0;i<len;i++)
	 		{
					while(USART_getflagstatus(pUSARThandle->pUSARTx,USART_TXE_FLAG) == FLAG_RESET)
					{}
					
					if(pUSARThandle->USARTconfig.USART_WORD_LENGTH == USART_9_BIT_DATA)
					{
							pUSARThandle->pUSARTx->DR |= ((*(uint8_t*)pTXbuffer)& (uint16_t)0x01FF);
						
										pTXbuffer++;
					}
			}
			while(USART_getflagstatus(pUSARThandle->pUSARTx,USART_TC_FLAG) == FLAG_RESET);
}



																											/***********/
																											/***********/
																											/***  3  ***/
																											/***********/
																											/***********/





void USART_SendData(uint8_t pTxBuffer)
{
			while(USART_getflagstatus(USART2,USART_TXE_FLAG) == FLAG_RESET);			
			USART2->DR = pTxBuffer;
			while(USART_getflagstatus(USART2,USART_TC_FLAG) == FLAG_RESET);
}







/*************************************************************************************************************************/
/******************************************  USART RECEIVE DATA FUNCTION DEFINATION  ************************************/
/*************************************************************************************************************************/
	





void USART_receivedata(USART_handle_t *pUSARThandle , uint8_t *pRXbuffer , uint32_t len)
{
			uint32_t i;
	
		
	    for(i=0;i<len;i++)
	 		{
													    /***************  CHECKING THE FLAG STATUS  ******************/
					while(USART_getflagstatus(pUSARThandle->pUSARTx,USART_RXNE_FLAG) == FLAG_RESET)
					{}
				
						
																	/*****************************************************/
																	/***************** FOR 8 BIT DATA ********************/
																	/*****************************************************/
						
						
						if(pUSARThandle->USARTconfig.USART_WORD_LENGTH == USART_8_BIT_DATA)
						{
									(*(uint8_t*)pRXbuffer) |= ((pUSARThandle->pUSARTx->DR) & ((uint8_t)0x00FF));
							
										pRXbuffer++;
						}
						
						
						
																	/*****************************************************/
																	/***************** FOR 9 BIT DATA ********************/
																	/*****************************************************/
						else
						{
								(*(uint16_t*)pRXbuffer) |= ((pUSARThandle->pUSARTx->DR) & ((uint16_t)0x01FF)) ;
									
							
									if(pUSARThandle->USARTconfig.USART_PARITY_BIT == USART_PARITY_DISABLE)
									{
												pRXbuffer++;
												pRXbuffer++;
									}
									else
									{
												pRXbuffer++;
									}
							
						}
			}
			
																/***************  CHECKING THE FLAG STATUS  ******************/
			while(USART_getflagstatus(pUSARThandle->pUSARTx,USART_TC_FLAG) == FLAG_RESET);
}





