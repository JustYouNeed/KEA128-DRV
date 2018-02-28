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
	
	bsp_Config();
	
	bsp_tim_CreateHardTimer(0, 200, test_Led1Test);
	bsp_tim_CreateHardTimer(1, 400, test_Led2Test);
	
	while(1)
	{
		bsp_tim_DelayMs(400);		
		cnt ++;
		
		if(cnt > 20)
		{
			bsp_tim_DeleteHardTimer(0);
			bsp_tim_DeleteHardTimer(1);
		}
	}
}

