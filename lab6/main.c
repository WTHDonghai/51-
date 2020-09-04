/**
 * 定时器中断实验
 * 秒表计时
 */
#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

void init_interrupt(void);
void task_1ms();
void fill_digital_led(u8*,u16,u8);
void delay(u8);
void display_digital_led(u8*);

u16 ms = 0; // 毫秒数
u16 se = 0; // 秒数
u16 mi = 0; // 分钟数
u16 hou = 0; // 小时数

// 设置数码管编码
u8 code smgduan[17] = {
    0x3F/*0*/,0x06/*1*/,0x5B/*2*/,0x4F/*3*/,
    0x66/*4*/,0x6D/*5*/,0x7D/*6*/,0x07/*7*/,
    0x7F/*8*/,0x6F/*9*/,0x77/*A*/,0x7C/*B*/,
    0x39/*C*/,0x5E/*D*/,0x79/*E*/,0x71/*F*/,
    0x40/*-*/
};

void main(void)
{
    init_interrupt();
    while(1)
    {
        u8 time[8] = { 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f };
        fill_digital_led(time,hou,1);
        time[2] = smgduan[16];
        fill_digital_led(time,mi,4);
        time[5] = smgduan[16];
        fill_digital_led(time,se,7);
        display_digital_led(time);
    }
}

/**
 * 定时器中断初始化
 */
void init_interrupt(void)
{

    EA = 1; // 打开中断总开关
    ET0 = 1; // 定时器0中断使能

    // 设置定时器允许方式1
    TMOD |= 0x01; 

    // th0 tl0赋初始值,1ms
    // 1个机器周期等于12个震荡周期，震荡周期为1/12MHZ; 1us = 12 * 1/12;
    // 1ms = 1000 * 1us
    // 16位计时器初值设置 = 65536 - 1000 + 1
    TH0 = 0XFC;
    TL0 = 0x18;

    TR0=1; // 打开计时器开始计时
}

/**
 * 定时器0中断方法
 * */
void time0() interrupt 1
{
    TH0 = 0XFC;
    TL0 = 0x18;
    task_1ms();
}

/**
 * 1毫秒执行任务
 */
void task_1ms(void)
{
    if(++ms%1000 == 0)
    {
        ms = 0;
        if (++se%60 == 0)
        {
            se = 0;
            if(++mi%60 == 0)
            {
                mi = 0;
                if(++hou%60 == 0)
                {
                    hou = 0;
                }
            }
        }
    }
}

/**
 * 填充数码管显示的字符
 * 参数: 
 *  n指定点亮第几个数码管,从0开始计数
 *  num指定显示数字，从0开始计数
 */
void fill_digital_led(u8 *arr, u16 num,u8 idx)
{
    u8 flag = 1;
    while(flag)
    {
        u8 num_pos = num%10;
        num /= 10;

        arr[idx--]=smgduan[num_pos];
        flag = num;
    }
}

/**
 * 延时函数
 */
void delay(u8 us)
{
    while(us--);
}

/**
 * 显示数码管
 */
void display_digital_led(u8* arr)
{
    char i,idx;
    P2 = 0xFF;
    P0 = arr[0];
    idx = 0;
    for(i=-5; i >= -33; )
    {           
        P0 = arr[idx++];
        delay(100);
        P0 = 0x0;

        P2 = i;
        i = i - 4;
        if(idx > 16)idx = 0;
    }
}

