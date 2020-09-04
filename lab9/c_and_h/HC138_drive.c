#include <all.h>

sbit LCA = P2^2;
sbit LCB = P2^3;
sbit LCC = P2^4;

/**
 * 功能说明:
 *      根据传入片选值控制片选信号Y0 ~ Y7电平
 * 参数:
 *      idx: 片选值 
 */

void chip_select(u8 idx)
{
    //P2 = 11 101 111 Y5送入低电平
    LCA = idx & 0x1;
    LCB = _cror_(idx,1) & 0x1;
    LCC = _cror_(idx,2) & 0x1;
}


