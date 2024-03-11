#ifndef __MY_ADC_H
#define __MY_ADC_H

#include "./SYSTEM/sys/sys.h"

//ADCѡȡDMAע���:  ADC1��ADC3֧��DMA��ADC2��֧��DMA  ADC3��DMAͨ��ֻ����DMA2_Channel5

//DMAͨ���궨��
#define ADC_DMA_CHx DMA2_Channel5 

//��������
void my_adc_nch_dma_init(uint32_t mar);
void my_adc_dma_enable(uint16_t cndtr);
uint16_t my_get_value(uint8_t n,uint8_t x,uint16_t dat[],uint16_t num);

//����������
uint8_t lsens_get_val(uint16_t lsens_analog);
uint8_t airqu_get_val(uint16_t airqu_analog);
#endif 















