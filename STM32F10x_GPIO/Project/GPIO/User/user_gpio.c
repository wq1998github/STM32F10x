#include "user_gpio.h"

int GPIOx_Open(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    ErrorStatus ret = ERROR;
    unsigned int RCC_APB2Periph_GPIOx = 0x00000000;

    if (GPIOx == GPIOA)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOA;
    }
    else if (GPIOx == GPIOB)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOB;
    }
    else if (GPIOx == GPIOC)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOC;
    }
    else if (GPIOx == GPIOD)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOD;
    }
    else if (GPIOx == GPIOE)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOE;
    }
    else if (GPIOx == GPIOF)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOF;
    }
    else if (GPIOx == GPIOG)
    {
        RCC_APB2Periph_GPIOx = RCC_APB2Periph_GPIOG;
    }

    if (RCC_APB2Periph_GPIOx > 0)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);
        GPIO_Init(GPIOx, GPIO_InitStruct);

        ret = SUCCESS;
    }

    return (int)ret;
}
