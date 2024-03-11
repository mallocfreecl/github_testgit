#ifndef __MY_ADC_H
#define __MY_ADC_H

#include "./SYSTEM/sys/sys.h"

//ADC选取DMA注意点:  ADC1和ADC3支持DMA，ADC2不支持DMA  ADC3的DMA通道只能是DMA2_Channel5

//DMA通道宏定义
#define ADC_DMA_CHx DMA2_Channel5 

//函数声明
void my_adc_nch_dma_init(uint32_t mar);
void my_adc_dma_enable(uint16_t cndtr);
uint16_t my_get_value(uint8_t n,uint8_t x,uint16_t dat[],uint16_t num);

//传感器函数
uint8_t lsens_get_val(uint16_t lsens_analog);
uint8_t airqu_get_val(uint16_t airqu_analog);
#endif 















