/**
  *******************************************************************************************************
  * File Name: drv_adc.c
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-1
  * Brief: KEA128芯片ADC底层驱动函数
  *******************************************************************************************************
  * History
  *		1.Data: 2018-2-1
	*     Author: Vector
	*     Mod: 建立文件,添加基本函数
  *
  *******************************************************************************************************
  */
	

/*
  *******************************************************************************************************
  *                              INCLUDE FILES
  *******************************************************************************************************
*/
# include "drv_adc.h"
# include "drv_rcc.h"


/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments  : 
*
* Reutrn     : 
*
* Note(s)    : 
*********************************************************************************************************
*/
void drv_adc_Init(ADC_InitTypeDef *ADC_InitStruct)
{
	uint16_t posbit = 0;
	uint8_t i = 0;
	
	drv_rcc_ClockCmd(RCC_PeriphClock_ADC, ENABLE);  /*  开启ADC时钟  */
	
	ADC->APCTL1 |= ADC_InitStruct->ADC_Channel;     /*  设置ADC采样通道  */
	ADC->SC3 |= ADC_InitStruct->ADC_Resolution;			/*  设置ADC采样位数  */
	ADC->SC3 |= ADC_InitStruct->ADC_Prescaler;			/*  时钟分频  */
	ADC->SC4 |= ADC_InitStruct->ADC_FIFOLevel;
	
	if(ADC_InitStruct->ADC_ContinuousConvMode == ENABLE)	/*  如果开启了连续转换模式  */
		ADC->SC1 |= 1 << 5;
	else
		ADC->SC1 &= ~(1 << 5);
	
	if(ADC_InitStruct->ADC_IRQCmd == ENABLE)		/*  如果使能了中断  */
		ADC->SC1 |= 1 << 6;
	else
		ADC->SC1 &= ~(1 << 6);
	
	ADC->SC1 |= ADC_InitStruct->ADC_ContinuousConvMode << 5;
	
	/*  如果设置了FIFO采样深度,则需要将需要采样的ADC通道连续写入FIFO,直到写满,系统才会启动采样  */
	if(ADC_InitStruct->ADC_FIFOLevel != ADC_FIFO_Disable)
	{
		for(i = 0; i < 16; i++)	/*  一位一位检查  */
		{
			posbit = (uint16_t)((ADC_InitStruct->ADC_Channel >> i) & 0x01);
			if(posbit)		/*  如果开启了改通道  */
			{
				ADC->SC1 |= i;
			}
		}
	}
}


/********************************************  END OF FILE  *******************************************/
