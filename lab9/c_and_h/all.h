#ifndef all
#define all
#include <reg52.h>

typedef unsigned char u8;
typedef unsigned int u16;

extern u16 ms; // 毫秒
extern u8 se; // 秒
extern u8 min; // 分
extern u8 hour; // 时

#include <HC245_drive.h>
#include <HC138_drive.h>
#include <seg_ser.h>
#include <intrins.h>

#endif
