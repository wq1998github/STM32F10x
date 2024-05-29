#include "usart.h"

int fputc(int ch, FILE* f)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

    USART_SendData(USART1, (u8)ch);
    return ch;
}

#if 1
int usart_open_usart1(uint32_t BaudRate /*, uint16_t WordLength, uint16_t StopBits, uint16_t Parity, uint16_t Mode*/)
{
    GPIO_InitTypeDef GPIOx = {0};
    USART_InitTypeDef USARTx = {0};
    NVIC_InitTypeDef NVIC_InitStruct = {0};

    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // 引脚初始化
    GPIOx.GPIO_Pin = GPIO_Pin_9; //USART1 -- TX
    GPIOx.GPIO_Mode = GPIO_Mode_AF_PP; //发送，输出引脚，所以配置为推挽输出
    GPIOx.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIOx);

    GPIOx.GPIO_Pin = GPIO_Pin_10; // USART1 -- RX
    GPIOx.GPIO_Mode = GPIO_Mode_IN_FLOATING; //接收，输入引脚，读取对端的高低电平变化
    GPIOx.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIOx);

    // 串口参数初始化
    USARTx.USART_BaudRate = BaudRate;
#if 0
    USARTx.USART_WordLength = WordLength;
    USARTx.USART_StopBits = StopBits;
    USARTx.USART_Parity = Parity;
    USARTx.USART_Mode = Mode;
#else
    USARTx.USART_WordLength = USART_WordLength_8b;
    USARTx.USART_StopBits = USART_StopBits_1;
    USARTx.USART_Parity = USART_Parity_No;
    USARTx.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USARTx.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
#endif
    USART_Init(USART1, &USARTx);

    // NVIC初始化
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0xF;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0xF;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 开启USART1的接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // 开启USART1
    USART_Cmd(USART1, ENABLE);
		
	return 0;
}
#else
int usart_open_usart1(uint32_t BaudRate /*, uint16_t WordLength, uint16_t StopBits, uint16_t Parity, uint16_t Mode*/)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    USART_InitTypeDef USART_InitStruct = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = BaudRate;                                  // 波特率
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件控制流
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 // 收发模式
    USART_InitStruct.USART_Parity = USART_Parity_No;                             // 不使用奇偶校验
    USART_InitStruct.USART_StopBits = USART_StopBits_1;                          // 一位停止位
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;                     // 八位的数据长度
    USART_Init(USART1, &USART_InitStruct);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 使能接收中断
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); // 使能空闲中断

    //	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //	NVIC_InitStruct.NVIC_IRQChannel    = USART1_IRQn;		//中断源
    //	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			//使能中断源
    //	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2
    //	NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 2;	//响应优先级2
    //	NVIC_Init(&NVIC_InitStruct);

    USART_Cmd(USART1, ENABLE); // 使能外设

    return 0;
}
#endif


