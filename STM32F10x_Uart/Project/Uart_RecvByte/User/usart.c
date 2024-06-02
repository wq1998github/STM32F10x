#include "usart.h"
#include <string.h>
#include <stdarg.h>


/**
 * @note 注意使用这种方式移植printf函数，只能重定向到一个串口，其他串口是没办法使用printf函数的
 */
int fputc(int ch, FILE* f)
{
#if 0
    // 这个 while 循环是为了保证后面发送的数据不会把前面发送的数据覆盖掉
    while(USART_GetFlagStatus(USART_LOG, USART_FLAG_TC) == RESET);
    USART_SendData(USART_LOG, (u8)ch);
#else
    USART_SendData(USART_LOG, (u8)ch);
    while (USART_GetFlagStatus(USART_LOG, USART_FLAG_TXE) == RESET);
#endif
    return ch;
}

#if 1
int usart_open_com_log(uint32_t BaudRate /*, uint16_t WordLength, uint16_t StopBits, uint16_t Parity, uint16_t Mode*/)
{
    GPIO_InitTypeDef GPIOx = {0};
    USART_InitTypeDef USARTx = {0};

#if (USART_RECV_MODE == 1)
    NVIC_InitTypeDef NVIC_InitStruct = {0};
#endif

    // 开启时钟
#if (USART_LOG_SELECT == 1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_Periph_GPIOx | RCC_Periph_USARTx, ENABLE);
#elif (USART_LOG_SELECT == 2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_Periph_GPIOx, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_Periph_USARTx, ENABLE);
#elif (USART_LOG_SELECT == 3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_Periph_GPIOx, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_Periph_USARTx, ENABLE);
#endif

    // 引脚初始化
    GPIOx.GPIO_Pin = USART_LOG_TX_PIN; // USART -- TX
    GPIOx.GPIO_Mode = GPIO_Mode_AF_PP; //发送，输出引脚，所以配置为推挽输出
    GPIOx.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_LOG_GPIOx, &GPIOx);

    // 输入引脚一般配置为浮空输入和上拉输入（因为引脚空闲状态是高电平）
    GPIOx.GPIO_Pin = USART_LOG_RX_PIN; // USART -- RX
    GPIOx.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 接收，输入引脚，读取对端的高低电平变化
    // GPIOx.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_LOG_GPIOx, &GPIOx);

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
#endif
    USARTx.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流控
    
    USART_Init(USART_LOG, &USARTx);

    // 开启USART
    USART_Cmd(USART_LOG, ENABLE);

#if (USART_RECV_MODE == 1)
    // 开启USART的接收中断
    USART_ITConfig(USART_LOG, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // NVIC初始化
    NVIC_InitStruct.NVIC_IRQChannel = USART_LOG_IRQN;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
#endif

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

void usart_send_byte(unsigned char byte)
{
    USART_SendData(USART_LOG, byte);
    while (USART_GetFlagStatus(USART_LOG, USART_FLAG_TXE) == RESET)
    {
        // do nothing
    }
}

void usart_send_string(char *str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        usart_send_byte(str[i]);
    }
}

void usart_send_string2(char *str)
{
    for (int i = 0; str[i] != '\0' ; i++)
    {
        usart_send_byte(str[i]);
    }
}

void usart_printf(char* format, ...)
{
    char tmp[100] = {0};

    va_list arg;
    va_start(arg, format);
    vsprintf(tmp, format, arg); //注意这里可能会出现溢出问题
    va_end(arg);

    usart_send_string2(tmp);
}

USART_RECV_TypeDef recv_structure = {0};

#if (USART_RECV_MODE == 1)

unsigned char usart_get_recv_flag(void)
{
    unsigned char ret = recv_structure.recv_flag;

    if (recv_structure.recv_flag == 1)
    {
        recv_structure.recv_flag = 0;
        recv_structure.recv_len = 0;
    }

    return ret;
}

unsigned char usart_get_recv_byte(void)
{
    return recv_structure.recv_buff[0];
}

char* usart_get_recv_string(void)
{
    return (char*)recv_structure.recv_buff;
}

#if 0
void USART1_IRQHandler(void)
{
    if (USART_GetFlagStatus(USART_LOG, USART_IT_RXNE) == SET)
    {
        recv_structure.recv_buff[0] = USART_ReceiveData(USART_LOG);
        recv_structure.recv_flag = 1;

        // 读取DR寄存器可以自动清除标志位，但其实手动清除标志位也没有什么影响
        USART_ClearITPendingBit(USART_LOG, USART_IT_RXNE);
    }
}
#endif

#elif (USART_RECV_MODE == 2)

// 查询的方式有问题，发送字符串 "12345" ，结果只收到 "12"，应该有哪里没配置好
int usart_poll_recv_data(void)
{
    // 这里其实应该用队列的，只是图省事 ~
    if (USART_GetFlagStatus(USART_LOG, USART_FLAG_RXNE) == SET)
    {
        recv_structure.recv_buff[recv_structure.recv_len] = (unsigned char)USART_ReceiveData(USART_LOG);
        recv_structure.recv_len = ++recv_structure.recv_len < sizeof(recv_structure.recv_buff) ? recv_structure.recv_len : 0;
    }

    return recv_structure.recv_len;
}

#endif
