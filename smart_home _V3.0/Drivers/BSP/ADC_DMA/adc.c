#include "./BSP/ADC_DMA/adc.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"

//ADC����ɨ��ģʽ������ģʽ  ���������
//DMA��������ģʽ  ���������
//����������жϵķ�ʽ��ת��ָ������ͨ����DMAת������жϣ�ADC��DMAֹͣ���������������ݺ��ڼ���ת������


//��ͨ��ADC�ɼ�(DMA��ȡ)ʵ�����

uint16_t my_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */
uint8_t g_adc_dma_sta;                       /* DMA����״̬��־, 0,δ���; 1, ����� */


DMA_HandleTypeDef g_dma_nch_adc_handle = {0};                               /* ����Ҫ����ADC��ͨ�����ݵ�DMA��� */
ADC_HandleTypeDef g_adc_nch_dma_handle = {0};                               /* ����ADC����ͨ��DMA��ȡ����� */

/**
 * @brief       ADC Nͨ��(2ͨ��) DMA��ȡ ��ʼ������
 *   @note      ����������ʹ��adc_init��ADC���д󲿷�����,�в���ĵط��ٵ�������
 *              ����,���ڱ������õ���2��ͨ��, �궨���Ƚ϶�����, ���,�������Ͳ����ú궨��ķ�ʽ���޸�ͨ����,
 *              ֱ���ڱ����������޸�, ��������Ĭ��ʹ��PA0~PA5��6��ͨ��.
 *
 *
 * @param       mar         : �洢����ַ 
 * @retval      ��
 */
