

//#include  "STM32F103C_RCC_DRIVER.h"


//static uint16_t  AHB_prescalar[8] = {2,4,8,16,64,128,256,512};  
//static uint16_t  APB1_prescalar[8] = {2,4,8,16};  





//uint8_t RCC_getPLLoutputclock(void)
//{
//  
//}



//uint32_t RCC_getPCLK1value(void)
//{
//		uint32_t pclk1 , systemclk;
//		uint8_t clksrc , temp , ahbp , apb1p; 
//	
//	/******************* reading the clock source *****************/
//							clksrc = ((RCC->CFGR >> 2) & 0x3);
//	/**************************************************************/
//	
//		if(clksrc == 0)
//	  {
//				systemclk = 8000000;
//		}
//		else if(clksrc == 1)
//		{
//				systemclk = 8000000;
//		}
//		else
//		{
//				systemclk = RCC_getPLLoutputclock(); 
//		}
//	 
//					/************************ for ahb prescalar *********************/
//							        temp = ((RCC->CFGR >> 4) & 0x0F);
//					/****************************************************************/
//		
//		if( temp < 8)
//		{
//				ahbp = 1;
//		}
//		else
//		{
//				ahbp = AHB_prescalar[temp-8];
//		}
//		
//					/************************ for apb1 prescalar *********************/
//											temp = ((RCC->CFGR >> 10) & 0x07);
//				  /*****************************************************************/
//		
//		if( temp < 4)
//		{
//				apb1p = 1;
//		}
//		else
//		{
//				apb1p = APB1_prescalar[temp-4];
//		}
//	
//		/*************** calculating the value of  pclk1 ****************/
//									pclk1 = ((systemclk / ahbp) / apb1p);
//		/****************************************************************/
//		
//	return pclk1 ;
//}
