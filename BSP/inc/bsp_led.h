# ifndef __BSP_LED_H
# define __BSP_LED_H


# include "derivative.h"

# define LED_ALL			0
# define LED1					1
# define LED2					2
# define LED3					3

# define LED_ON				GPIO_PIN_SET
# define LED_OFF			GPIO_PIN_RESET

# define LED1_PORT		PORTA
# define LED2_PORT		PORTA
# define LED3_PORT		PORTA

# define LED1_PIN			GPIO_Pin_A0
# define LED2_PIN			GPIO_Pin_A1
# define LED3_PIN			GPIO_Pin_A2

void bsp_led_Config(void);
void bsp_led_ON(uint8_t LEDx);
void bsp_led_OFF(uint8_t LEDx);
void bsp_led_Toggle(uint8_t LEDx);

# endif

