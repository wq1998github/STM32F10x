#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "usart.h"

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

unsigned char rxData;

void USART1_Init(u32 bound)
{ // 串口1初始化并启动
    // GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); // 使能USART1，GPIOA时钟
                                                                                  // USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                     // PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        // 子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                           // 根据指定的参数初始化VIC寄存器
    // USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;                                     // 一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          // 一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 // 收发模式
    USART_Init(USART1, &USART_InitStructure);                                       // 初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);                                 // 开启ENABLE/关闭DISABLE中断
    USART_Cmd(USART1, ENABLE);                                                      // 使能串口
}

int main(void)
{
    uint8_t a = 0;
    usart_open_com_log(115200);
    // USART1_Init(115200);

    /* Infinite loop */
    while (1)
    {
#if (USART_RECV_MODE == 1)

        // if (usart_get_recv_flag() == 1)
        // {
        //     // printf("%02x\r\n", usart_get_recv_byte());
        //     usart_send_buffer((unsigned char*)recv_structure.recv_buff, 4);
        // }

        // 查询方式接收
        // if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
        // {                                  // 查询串口待处理标志位
        //     a = USART_ReceiveData(USART1); // 读取接收到的数据
        //     printf("%c", a);               // 把收到的数据发送回电脑
        // }

#elif (USART_RECV_MODE == 2)
        usart_poll_recv_data();

        if (recv_structure.recv_len > 0)
        {
            printf("[%d] %s\r\n", recv_structure.recv_len, recv_structure.recv_buff);
            recv_structure.recv_len = 0;
        }

#endif
    }
}