void adc_nch_dma_init(uint32_t mar)
{
    GPIO_InitTypeDef gpio_init_struct;
    RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
    ADC_ChannelConfTypeDef adc_ch_conf = {0};

    ADC_ADCX_CHY_CLK_ENABLE();                                                /* ʹ��ADCxʱ�� */
    __HAL_RCC_GPIOF_CLK_ENABLE();                                             /* ����GPIOFʱ�� */

    if ((uint32_t)ADC_ADCX_DMACx > (uint32_t)DMA1_Channel7)                   /* ����DMA1_Channel7, ��ΪDMA2��ͨ���� */
    {
        __HAL_RCC_DMA2_CLK_ENABLE();                                          /* DMA2ʱ��ʹ�� */
    }
    else
    {
        __HAL_RCC_DMA1_CLK_ENABLE();                                          /* DMA1ʱ��ʹ�� */
    }

    /* ����ADCʱ�� */
    adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;                    /* ADC����ʱ�� */
    adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;                       /* ��Ƶ����6ʱ��Ϊ72M/6=12MHz */
    HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);                                 /* ����ADCʱ�� */

    /*����ģ����������*/
    gpio_init_struct.Pin = GPIO_PIN_7|GPIO_PIN_8;                             /* GPIOF7~8 */
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;                                 /* ģ�� */
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);

    /* ��ʼ��DMA */ 
    g_dma_nch_adc_handle.Instance = ADC_ADCX_DMACx;                           /* ����DMAͨ�� */
    g_dma_nch_adc_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;               /* �����赽�洢��ģʽ */
    g_dma_nch_adc_handle.Init.PeriphInc = DMA_PINC_DISABLE;                   /* ���������ģʽ */
    g_dma_nch_adc_handle.Init.MemInc = DMA_MINC_ENABLE;                       /* �洢������ģʽ */
    g_dma_nch_adc_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;  /* �������ݳ���:16λ */
    g_dma_nch_adc_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;     /* �洢�����ݳ���:16λ */
    g_dma_nch_adc_handle.Init.Mode = DMA_NORMAL;                              /* ��������ģʽ */
    g_dma_nch_adc_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                 /* �е����ȼ� */
    HAL_DMA_Init(&g_dma_nch_adc_handle);

    __HAL_LINKDMA(&g_adc_nch_dma_handle, DMA_Handle, g_dma_nch_adc_handle);   /* ��DMA��adc��ϵ���� */

    /* ��ʼ��ADC */
    g_adc_nch_dma_handle.Instance = ADC_ADCX;                                 /* ѡ���ĸ�ADC */
    g_adc_nch_dma_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                /* ���ݶ��뷽ʽ���Ҷ��� */
    g_adc_nch_dma_handle.Init.ScanConvMode = ADC_SCAN_ENABLE;                 /* ʹ��ɨ��ģʽ */
    g_adc_nch_dma_handle.Init.ContinuousConvMode = ENABLE;                    /* ʹ������ת�� */
    g_adc_nch_dma_handle.Init.NbrOfConversion = 2;                            /* ��ֵ��Χ��1~16����ʵ���õ�6������ͨ������ */
    g_adc_nch_dma_handle.Init.DiscontinuousConvMode = DISABLE;                /* ��ֹ����ͨ������ģʽ */
    g_adc_nch_dma_handle.Init.NbrOfDiscConversion = 0;                        /* ���ü��ģʽ�Ĺ���ͨ����������ֹ����ͨ������ģʽ�󣬴˲������� */
    g_adc_nch_dma_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;          /* ������� */
    HAL_ADC_Init(&g_adc_nch_dma_handle);                                      /* ��ʼ�� */

    HAL_ADCEx_Calibration_Start(&g_adc_nch_dma_handle);                       /* У׼ADC */

    /* ����ADCͨ�� */
    adc_ch_conf.Channel = ADC_CHANNEL_5;                                      /* ����ʹ�õ�ADCͨ�� */
    adc_ch_conf.Rank = ADC_REGULAR_RANK_1;                                    /* ����������ĵ�1�� */
    adc_ch_conf.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;                    /* ����ʱ�䣬��������������:239.5��ADC���� */
    HAL_ADC_ConfigChannel(&g_adc_nch_dma_handle, &adc_ch_conf);               /* ͨ������ */
    
    adc_ch_conf.Channel = ADC_CHANNEL_6;                                      /* ����ʹ�õ�ADCͨ�� */
    adc_ch_conf.Rank = ADC_REGULAR_RANK_2;                                    /* ����������ĵ�2�� */
    HAL_ADC_ConfigChannel(&g_adc_nch_dma_handle, &adc_ch_conf);               /* ����ADCͨ�� */

    /* ����DMA�����������ж����ȼ� */
    HAL_NVIC_SetPriority(ADC_ADCX_DMACx_IRQn, 1, 3);
    HAL_NVIC_EnableIRQ(ADC_ADCX_DMACx_IRQn);

    HAL_DMA_Start_IT(&g_dma_nch_adc_handle, (uint32_t)&ADC1->DR, mar, 0);     /* ����DMA���������ж� */
    HAL_ADC_Start_DMA(&g_adc_nch_dma_handle, &mar, 0);                        /* ����ADC��ͨ��DMA������ */
}


/**
 * @brief       ʹ��һ��ADC DMA����
 *   @note      �ú����üĴ�������������ֹ��HAL������������������޸�,ҲΪ�˼�����
 * @param       ndtr: DMA����Ĵ���
 * @retval      ��
 */
void adc_dma_enable(uint16_t cndtr)
{
	
    ADC_ADCX->CR2 &= ~(1 << 0);                 /* �ȹر�ADC */

    ADC_ADCX_DMACx->CCR &= ~(1 << 0);           /* �ر�DMA���� */
    while (ADC_ADCX_DMACx->CCR & (1 << 0));     /* ȷ��DMA���Ա����� */
    ADC_ADCX_DMACx->CNDTR = cndtr;              /* DMA���������� */
    ADC_ADCX_DMACx->CCR |= 1 << 0;              /* ����DMA���� */

    ADC_ADCX->CR2 |= 1 << 0;                    /* ��������ADC */
    ADC_ADCX->CR2 |= 1 << 22;                   /* ��������ת��ͨ�� */
	
}



/**
 * @brief       ADC DMA�ɼ��жϷ�����
 * @param       �� 
 * @retval      ��
 */
void ADC_ADCX_DMACx_IRQHandler(void)
{
	
    if (ADC_ADCX_DMACx_IS_TC())
    {
        g_adc_dma_sta = 1;                      /* ���DMA������� */
        ADC_ADCX_DMACx_CLR_TC();                /* ���DMA1 ������7 ��������ж� */
    }
	
}

