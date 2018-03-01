# include "drv.h"
# include "bsp.h"

void test_Led1Test(void)
{
	bsp_led_Toggle(1);
}

void test_Led2Test(void)
{
	bsp_led_Toggle(2);
}

int main(void)
{		
	uint16_t cnt = 0;
	ADC_InitTypeDef ADC_InitStruct;
	
	ADC_InitStruct.ADC_Channel = ADC_Channel_A0 | ADC_Channel_A1;
	ADC_InitStruct.ADC_ChannelCount = 2;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_IRQCmd = ENABLE;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ClockSource = ADC_RefSource_VDD;
//	ADC_InitStruct.ADC_TrigConvMode
	drv_adc_Init(&ADC_InitStruct);
	
	bsp_Config();
	
	
	
//	bsp_tim_CreateHardTimer(0, 200, test_Led1Test);
	bsp_tim_CreateHardTimer(1, 400, test_Led2Test);
	
	while(1)
	{
		bsp_tim_DelayMs(400);		
//		cnt ++;
//		
//		if(cnt > 20)
//		{
//			bsp_tim_DeleteHardTimer(0);
//			bsp_tim_DeleteHardTimer(1);
//		}
	}
}

