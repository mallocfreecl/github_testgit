#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ADC及引脚 定义 */
#define ADC_ADCX                            ADC3
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC3_CLK_ENABLE(); }while(0)   /* ADC1 时钟使能 */

/* ADC单通道/多通道 DMA采集 DMA及通道 定义
 * 注意: ADC1的DMA通道只能是: DMA1_Channel1, 因此只要是ADC1, 这里是不能改动的
 *       ADC2不支持DMA采集
 *       ADC3的DMA通道只能是: DMA2_Channel5, 因此如果使用 ADC3 则需要修改  注意DMA2的通道4和5用一个中断  
 *       
 */
#define ADC_ADCX_DMACx                      DMA2_Channel5
#define ADC_ADCX_DMACx_IRQn                 DMA2_Channel4_5_IRQn
#define ADC_ADCX_DMACx_IRQHandler           DMA2_Channel4_5_IRQHandler

#define ADC_ADCX_DMACx_IS_TC()              (DMA2->ISR & (17 << 1))    /* 判断 DMA2_Channel5 传输完成标志, 这是一个假函数形式,
                                                                          * 不能当函数使用, 只能用在if等语句里面                                                                       */
#define ADC_ADCX_DMACx_CLR_TC()             do{ DMA2->IFCR |= 17 << 1; }while(0) /* 清除 DMA2_Channel5 传输完成标志 */

//函数声明

void adc_dma_enable( uint16_t cndtr);                          /* 使能一次ADC DMA采集传输 */
void adc_nch_dma_init(uint32_t mar);                           /* ADC多通道 DMA采集初始化 */
void adc_get_value(uint16_t* dat,uint8_t n);

//可能需要改的地方
#define ADC_DMA_BUF_SIZE        50 * 2      /* ADC DMA采集 BUF大小, 应等于ADC通道数的整数倍 */
extern uint16_t my_adc_dma_buf[ADC_DMA_BUF_SIZE];

#endif 















