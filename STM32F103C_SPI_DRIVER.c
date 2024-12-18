
#include "STM32F103C_SPI_DRIVER.h"
#include "stm32f10x.h"
#include "string.h"
#include <stdint.h>


/*************************************************************************************************************************************/
/********************************************************   CLOCK SETUP   ************************************************************/
/*************************************************************************************************************************************/




void SPI_periclockcontrol(SPI_TypeDef *pSPIx, uint8_t enordi)
{
		if(enordi == ENABLE)
	{
			if(pSPIx == SPI1)
			{
					SPI1_PCLK_EN();
			}
			else if(pSPIx == SPI2)
			{
					SPI2_PCLK_EN();
			}
			else if(pSPIx == SPI3)	
			{
					SPI3_PCLK_EN();
			}
	}
	else
	{
		if(pSPIx == SPI1)
			{
					SPI1_PCLK_DI();
			}
			else if(pSPIx == SPI2)
			{
					SPI2_PCLK_DI();	
			}
			else if(pSPIx == SPI3)
			{
					SPI3_PCLK_DI();
			}
	}
}





/**********************************************************************************************************************************/
/******************************************************  SPI init  function   *****************************************************/
/**********************************************************************************************************************************/





void SPI_init(SPI_handle_t *pSPIhandle)
{ 	
	
			/*////////////////////// SPI CLOCK ENABLE ////////////////////*/
										SPI_periclockcontrol(SPI1,ENABLE);
			/*////////////////////////////////////////////////////////////*/
	
	
		uint16_t  temp = 0;
	
	
	if(pSPIhandle->SPIConfig.SPI_CONFIGURATION==SPI_CONFIGURATION_FD)
	{
			temp&=~(1<<15);	
	}
	else if(pSPIhandle->SPIConfig.SPI_CONFIGURATION==SPI_CONFIGURATION_HD)
	{
			temp|=(1<<15);
	}
	else if(pSPIhandle->SPIConfig.SPI_CONFIGURATION==SPI_CONFIGURATION_RXONLY)
	{
			temp&=~(1<<15);
		
			temp|=(1<<10);
	}
				temp|=pSPIhandle->SPIConfig.SPI_MODE<<2;
			
				temp|=pSPIhandle->SPIConfig.SPI_CPHA<<0;
			
				temp|=pSPIhandle->SPIConfig.SPI_CPOL<<1;
			
				temp|=pSPIhandle->SPIConfig.SPI_SSM<<9;
			
				temp|=pSPIhandle->SPIConfig.SPI_CLKSPEED<<3;
			
				temp|=pSPIhandle->SPIConfig.SPI_DFF<<11;
			
				temp|=pSPIhandle->SPIConfig.SPI_FRAMEFORMATE<<7;
			
	/********************* programming the SPI CR1 register **********************/
													pSPIhandle->pSPIx->CR1 = temp;	
	/*****************************************************************************/
	
}	



/**********************************************************************************************************************************/
/***************************************************  SPI GET FALG STATUS  ***** **************************************************/
/**********************************************************************************************************************************/



uint8_t SPI_getflagstatus(SPI_TypeDef *pSPIx, uint8_t flagname)
{
	
	if(pSPIx->SR & flagname)
	{
			return FLAG_SET;
	}
   return FLAG_RESET;	
}



/**********************************************************************************************************************************/
/**********************************************************  SPI transmit data   **************************************************/
/**********************************************************************************************************************************/



																															/***********/
																															/***********/
																															/***  1  ***/
																															/***********/
																															/***********/



//void SPI_transmitdata(SPI_TypeDef *pSPIx, uint8_t pTXbuffer)
//{
//		while(len>0)
//		{		
//			
//			/*******************  checking for flag status *************************/
//						while(SPI_getflagstatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);
//			/***********************************************************************/
//			
//			
//												/***************** for 16 bits data frame formate **********************/
//			
//					if((pSPIx->CR1 & (1<<11)))
//					{
//								pSPIx->DR = (pTXbuffer);
////								len--;
////					  		len--;
////					  		(uint16_t*)pTXbuffer ++;
//					}     
//												/***************** for 8 bits data frame formate **********************/					
//					else
//					{ 
//									pSPIx->DR = (pTXbuffer);
////									len--;
////							    pTXbuffer++;
//					}	
//					
//					
//				/*******************  checking for flag status *************************/	
//					while(SPI_getflagstatus(pSPIx,SPI_BUSY_FLAG) == FLAG_SET);
//				/***********************************************************************/	
//					
//		}	
//}	
						
																																/***********/
																																/***********/
																																/***  2  ***/
																																/***********/
																																/***********/


void SPI_transmitdata2(SPI_TypeDef *pSPIx, uint16_t *pTXbuffer, uint8_t len)
{
	
		while(len>0)
		{		
				
			/*******************  checking for flag status *************************/
						while(SPI_getflagstatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);
			/***********************************************************************/
			
			
														/***************** for 16 bits data frame formate *********************/		
			
					if((pSPIx->CR1 & (1<<11)))
					{	
								pSPIx->DR = *pTXbuffer;
								len--;
								len--;
								pTXbuffer ++;
					} 
														/***************** for 8 bits data frame formate **********************/			
					
					else
					{ 
									pSPIx->DR = *((uint8_t*)pTXbuffer);
									len--;
								 (uint8_t)pTXbuffer++;
					}	
					
								/*******************  checking for flag status *************************/	
									while(SPI_getflagstatus(pSPIx,SPI_BUSY_FLAG) == FLAG_SET);
								/***********************************************************************/	
		}	
}	





/**********************************************************************************************************************************/
/**********************************************************  SPI receive data   **************************************************/
/**********************************************************************************************************************************/





void SPI_receivedata(SPI_TypeDef *pSPIx, uint8_t *pRXbuffer, uint8_t len)
{
		while(len>0)
		{		
				
				/*******************  checking for flag status *************************/
				 while(SPI_getflagstatus(pSPIx,SPI_RXE_FLAG) == FLAG_SET);
				/***********************************************************************/
				
				
													/********************* for 16 bit data frame formate *************************/
				
				if((pSPIx->CR1 & (1<<11)))
				{
						
							*((uint16_t*)pRXbuffer) = pSPIx->DR;
							len--;
							len--;
							(uint16_t*)pRXbuffer ++;
				} 
													 /***************** for 8 bit data frame formate ******************************/			
				
				else
				{ 	
							*(pRXbuffer) = pSPIx->DR ;
								len--;
							 pRXbuffer++;
				}	
		}
}






/**********************************************************************************************************************************/
/***********************************************  SPI peripherial control function   **********************************************/
/**********************************************************************************************************************************/






void SPI_peripherialcontrol(SPI_TypeDef *pSPIx, uint8_t enordi)
{
		if(enordi==ENABLE)
		{
			pSPIx->CR1 |= (1<<6);
		}
		else
		{
				pSPIx->CR1 &= ~(1<<6);
		}
}






/**********************************************************************************************************************************/
/**************************************************  SPI SSI bit configuration data   *********************************************/
/**********************************************************************************************************************************/





void SPI_SSIconfig(SPI_TypeDef *pSPIx, uint8_t enordi)
{
		if(enordi==ENABLE)
		{
			pSPIx->CR1 |= (1<<8);
		}
		else
		{
			pSPIx->CR1 &= ~(1<<8);
		}
}	

