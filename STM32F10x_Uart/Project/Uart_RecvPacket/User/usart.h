#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "stm32f10x_conf.h"


/**
 * @brief  选择串口接收的模式，1是中断，2是轮询
 */
#define USART_RECV_MODE     1

/**
 * @brief 选择哪个串口作为日志输出口
 */
#define USART_LOG_SELECT    1


/**
 * @brief 日志口相关参数
 */
#if (USART_LOG_SELECT == 1)

// USART1 的相关配置
#define USART_LOG_GPIOx     GPIOA
#define USART_LOG_TX_PIN    GPIO_Pin_9 
#define USART_LOG_RX_PIN    GPIO_Pin_10

#define USART_LOG_IRQN      USART1_IRQn

#define RCC_Periph_GPIOx    RCC_APB2Periph_GPIOA
#define RCC_Periph_USARTx   RCC_APB2Periph_USART1

#define USART_LOG           USART1

#elif (USART_LOG_SELECT == 2)

// USART1 的相关配置
#define USART_LOG_GPIOx     GPIOA
#define USART_LOG_TX_PIN    GPIO_Pin_2
#define USART_LOG_RX_PIN    GPIO_Pin_3

#define USART_LOG_IRQN      USART2_IRQn

#define RCC_Periph_GPIOx    RCC_APB2Periph_GPIOA
#define RCC_Periph_USARTx   RCC_APB1Periph_USART2

#define USART_LOG           USART2

#elif (USART_LOG_SELECT == 3)

// USART3 的相关配置
#define USART_LOG_GPIOx     GPIOB
#define USART_LOG_TX_PIN    GPIO_Pin_10
#define USART_LOG_RX_PIN    GPIO_Pin_11

#define USART_LOG_IRQN      USART3_IRQn

#define RCC_Periph_GPIOx    RCC_APB2Periph_GPIOB
#define RCC_Periph_USARTx   RCC_APB1Periph_USART3

#define USART_LOG           USART3

#endif

/**
 * @brief 串口编号，STM32F103C8T6有三个串口
 */
typedef enum
{
    USART_COM_1 = 1,
    USART_COM_2,
    USART_COM_3,
    USART_COM_MAX = 3,
} USART_COM_Type;


typedef struct
{
    unsigned char recv_buff[512];
    unsigned long recv_len;
    unsigned char recv_flag;
} USART_RECV_TypeDef;

extern USART_RECV_TypeDef recv_structure;

/**
 * @brief  打开日志输出口
 * @param  BaudRate 波特率
 * @return int 固定为0
 */
int usart_open_com_log(uint32_t BaudRate);

/**
 * @brief  发送一个字节的数据
 * @param  byte 字节数据
 */
void usart_send_byte(unsigned char byte);

/**
 * @brief  发送buffer
 * @param  buffer 
 * @param  len 
 */
void usart_send_buffer(unsigned char *buffer, int len);

/**
 * @brief  发送一个字符串
 * @param  str 字符串
 */
void usart_send_string(char* str);

/**
 * @brief  发送一个字符串
 * @param  str 字符串
 */
void usart_send_string2(char *str);

/**
 * @brief  不使用微库的printf，注意可能会出现溢出问题
 * @param  format 
 * @param  ... 
 */
void usart_printf(char *format, ...);

/**
 * @brief  查询方式的串口接收
 * @return int 当前接收缓冲区的长度
 */
int usart_poll_recv_data(void);

unsigned char usart_get_recv_flag(void);

unsigned char usart_get_recv_byte(void);

char* usart_get_recv_string(void);

#ifdef __cplusplus
}
#endif

#endif
