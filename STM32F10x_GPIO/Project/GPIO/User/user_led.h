#ifndef _USER_LED_H_
#define _USER_LED_H_

#ifdef _cplusplus
extern "C" {
#endif

#include "stm32f10x_conf.h"
#include "user_gpio.h"

#define GPIO_LED_GROUP  GPIOC
#define GPIO_LED_PIN    GPIO_Pin_13

typedef enum
{
    LED_State_OFF = 0,
    LED_State_ON = 1,
} LED_State_Typedef;

/**
 * @brief  初始化 LED
 */
void LED_init(void);

/**
 * @brief  控制 LED 灯的亮灭
 * @param  mode LED_State_OFF: power off; LED_State_ON: power on
 */
void LED_switch(LED_State_Typedef mode);

#ifdef _cplusplus
}
#endif

#endif
