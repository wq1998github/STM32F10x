#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "stm32f10x_conf.h"

int usart_open_usart1(uint32_t BaudRate);

#ifdef __cplusplus
}
#endif

#endif
