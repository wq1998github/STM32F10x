#include <stdio.h>
#include "stm32f10x.h"
// #include "stm32f10x_rcc.h"
// #include "stm32f10x_gpio.h"
#include "user_gpio.h"
#include "user_led.h"

/**
 * @brief  软件模拟延时，并不准确，只是简单模拟一下延时 ~
 * @param  ms 
 */
void delay_ms(int ms)
{
    unsigned short index = 0;

    for (; ms > 0; ms--)
    {
        for (index = 0; index < 10000; index++)
        {
            // do nothing
        }
    }
}

int main(void)
{
    LED_init();

    /* Infinite loop */
    while (1)
    {
        LED_switch(LED_State_ON);
        delay_ms(1000);
        LED_switch(LED_State_OFF);
        delay_ms(1000);
    }
}
