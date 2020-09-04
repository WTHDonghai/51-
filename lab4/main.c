/**
 * 矩阵键盘实验
 */

#include <reg52.h>

#define GPIO_DIG P0
#define GPIO_KEY P1

typedef unsigned int u16;
typedef unsigned char u8;

u8 KEY_VALUE; // 用来存放读取到的键值

void display_digital(u8,u8);
void delay(u16);
void key_down(void);
void my_key_down(void);

// 设置数码管编码
u8 code smgduan[16] = {
    0x3F/*0*/,0x06/*1*/,0x5B/*2*/,0x4F/*3*/,
    0x66/*4*/,0x6D/*5*/,0x7D/*6*/,0x07/*7*/,
    0x7F/*8*/,0x6F/*9*/,0x77/*A*/,0x7C/*B*/,
    0x39/*C*/,0x5E/*D*/,0x79/*E*/,0x71/*F*/
};

u8 smgduan_len = sizeof(smgduan) / sizeof(smgduan[0]);

u8 led_idx , led_num , f;

void main(void)
{

    while(1)
    {
        key_down();
        GPIO_DIG=smgduan[KEY_VALUE];
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
 * 演示函数10000大约1ms
 * */
void delay(u16 us)
{
    while(us--);
}


void key_down(void)
{
    col = 0,row = 0;

    GPIO_KEY = 0x0f; // 给低4位送高电平,低四位控制列，高四位控制行

    if(GPIO_KEY!=0x0f)
    {
        delay(10000); // 消除抖动
        if (GPIO_KEY!=0x0f) // 再次检查按键是否被按下
        {

            // 测试列
            GPIO_KEY=0x0f;
            switch(GPIO_KEY)
            {
                case(0x07): KEY_VALUE = 0; break;
                case(0x0b): KEY_VALUE = 1; break;
                case(0x0d): KEY_VALUE = 2; break;
                case(0x0e): KEY_VALUE = 3; break;
            }

            //测试行
            GPIO_KEY=0xf0;
            switch(GPIO_KEY)
            {
                case(0x70): KEY_VALUE = KEY_VALUE; break;
                case(0xb0): KEY_VALUE = KEY_VALUE+4; break;
                case(0xd0): KEY_VALUE = KEY_VALUE+8; break;
                case(0xe0): KEY_VALUE = KEY_VALUE+12; break;
            }
        }
    }

    delay(1000);
}


