#include <all.h>

code u8 SEG_NUM_CODE[18] = { // 数字编码
    0x3F/*0*/,0x06/*1*/,0x5B/*2*/,0x4F/*3*/,
    0x66/*4*/,0x6D/*5*/,0x7D/*6*/,0x07/*7*/,
    0x7F/*8*/,0x6F/*9*/,0x77/*A*/,0x7C/*B*/,
    0x39/*C*/,0x5E/*D*/,0x79/*E*/,0x71/*F*/,
    0x01/*.*/,0x40/*-*/
};

/*
 * 功能说明:
 *      根据传入段选值控制段选信号 a ~ g,dp
 * 参数:
 *      显示的数字
 */
void segment_select(u8 num)
{
    P0 = SEG_NUM_CODE[num];
}

