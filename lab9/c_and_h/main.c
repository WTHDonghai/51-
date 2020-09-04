#include <all.h>

void init_interrupt(void);
void seg_data_allow(); // 数码管服务数据分配

u16 ms = 0; // 毫秒计数器
u8 se = 0; // 秒计数器
u8 min = 0; // 分计数器
u8 hour = 0; // 时计数器

u16 segNum = 0; // 数码管显示的数据

void main(void)
{
    init_interrupt();
    while(1)
    {
        seg_data_allow();
        seg_dispaly();
    }
}

/**
 * 数码管数据分配
 */
void seg_data_allow()
{
    init_dec_data(segNum++);
    while(se % 10 == 0);
}

/**
 * 1秒任务
void sec_task()
{
}
void ms_task()
{
    static u16 i = ms;
}
*/


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
    // 16位计时器初值设置 = 65535 -1000 + 1;
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

    //ms_task();
    if (++ms%1000 == 0) 
    {
        ms = 0;
        //sec_task();
        if(++se%60 == 0)
        {
            se = 0;
            if(++min%60==0)
            {
                min = 0;
            }
        }
    }
}



