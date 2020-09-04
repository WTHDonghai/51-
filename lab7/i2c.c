/**
 * ic2串口协议实验
 * 将数据持久写入24c02芯片上
 * 在通过独立按键读写数据
 */

#include "i2c.h"


void init_interrupt(void); // 定时器中断初始化
void task_10mil(void); // 10微秒任务

u16 umil = 0; // 微秒数

/**
 * 延时10us
 */
void delay10us(void)
{
    u8 a,b;
    for(b = 1; b>0;b--)
        for(a = 2; a > 0; a--);
}

void i2cStart(void)
{
    SDA = 1;
    delay10us();
    SCL = 1;
    delay10us();
    SCL = 0;
    delay10us();
    SCL = 0;
    delay10us();
}

u8 i2cSend(u8 dat)
{
    u8 a=0,b=0;
    for(a = 0; a < 8; a++)
    {
        SDA = dat >> 7;
        dat = dat << 1;
        SCL = 1;
        delay10us();
        SCL = 0;
        delay10us();
    }
    SDA = 1;
    delay10us();
    SCL = 1;
    while(SDA) //  等待应答
    {
        b++;
        if (b > 200)  
        {
            SCL = 0;
            delay10us();
            return 0;
        }
    }
    SCL = 0;
    delay10us();
    return 1;
}

u8 i2cRead()
{
    u8 a = 0, dat = 0;
    SDA = 1;
    delay10us();
    for(a = 0; a < 8; a++)
    {
        SCL = 1;
        delay10us();
        dat<<=1;
        dat|=SDA;
        delay10us();
        SCL=0;
        delay10us();
    }
    return dat;
}

void At24c02Write(u8 addr,u8 dat)
{
    i2cStart();
    i2cSend(0xa0);//发送写器件地址
    i2cSend(addr);//发送要写入内存地址
    i2cSend(dat); //发送数据
    i2cStop();
}

u8 At24c02Read(u8 addr)
{
    u8 num;
    i2cStart();
    i2cSend(0xa0); //发送写器件地址
    i2cSend(addr); //发送要读取的地址
    i2cStart();
    i2cSend(0xa1); //发送读器件地址
    num=i2cRead(); //读取数据
    i2cStop();
    return num;
}


/**
 * i2c传输结束
 */
void i2cStop(void)
{
    SDA = 0;
    delay10us();
    SCL = 1;
    delay10us();
    SDA = 1;
    delay10us();
}



