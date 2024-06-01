#ifndef _USER_GPIO_H_
#define _USER_GPIO_H_

#ifdef _cplusplus
extern "C" {
#endif

#include "stm32f10x_conf.h"

/**
 * @brief  初始化 GPIO Pin
 * @param  GPIOx GPIOA ~ GPIOG
 * @param  GPIO_InitStruct 
 * @return int 1：成功，0失败
 */
int GPIOx_Open(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);

#ifdef _cplusplus
}
#endif

#endif
