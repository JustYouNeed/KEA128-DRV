# include "drv_rcc.h"

/*
*********************************************************************************************************
*                               drv_rcc_ClockCmd           
*
* Description: ʹ������ʱ��
*             
* Arguments  : 1> PeriphColck: ����ʱ��
*              2> NewState: ʹ��ѡ��
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


