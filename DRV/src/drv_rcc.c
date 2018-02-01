# include "drv_rcc.h"

/*
*********************************************************************************************************
*                               drv_rcc_ClockCmd           
*
* Description: 使能外设时钟
*             
* Arguments  : 1> PeriphColck: 外设时钟
*              2> NewState: 使能选项
*
* Reutrn     : None.
*
* Note(s)    : None.
*********************************************************************************************************
*/
void drv_rcc_ClockCmd(uint32_t PeriphColck, FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		SIM->SCGC |= PeriphColck;
	}
	else
	{
		SIM->SCGC &= ~PeriphColck;
	}
}


