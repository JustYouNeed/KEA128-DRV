# include "drv_adc.h"
# include "drv_rcc.h"

void drv_adc_Init(ADC_InitTypeDef *ADC_InitStruct)
{
	drv_rcc_ClockCmd(RCC_PeriphClock_ADC, ENABLE);
	
	ADC->APCTL1 |= ADC_InitStruct->ADC_Channel;
	ADC->SC3 |= ADC_InitStruct->ADC_Resolution;
	ADC->SC3 |= ADC_InitStruct->ADC_Prescaler;
	
	ADC->SC1 |= ADC_InitStruct->ADC_ContinuousConvMode << 5;
}



