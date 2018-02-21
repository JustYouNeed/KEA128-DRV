/**
  *******************************************************************************************************
  * File Name: drv_adc.c
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-1
  * Brief: KEA128оƬADC�ײ���������
  *******************************************************************************************************
  * History
  *		1.Data: 2018-2-1
	*     Author: Vector
	*     Mod: �����ļ�,��ӻ�������
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
	
	drv_rcc_ClockCmd(RCC_PeriphClock_ADC, ENABLE);  /*  ����ADCʱ��  */
	
	ADC->APCTL1 |= ADC_InitStruct->ADC_Channel;     /*  ����ADC����ͨ��  */
	ADC->SC3 |= ADC_InitStruct->ADC_Resolution;			/*  ����ADC����λ��  */
	ADC->SC3 |= ADC_InitStruct->ADC_Prescaler;			/*  ʱ�ӷ�Ƶ  */
	ADC->SC4 |= ADC_InitStruct->ADC_FIFOLevel;
	
	if(ADC_InitStruct->ADC_ContinuousConvMode == ENABLE)	/*  �������������ת��ģʽ  */
		ADC->SC1 |= 1 << 5;
	else
		ADC->SC1 &= ~(1 << 5);
	
	if(ADC_InitStruct->ADC_IRQCmd == ENABLE)		/*  ���ʹ�����ж�  */
		ADC->SC1 |= 1 << 6;
	else
		ADC->SC1 &= ~(1 << 6);
	
	ADC->SC1 |= ADC_InitStruct->ADC_ContinuousConvMode << 5;
	
	/*  ���������FIFO�������,����Ҫ����Ҫ������ADCͨ������д��FIFO,ֱ��д��,ϵͳ�Ż���������  */
	if(ADC_InitStruct->ADC_FIFOLevel != ADC_FIFO_Disable)
	{
		for(i = 0; i < 16; i++)	/*  һλһλ���  */
		{
			posbit = (uint16_t)((ADC_InitStruct->ADC_Channel >> i) & 0x01);
			if(posbit)		/*  ��������˸�ͨ��  */
			{
				ADC->SC1 |= i;
			}
		}
	}
}


/********************************************  END OF FILE  *******************************************/