/**
 * @brief       ��ADC_DMA�ɼ������ݽ���ƽ������
 * @note        ʹ�øú�����Ҫһ��ȫ�ֻ�������uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];
                ADC_DMA_BUF_SIZE����Ϊͨ������������������Ҳ���ܹ��࣬Ҫ��ȻӰ��ת��Ч��
                ��Ҫ�ڱ��ļ���ͷ����һ��ȫ�ֱ���g_adc_dma_sta  �Զ���DMAת����ɱ�־
                Ҫ��main��������ѭ���в��ϵ���adc_get_value()����
 * @param       ��һ���������ݵ�������,������ĸ���ΪADCͨ���������������ֵ����ת�˺�
                ƽ����ֵ������ֱ��ȡ�����ã��Ҹ�����ʵʱ���¡�������Ҫ��main�����н���Ϊȫ�ֱ���
                �磺uint16_t data[2];//���ƽ�������ݴ�ŵ�����
 * @param       ADCͨ������ 
 * @retval      ��
 */

void  adc_get_value(uint16_t* dat,uint8_t n)  
{
	uint8_t i = 0, j = 0;
	uint32_t sum = 0;
	if (g_adc_dma_sta == 1)
		{
            for(j = 0; j < n; j++)
			{
                sum = 0; /* ���� */
                for (i = 0; i < ADC_DMA_BUF_SIZE / n; i++)  /* ÿ��ͨ���ɼ���ADC_DMA_BUF_SIZE / n������,�����ۼ� */
                {
                    sum += my_adc_dma_buf[(n * i) + j];      /* ��ͬͨ����ת�������ۼ� */
                }
                *(dat+j) = sum / (ADC_DMA_BUF_SIZE / n);    /* ȡƽ��ֵ */
                
			} 
            g_adc_dma_sta = 0;                      /* ���DMA�ɼ����״̬��־ */
            adc_dma_enable(ADC_DMA_BUF_SIZE);       /* ������һ��ADC DMA�ɼ� */
        }

}



//#include "./SYSTEM/sys/sys.h"
//#include "./SYSTEM/usart/usart.h"
//#include "./SYSTEM/delay/delay.h"
//#include "./USMART/usmart.h"
//#include "./BSP/LED/led.h"
//#include "./BSP/LCD/lcd.h"
//#include "./BSP/KEY/key.h"
//#include "./BSP/ADC_DMA/adc.h"
//#include "./BSP/DAC/dac.h"
//#include "./BSP/BEEP/beep.h"


//extern DAC_HandleTypeDef g_dac_handle; 
//uint16_t data[2];//���ƽ�������ݴ�ŵ�����
//int main(void)
//{
//	uint8_t t = 0;
//    HAL_Init();                                 /* ��ʼ��HAL�� */
//    sys_stm32_clock_init(RCC_PLL_MUL9);         /* ����ʱ��, 72Mhz */
//    delay_init(72);                             /* ��ʱ��ʼ�� */
//    usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
//    //usmart_dev.init(72);                        /* ��ʼ��USMART */
//    led_init();                                 /* ��ʼ��LED */
//    lcd_init();                                 /* ��ʼ��LCD */
//    key_init();                                 /* ��ʼ������ */
//	beep_init();                                /*��ʼ��������*/
//    dac_init();	                                /* ��ʼ��DAC1_OUT1/OUT2ͨ�� */ 
//    adc_nch_dma_init((uint32_t)&my_adc_dma_buf); /* ��ʼ��ADC3 */
//    //adc_dma_enable(ADC_DMA_BUF_SIZE);      �˳���������
//	while (1)
//    {
//		adc_get_value(data,2);
//        lcd_show_xnum(30, 50, data[0], 4, 16, 0, BLUE);           /* ��ʾ��ѹֵ�������� */
//		
//        lcd_show_xnum(30, 70, data[1], 4, 16, 0, BLUE);           /* ��ʾ��ѹֵ�������� */
//		t++;
//		delay_ms(20);
//		if(t==10)
//		{
//			LED0_TOGGLE();
//			t=0;
//		}
//     } 
//}

