/**
  *******************************************************************************************************
  * File Name: drv_kbi.c
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-28
  * Brief: 本文件定义了有关操作KBI外设的底层驱动函数
  *******************************************************************************************************
  * History
  *		1.Author: Vector
	*     Date: 2018-2-28
	*     Mod: 建立文件
  *
  *******************************************************************************************************
  */	

/*
  *******************************************************************************************************
  *                              INCLUDE FILES
  *******************************************************************************************************
*/
# include "drv_kbi.h"


static KBI_Type * const KBIX[] = KBI_BASES;

void drv_kbi_Init(KBI_ChannelType KBI_Channel, KBI_TrigModeType KBI_TrigMode)
{
	uint8_t kbix, kbin;
	
	kbix = (uint8_t)(KBI_Channel >> 5);			/*  得到KBI模块编号  */
	kbin = (uint8_t)(KBI_Channel & 0x1f);		/*  得到KBI引脚号  */
	
	SIM->SCGC |= (kbix == 0) ? SIM_SCGC_KBI0_MASK : SIM_SCGC_KBI1_MASK;		/*  开启相应时钟  */
	
	KBIX[kbix]->SC &= ~(uint32_t)KBI_SC_KBIE_MASK;		/*  设置前先关闭中断  */
	
	/*  设置触发模式  */
	if(KBI_TrigMode == KBI_TrigFalling || KBI_TrigMode == KBI_TringFallingLow)
		KBIX[kbix]->ES &= ~((uint32_t)1 << kbin);
	else
		KBIX[kbix]->ES |= (uint32_t)1 << kbin;
	
	/*  开启上拉  */
	drv_gpio_PullCmd((GPIOPin_TypeDef)((uint8_t)kbin), ENABLE);
	
	/*  使能KBI引脚  */
	KBIX[kbix]->PE = (1 << kbin);
	
	/*  清除标志位  */
	if(kbix == 0) KBI0->SC |= KBI_SC_KBACK_MASK | KBI_SC_RSTKBSP_MASK;
	else if(kbix == 1) KBI1->SC |= KBI_SC_KBACK_MASK | KBI_SC_RSTKBSP_MASK;
	
	/*  设置触发模式  */
	if(KBI_TrigMode == KBI_TrigFalling || KBI_TrigMode == KBI_TrigRising)
		KBIX[kbix]->SC = 0;
	else 
		KBIX[kbix]->SC = KBI_SC_KBMOD_MASK;
	
	KBIX[kbix]->SC |= ( 0
										| KBI_SC_KBIE_MASK    //KBI中断使能
										| KBI_SC_RSTKBSP_MASK
										| KBI_SC_KBSPEN_MASK  //使能KBI_SP寄存器
										);
	
	if(kbix == 0) 
	{
		NVIC_EnableIRQ(KBI0_IRQn);
		NVIC_SetPriority(KBI0_IRQn, 1);
	}
	else if(kbix == 1) 
	{
		NVIC_EnableIRQ(KBI0_IRQn);
		NVIC_SetPriority(KBI1_IRQn, 2);
	}
}


void KBI0_IRQHandler(void)
{
	if(KBI0_SC & KBI_SC_KBF_MASK)
	{
		
	}
	KBI0_SC |= KBI_SC_KBACK_MASK | KBI_SC_RSTKBSP_MASK;
}

void KBI1_IRQHandler(void)
{

}



/********************************************  END OF FILE  *******************************************/

