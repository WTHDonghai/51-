#ifndef seg_ser
#define seg_ser

extern void seg_dispaly(); // 数码管显示
extern void init_dec_data(u8 num); // 初始化10进制数据
extern u8 seg_data_buffer[8]; // 数码管数据缓存

#endif

