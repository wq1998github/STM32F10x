/**
 ******************************************************************************
 * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
 * @author  MCD Application Team
 * @version V3.6.0
 * @date    20-September-2021
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2011 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

#if 0
#include <stdio.h>
void USART1_IRQHandler(void)
{ // 串口1中断服务程序（固定的函数名不能修改）
    u8 a;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {                                  // 接收中断(接收到的数据必须是0x0d 0x0a结尾)
        a = USART_ReceiveData(USART1); // 读取接收到的数据
        printf("%c", a);               // 把收到的数据发送回电脑
    }
}
#else
#include "usart.h"

/**
 * @brief  这部分代码的处理是有问题的，实际运行起来会出现丢数据、错位等问题
 */
void USART1_IRQHandler(void)
{
    static unsigned char recv_fsm = 0x01;
    unsigned char recv_tmp = 0;

    if (USART_GetFlagStatus(USART_LOG, USART_IT_RXNE) != RESET)
    {
        recv_tmp = USART_ReceiveData(USART_LOG);
        printf("recv: %02x\r\n", recv_tmp);

        switch (recv_fsm)
        {
        case 0x01:
            if (recv_tmp == 0xFF)
            {
                recv_fsm = 0x02;
                recv_structure.recv_len = 0;
            }
            else
            {
                recv_fsm = 0x01;
            }
            break;

        case 0x02:
            recv_structure.recv_buff[recv_structure.recv_len] = recv_tmp;
            recv_structure.recv_len++;

            if (recv_structure.recv_len >= 4)
            {
                recv_fsm = 0x03;
            }
            break;

        case 0x03:
            if (recv_tmp == 0xFE)
            {
                recv_structure.recv_flag = 1;
                recv_tmp = 0x01;
            }
            else
            {
                // recv_structure.recv_len = 0;
            }

            // recv_fsm = 0x01;
            break;

        default:

            break;
        }

        // recv_structure.recv_len++;
        // recv_structure.recv_flag = 1;

        // 读取DR寄存器可以自动清除标志位，但其实手动清除标志位也没有什么影响
        USART_ClearITPendingBit(USART_LOG, USART_IT_RXNE);
    }
}
#endif
