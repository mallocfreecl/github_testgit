#ifndef __ADC_H
#define __ADC_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ADC������ ���� */
#define ADC_ADCX                            ADC3
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC3_CLK_ENABLE(); }while(0)   /* ADC1 ʱ��ʹ�� */

/* ADC��ͨ��/��ͨ�� DMA�ɼ� DMA��ͨ�� ����
 * ע��: ADC1��DMAͨ��ֻ����: DMA1_Channel1, ���ֻҪ��ADC1, �����ǲ��ܸĶ���
 *       ADC2��֧��DMA�ɼ�
 *       ADC3��DMAͨ��ֻ����: DMA2_Channel5, ������ʹ�� ADC3 ����Ҫ�޸�  ע��DMA2��ͨ��4��5��һ���ж�  
 *       
 */
#define ADC_ADCX_DMACx                      DMA2_Channel5
#define ADC_ADCX_DMACx_IRQn                 DMA2_Channel4_5_IRQn
#define ADC_ADCX_DMACx_IRQHandler           DMA2_Channel4_5_IRQHandler

#define ADC_ADCX_DMACx_IS_TC()              (DMA2->ISR & (17 << 1))    /* �ж� DMA2_Channel5 ������ɱ�־, ����һ���ٺ�����ʽ,
                                                                          * ���ܵ�����ʹ��, ֻ������if���������                                                                       */
#define ADC_ADCX_DMACx_CLR_TC()             do{ DMA2->IFCR |= 17 << 1; }while(0) /* ��� DMA2_Channel5 ������ɱ�־ */

//��������

void adc_dma_enable( uint16_t cndtr);                          /* ʹ��һ��ADC DMA�ɼ����� */
void adc_nch_dma_init(uint32_t mar);                           /* ADC��ͨ�� DMA�ɼ���ʼ�� */
void adc_get_value(uint16_t* dat,uint8_t n);

//������Ҫ�ĵĵط�
#define ADC_DMA_BUF_SIZE        50 * 2      /* ADC DMA�ɼ� BUF��С, Ӧ����ADCͨ������������ */
extern uint16_t my_adc_dma_buf[ADC_DMA_BUF_SIZE];

#endif 















