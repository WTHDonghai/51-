/**
 * 外部中断实验
 * 通过k3触发外部中断0，开关led灯
 */

#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

// 设置数码管编码
u8 code smgduan[16] = {
    0x3F/*0*/,0x06/*1*/,0x5B/*2*/,0x4F/*3*/,
    0x66/*4*/,0x6D/*5*/,0x7D/*6*/,0x07/*7*/,
    0x7F/*8*/,0x6F/*9*/,0x77/*A*/,0x7C/*B*/,
    0x39/*C*/,0x5E/*D*/,0x79/*E*/,0x71/*F*/
};

u8 smgduan_len = sizeof(smgduan) / sizeof(smgduan[0]);

sbit led = P2^0;

// P3.2管脚连接独立按键k3,触发外部中断INT0
sbit key3 = P3^2;

void init_interrupt(void);
void display_digital(u8,u8);
void delay(u16);

void main(void)
{
    u8 num_idx = 0;

    init_interrupt();
    while(1)
    {
        delay(10000);
        if(num_idx++ > smgduan_len - 1) num_idx = 0;
        display_digital(0,num_idx);
    }
}

/**
 * 外部中断设置初始化
 **/
void init_interrupt(void)
{
    // 设置cpu中断允许寄存器开放中断使能
    EX0 = 1; // 打开INTO的中断允许

    EA = 1; // 打开中断总开关

    IT0 = 1; // 设置跳变沿触发方式
}

void Key3_Int0() interrupt 0
{
    delay(1000);
    led = ~led;
    delay(10000);
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


