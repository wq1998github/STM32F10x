#include "user_led.h"

void LED_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin = GPIO_LED_PIN;

    GPIOx_Open(GPIO_LED_GROUP, &GPIO_InitStruct);
}

static void LED_power_on(void)
{
    GPIO_SetBits(GPIO_LED_GROUP, GPIO_LED_PIN);
}

static void LED_power_off(void)
{
    GPIO_ResetBits(GPIO_LED_GROUP, GPIO_LED_PIN);
}

void LED_switch(LED_State_Typedef mode)
{
    if (mode == LED_State_OFF)
    {
        LED_power_off();
    }
    else if (mode == LED_State_ON)
    {
        LED_power_on();
    }
    else
    {
        // do nothing
    }
}
