#include <all.h>

/**
 * 数据分配
 */
void HC595_Allot()
{
    static u8 count = 0;
    /*
     * 计数控制。
     * 抽离出main方法中可以单独控制，
     * 避免main方法中编写一堆if判断方法
     * */
    if (count++ > 250) 
    {
        count = 0;
        HC595_Wirte_Buffer[1] = 0xf0;
        HC595_Init();
    }
}

void main(void)
{
    // HC595_Wirte_Buffer[1] = 0xf0;
    // HC595_Init();
    
    while(1) 
    {
        HC595_Allot();
    }
}

