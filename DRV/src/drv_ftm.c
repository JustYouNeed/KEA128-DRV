# include "drv_ftm.h"


void drv_ftm_BaseInit(FTM_Type *FTMx, FTM_BaseInitTypeDef *FTM_BaseInitStruct)
{
	FTMx->MODE |= 1 << 2;  /*  È¥³ýÐ´±£»¤  */
	FTMx->SC |= FTM_BaseInitStruct->FTM_ClockSource << 3;
	FTMx->SC |= FTM_BaseInitStruct->FTM_Prescaler << 0;
	
	
}


