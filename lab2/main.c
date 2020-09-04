/**
 * 显示数码管
 */
#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

void delay(u16);
void display_all_digital();
void display_digital(u8,u8);

// 设置片选锁存器74HC138D
sbit sc_A = P2^2;
sbit sc_B = P2^3;
sbit sc_C = P2^4;

// 设置数码管编码
u8 code smgduan[16] = {
    0x3F/*0*/,0x06/*1*/,0x5B/*2*/,0x4F/*3*/,
    0x66/*4*/,0x6D/*5*/,0x7D/*6*/,0x07/*7*/,
    0x7F/*8*/,0x6F/*9*/,0x77/*A*/,0x7C/*B*/,
    0x39/*C*/,0x5E/*D*/,0x79/*E*/,0x71/*F*/
};

// 计算出第几个数码管 0xff - (n * 4)

void main(void)
{
    while(1)
    {
        // display_all_digital();
        display_digital(2,15);
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

/**
 * 显示所有的数码管
 */
void display_all_digital(void)
{

    // 选中第一个数码管
    /*
    sc_A = 0x01;
    sc_B = 0x00; 
    sc_C = 0x01; 
    P0 = smgduan[0];
    */
    char i,idx;
    P2 = 0xFF;
    P0 = smgduan[0];
    idx = 0;
    for(i=-5; i >= -33; )
    {           
        P0 = smgduan[idx++];
        delay(100);
        P0 = 0x0;
        P2 = i;
        i = i - 4;
        if(idx > 16)idx = 0;
    }
}

void delay(u16 us)
{
    while(us--);
}
