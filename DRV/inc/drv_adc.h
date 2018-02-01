# ifndef __DRV_ADC_H
# define __DRV_ADC_H

# include "derivative.h"


#define ADC_Channel_0                               ((uint16_t)0x0001)
#define ADC_Channel_1                               ((uint16_t)0x0002)
#define ADC_Channel_2                               ((uint16_t)0x0004)
#define ADC_Channel_3                               ((uint16_t)0x0008)
#define ADC_Channel_4                               ((uint16_t)0x0010)
#define ADC_Channel_5                               ((uint16_t)0x0020)
#define ADC_Channel_6                               ((uint16_t)0x0040)
#define ADC_Channel_7                               ((uint16_t)0x0080)
#define ADC_Channel_8                               ((uint16_t)0x0100)
#define ADC_Channel_9                               ((uint16_t)0x0200)
#define ADC_Channel_10                              ((uint16_t)0x0400)
#define ADC_Channel_11                              ((uint16_t)0x0800)
#define ADC_Channel_12                              ((uint16_t)0x1000)
#define ADC_Channel_13                              ((uint16_t)0x2000)
#define ADC_Channel_14                              ((uint16_t)0x4000)
#define ADC_Channel_15                              ((uint16_t)0x8000)

#define ADC_TwoSamplingDelay_5Cycles               ((uint32_t)0x00000000)
#define ADC_TwoSamplingDelay_6Cycles               ((uint32_t)0x00000100)
#define ADC_TwoSamplingDelay_7Cycles               ((uint32_t)0x00000200)
#define ADC_TwoSamplingDelay_8Cycles               ((uint32_t)0x00000300)
#define ADC_TwoSamplingDelay_9Cycles               ((uint32_t)0x00000400)
#define ADC_TwoSamplingDelay_10Cycles              ((uint32_t)0x00000500)
#define ADC_TwoSamplingDelay_11Cycles              ((uint32_t)0x00000600)
#define ADC_TwoSamplingDelay_12Cycles              ((uint32_t)0x00000700)
#define ADC_TwoSamplingDelay_13Cycles              ((uint32_t)0x00000800)
#define ADC_TwoSamplingDelay_14Cycles              ((uint32_t)0x00000900)
#define ADC_TwoSamplingDelay_15Cycles              ((uint32_t)0x00000A00)
#define ADC_TwoSamplingDelay_16Cycles              ((uint32_t)0x00000B00)
#define ADC_TwoSamplingDelay_17Cycles              ((uint32_t)0x00000C00)
#define ADC_TwoSamplingDelay_18Cycles              ((uint32_t)0x00000D00)
#define ADC_TwoSamplingDelay_19Cycles              ((uint32_t)0x00000E00)
#define ADC_TwoSamplingDelay_20Cycles              ((uint32_t)0x00000F00)

#define ADC_Prescaler_Div2                         ((uint32_t)0x00000000)
#define ADC_Prescaler_Div4                         ((uint32_t)0x00010000)
#define ADC_Prescaler_Div6                         ((uint32_t)0x00020000)
#define ADC_Prescaler_Div8                         ((uint32_t)0x00030000)


#define ADC_Resolution_12b                         ((uint32_t)0x00000008)
#define ADC_Resolution_10b                         ((uint32_t)0x00000004)
#define ADC_Resolution_8b                          ((uint32_t)0x00000000)

typedef struct
{
	uint16_t ADC_Channel;											/*  ADC 通道  */
	uint32_t ADC_Resolution;									/*  ADC数据位数  */
  FunctionalState ADC_ScanConvMode;					/*  扫描模式  */
	FunctionalState ADC_ContinuousConvMode;		/*  连续转换  */
	uint32_t ADC_TwoSamplingDelay;						/*  采样间隔  */
	uint32_t ADC_Prescaler;										/*  ADC时钟分频  */
	uint32_t ADC_ExternalTrigConvEdge;				/*  外部触发采样  */
}ADC_InitTypeDef;


void drv_adc_Init(ADC_InitTypeDef *ADC_InitStruct);


# endif

