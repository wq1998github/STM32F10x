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

int main(void)
{
    usart_open_com_log(115200);

    /* Infinite loop */
    while (1)
    {
#if (USART_RECV_MODE == 1)

        if (usart_get_recv_flag() == 1)
        {
            printf("%02x\r\n", usart_get_recv_byte());
        }

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
