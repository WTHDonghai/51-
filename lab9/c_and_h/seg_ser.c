#include <all.h>

// 数码管数据,用以显示,数组的下标表示数码管的位选
u8 seg_data_buffer[8]; 
u8 chip_idx = 0; // 位选个数

/**
 * 功能说明:
 *      初始化10进制数据
 * 参数:
 *      num: 填充的10进制数
 */
void init_dec_data(u8 num)
{
    chip_idx = 0;
    while(num)
    {
        u8 tmp = num % 10;
        num /= 10;
        seg_data_buffer[chip_idx++] = tmp;
    }
}

/*
 * 功能说明:
 *      led数码管显示数字
 * 参数:
 *      idx: 点亮数码管序列号
 *      num: 点亮的数字
 **/
void seg_dispaly()
{
    u8 i = 0;
    for(;i < chip_idx;i++)
    {
        P0=0x00;
        chip_select(i); // 位选(片选)
        segment_select(seg_data_buffer[i]); // 段选
    }
}

