# include "bsp.h"


void bsp_Config(void)
{
	bsp_tim_SoftConfig();
	bsp_uart_Config();
	bsp_oled_Config();
	bsp_led_Config();
	ENABLE_INT();
}

