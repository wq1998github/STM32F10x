#include <stdio.h>
#include "stm32f10x.h"
#include "usart.h"

void delay(int ms)
{
    int num = 0;
    for (int i = 0; i < 6000; i++)
    {
        for (int j = 0; j < ms; j++)
            num++;
    }
}


int main(void)
{
    usart_open_usart1(115200);

    /* Infinite loop */
    while (1)
    {
        printf("hello world...\r\n");
        delay(1000);
    }
}
