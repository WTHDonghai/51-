/**
 * 独立按键实验
 */
#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

void display_digital(u8,u8);
void delay(u16);

sbit key1 = P3^1;

// 设置数码管编码
u8 code smgduan[16] = {
    0x3F/*0*/,0x06/*1*/,0x5B/*2*/,0x4F/*3*/,
    0x66/*4*/,0x6D/*5*/,0x7D/*6*/,0x07/*7*/,
    0x7F/*8*/,0x6F/*9*/,0x77/*A*/,0x7C/*B*/,
    0x39/*C*/,0x5E/*D*/,0x79/*E*/,0x71/*F*/
};

u8 smgduan_len = sizeof(smgduan) / sizeof(smgduan[0]);

void main(void)
{
    
    u8 num;
    num = 0;
    display_digital(0,num);
    while(1)
    {
        if(key1 == 0)
        {
            delay(10000);
            num++;
            if(num > smgduan_len - 1) num = 0; 
            delay(10000);
            while(!key1);
            display_digital(0,num);
        }
    }
}

/**
 * 显示指定单个数码管
 * 参数: 
 *  n指定点亮第几个数码管,从0开始计数
 *  num指定显示数字，从0开始计数
 */
void display_digital(u8 n,u8 num)
{
    u8 idx = 0xff - (n * 4);
    P2 &= idx;
    P0 = smgduan[num];
}

void delay(u16 us)
{
    while(us--);
}
