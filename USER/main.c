# include "drv_gpio.h"
# include "bsp_uart.h"
# include "bsp_timer.h"

int main(void)
{	
	bsp_tim_SoftConfig();
	bsp_uart_Init();
	
	while(1)
	{
		bsp_tim_DelayMs(100);
		bsp_uart_Printf("Hello World\r\n");
	}
}

