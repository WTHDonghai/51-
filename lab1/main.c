#include "reg52.h"
#include <intrins.h>

#define LED P2

typedef unsigned int u16;
typedef unsigned char u8;

/**
 * 实验1:点亮发光二极管
 *
 */
sbit led0 = P2^0;
void delay(u16);

void main(void)
{
    
    u16 delay_u_sec; // 延时变量
    int i;
     while(1)
     {
        LED = ~0x01; // 0xfe
        delay_u_sec = 50000;
        for(i = 0; i < 8; i++)
        {
            LED = ~(0x01<<i);
            delay(delay_u_sec);
        }
     }
     
}


/**
 * i = 1,大约延时10us
 */
void delay(u16 i)
{
    while(i--);
}
