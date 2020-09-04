#include "reg52.h"
#include "i2c.h"

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3; //定义按键端口

char num=0;
u8 disp[4];
u8 code smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void delay(u16 i)
{
    while(i--);
}
void Keypros()
{
    if(k1==0)
    {
        delay(1000); //消抖处理
        if(k1==0)
        {
            At24c02Write(1,num); //在地址1 内写入数据num
        }
        while(!k1);
    }
    if(k2==0)
    {
        delay(1000); //消抖处理
        if(k2==0)
        {
            num=At24c02Read(1); //读取EEPROM 地址1 内的数据保存在 num 中
        }
        while(!k2);
    }
    if(k3==0)
    {
        delay(100); //消抖处理
        if(k3==0)
        {
            num++; //数据加1
            if(num>255)num=0;
        }
        while(!k3);
    }
    if(k4==0)
    {
        delay(1000); //消抖处理
        if(k4==0)
        {
            num=0; //数据清零
        }
        while(!k4);
    }
}

void datapros()
{
    disp[0]=smgduan[num/1000];//千位
    disp[1]=smgduan[num%1000/100];//百位
    disp[2]=smgduan[num%1000%100/10];//个位
    disp[3]=smgduan[num%1000%100%10];
}
void DigDisplay()
{
    u8 i;
    for(i=0;i<4;i++)
    {
        switch(i) //位选，选择点亮的数码管，
        {
            case(0):
                LSA=1;LSB=1;LSC=0; break;//显示第0 位
            case(1):
                LSA=0;LSB=1;LSC=0; break;//显示第1 位
            case(2):
                LSA=1;LSB=0;LSC=0; break;//显示第2 位
            case(3):
                LSA=0;LSB=0;LSC=0; break;//显示第3 位
        }
        P0=disp[i];//发送数据
        delay(100); //间隔一段时间扫描
        P0=0x00;//消隐
    }
}

void main()
{
    while(1)
    {
        Keypros(); //按键处理函数
        datapros(); //数据处理函数
        DigDisplay();//数码管显示函数
    }
}
