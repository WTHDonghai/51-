#ifndef __I2C_H__
#define __I2C_H__
#include <reg52.h>

sbit SCL = P2^1;
sbit SDA = P2^0;


typedef unsigned int u16;
typedef unsigned char u8;

void delay10us();
void i2cStart(void); // i2c开始
void i2cStart2(void);
void i2cStop(void); // i2c结束
u8 i2cSend(u8); // i2c传输
void At24c02Write(u8 ,u8);
u8 At24c02Read(u8);
u8 i2cRead(void);

#endif 
