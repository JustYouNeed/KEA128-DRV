# ifndef __DRV_FTM_H
# define __DRV_FTM_H

# include "derivative.h"

# define FTM_OCChannel_0				(uint8_t)0x01
# define FTM_OCChannel_1				(uint8_t)0x02
# define FTM_OCChannel_2				(uint8_t)0x04
# define FTM_OCChannel_3				(uint8_t)0x08
# define FTM_OCChannel_4				(uint8_t)0x10
# define FTM_OCChannel_5				(uint8_t)0x20
# define FTM_OCChannel_6				(uint8_t)0x40
# define FTM_OCChannel_7				(uint8_t)0x80


typedef struct
{
	uint8_t FTM_Prescaler;		/*  时钟预分频系数  */
	uint16_t FTM_CounterMode;	/*  计数模式  */
	uint32_t FTM_Period;			/*  定时器周期  */
	uint8_t FTM_ClockSource;	/*  时钟源  */
	uint8_t  FTM_RepetitionCounter;
	uint8_t  FTM_IRQCmd;
}FTM_BaseInitTypeDef;

typedef struct
{
	uint8_t  FTM_OCChannel;
	uint16_t FTM_OCMode;
	uint16_t FTM_OutputState;
	uint32_t FTM_Pulse;
	uint16_t FTM_OCPolarity;
	uint16_t FTM_OCIdleState;
}FTM_OCInitTypeDef;


typedef enum
{
	FTM_Prescaler_1 = 0,
	FTM_Prescaler_2,
	FTM_Prescaler_4,
	FTM_Prescaler_8,
	FTM_Prescaler_16,
	FTM_Prescaler_32,
	FTM_Prescaler_64,
	FTM_Prescaler_128,
}FTM_PrescalerTypeDef;


void drv_ftm_BaseInit(FTM_Type *FTMx, FTM_BaseInitTypeDef *FTM_BaseInitStruct);
void drv_ftm_OCInit(FTM_Type *FTMx, FTM_OCInitTypeDef *FTM_OCInitStruct);

# endif

