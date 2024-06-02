#include <stdio.h>
#include "stm32f10x.h"
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

int main(void)
{
    char str1[128] = {0};
    char str2[128] = {0};

    sprintf(str1, "hello world in line%d\r\n", __LINE__);

    snprintf(str2, sizeof(str2), "hello world in line%d\r\n", __LINE__);

    usart_open_com_log(115200);

    /* Infinite loop */
    while (1)
    {
        printf("hello world in line%d\r\n", __LINE__);

        usart_printf("hello world in line%d\r\n", __LINE__);

        // 注意串口助手也要是 UTF-8 编码
        printf("你好世界\r\n");

#if 1
        usart_send_string(str1);

        usart_send_string2(str2);

        usart_send_byte('1');
        usart_send_byte('\x32');
        usart_send_byte(0x33);
        usart_send_byte('\r');
        usart_send_byte('\n');
#endif

        delay_ms(1000);
    }
}
