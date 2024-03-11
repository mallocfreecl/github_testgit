#include "./BSP/ADC_DMA/my_adc.h"
#include "./SYSTEM/delay/delay.h"

//ʹ��ADC��ͨ��DMAת�����ݣ�ADCģ��ͨ��:ADC3��ͨ��5(PF7,MQ_135)��ͨ��6(PF8,lsens)
//ADC:����ģʽ��ɨ��ģʽ(һ���Կ���ɨ����ͨ��)  ���������  
//DMA:ѭ��ģʽ����ADCӲ������

DMA_HandleTypeDef g_dma_nch_handle = {0};    /* ����Ҫ����ADC��ͨ�����ݵ�DMA��� */
ADC_HandleTypeDef g_adc_nch_handle = {0};    /* ����ADC����ͨ��DMA��ȡ����� */

/**
 * @brief       ADC Nͨ��(2ͨ��) DMA��ȡ ��ʼ������
 * @note        ����������ʹ��adc_init��ADC���д󲿷�����,�в���ĵط��ٵ�������
 *              ����,���ڱ������õ���ADC 2��ͨ��, �궨���Ƚ϶�����, ���,�������Ͳ����ú궨��ķ�ʽ���޸�ͨ����,
 *              ֱ���ڱ����������޸�, ��������ʹ��ADC3��ͨ��5(PF7,MQ_135)��ͨ��6(PF8,lsens)��
 *
* @param        mar: 32λ�洢����ַ ʹ�÷���:adc_nch_dma_init((uint32_t)&g_adc_dma_buf);  uint16_t g_adc_dma_buf[50]
 * @retval      ��   DMAת����16λ�ģ�ADCת��������Ĭ��Ϊ12λ��
 */
void my_adc_nch_dma_init(uint32_t mar)
{
	//����Ҫ�õ��Ľṹ��
    GPIO_InitTypeDef gpio_init_struct = {0};
    RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
    ADC_ChannelConfTypeDef adc_ch_conf = {0};
    
	//1.ʹ��ADC3/GPIOF(PF7��PF8)/DMAʱ��
    __HAL_RCC_ADC3_CLK_ENABLE();                                              /* ʹ��ADC1ʱ�� */
    __HAL_RCC_GPIOF_CLK_ENABLE();                                             /* ����GPIOFʱ�� */
		
    if ((uint32_t)ADC_DMA_CHx > (uint32_t)DMA1_Channel7)                      /* ����DMA1_Channel7, ��ΪDMA2��ͨ���� */
    {
        __HAL_RCC_DMA2_CLK_ENABLE();                                          /* DMA2ʱ��ʹ�� */ //��ʵ���õ���DMA2
    }
    else
    {
        __HAL_RCC_DMA1_CLK_ENABLE();                                          /* DMA1ʱ��ʹ�� */
    }

    /* ����ADCʱ�� */
    adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;                    /* ADC����ʱ�� */
    adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;                       /* ��Ƶ����6ʱ��Ϊ72M/6=12MHz */
    HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);                                 /* ����ADCʱ�� */
    
    /* 
        ����ADC3ͨ��5��6��Ӧ��IO��ģ������
        AD�ɼ�����ģʽ����,ģ������
        PF7��Ӧ ADC3_IN5
        PF8��Ӧ ADC3_IN6
        
    */
	//2.��ʼ��ADC����������
    gpio_init_struct.Pin = GPIO_PIN_7;                                        /* GPIOF7*/
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;                                 /* ģ�� */
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);
    
	gpio_init_struct.Pin = GPIO_PIN_8;                                        /* GPIOF8*/
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;                                 /* ģ�� */
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);
    //3.��ʼ��DMA 
    g_dma_nch_handle.Instance = ADC_DMA_CHx;                              /* ����DMAͨ�� */
    g_dma_nch_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;               /* �����赽�洢��ģʽ */
    g_dma_nch_handle.Init.PeriphInc = DMA_PINC_DISABLE;                   /* ���������ģʽ */
    g_dma_nch_handle.Init.MemInc = DMA_MINC_ENABLE;                       /* �洢������ģʽ */
    g_dma_nch_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;  /* �������ݳ���:16λ */
    g_dma_nch_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;     /* �洢�����ݳ���:16λ */
    g_dma_nch_handle.Init.Mode = DMA_CIRCULAR;                            /* ѭ��ģʽ */ //ѭ��ģʽ����ת���������ݵ�mar[2]������ٴν�����ת��                    
    g_dma_nch_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                 /* �е����ȼ� */ //������mar[2],���µ�ת��ֵ�Ḳ�Ǿɵ�ת��ֵ
    HAL_DMA_Init(&g_dma_nch_handle);
    //��DMA��Ӳ����������
    __HAL_LINKDMA(&g_adc_nch_handle, DMA_Handle, g_dma_nch_handle);   /* ��DMA��adc��ϵ���� */

    //4.��ʼ��ADC 
    g_adc_nch_handle.Instance = ADC3;                                     /* ѡ���ĸ�ADC */
    g_adc_nch_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                /* ���ݶ��뷽ʽ���Ҷ��� */
    g_adc_nch_handle.Init.ScanConvMode = ADC_SCAN_ENABLE;                 /* ʹ��ɨ��ģʽ */
    g_adc_nch_handle.Init.ContinuousConvMode = ENABLE;                    /* ʹ������ת�� */
    g_adc_nch_handle.Init.NbrOfConversion = 2;                            /* ��ֵ��Χ��1~16����ʵ���õ�6������ͨ������ */
    g_adc_nch_handle.Init.DiscontinuousConvMode = DISABLE;                /* ��ֹ����ͨ������ģʽ */
    g_adc_nch_handle.Init.NbrOfDiscConversion = 0;                        /* ���ü��ģʽ�Ĺ���ͨ����������ֹ����ͨ������ģʽ�󣬴˲������� */
    g_adc_nch_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;          /* ������� */
    HAL_ADC_Init(&g_adc_nch_handle);                                      /* ��ʼ�� */
    //5.У׼ADC
    HAL_ADCEx_Calibration_Start(&g_adc_nch_handle);                       /* У׼ADC */

    //6.����ADCͨ�� 
    adc_ch_conf.Channel = ADC_CHANNEL_5;                                  /* ����ʹ�õ�ADCͨ�� */ //PF7
    adc_ch_conf.Rank = ADC_REGULAR_RANK_1;                                /* ����������ĵ�1�� */
    adc_ch_conf.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;                /* ����ʱ�䣬��������������:239.5��ADC���� */
    HAL_ADC_ConfigChannel(&g_adc_nch_handle, &adc_ch_conf);               /* ͨ������ */
    
    adc_ch_conf.Channel = ADC_CHANNEL_6;                                  /* ����ʹ�õ�ADCͨ�� */ //PF8
    adc_ch_conf.Rank = ADC_REGULAR_RANK_2;                                /* ����������ĵ�2�� */
    HAL_ADC_ConfigChannel(&g_adc_nch_handle, &adc_ch_conf);               /* ����ADCͨ�� */

    //7.����DMA��ADC
    HAL_DMA_Start(&g_dma_nch_handle, (uint32_t)&ADC3->DR, mar, 0);        /* ����DMA����û�п����ж� */
    HAL_ADC_Start_DMA(&g_adc_nch_handle, &mar, 0);                        /* ����ADC��ͨ��DMA������ */
}   //�������������һ������Ӧ����DMA_start�ĸ���һ��,����Ϊ0,����ʱ������DMA


/**
 * @brief       ʹ��һ��ADC DMA����
 * @note        �ú����üĴ�������������ֹ��HAL������������������޸�,ҲΪ�˼�����
 * @param       ndtr: DMA����Ĵ���
 * @retval      ��
 */
void my_adc_dma_enable(uint16_t cndtr)//ʹ��һ��DMA,֮���һֱ���� //��ʵҲ����ֱ����init�����涨������ֱ�ӿ�ʼת��
{
    ADC3->CR2 &= ~(1 << 0);                    /* �ȹر�ADC */
    DMA2_Channel5->CCR &= ~(1 << 0);           /* �ر�DMA���� */
    
	while (DMA2_Channel5->CCR & (1 << 0));    /* ȷ��DMA���Ա����� */
    DMA2_Channel5->CNDTR = cndtr;              /* DMA���������� */
    
	DMA2_Channel5->CCR |= 1 << 0;              /* ����DMA���� */
    ADC3->CR2 |= 1 << 0;                       /* ��������ADC */
    ADC3->CR2 |= 1 << 22;                      /* ��������ת��ͨ�� */
} 

/**
 * @brief       ���������ݽ���ƽ������
 * @note        ������Ԫ�ؽ϶�ʱ��ע��sum��Ҫ����
 *  
 * @param       n:ADCʹ�õ�ͨ����
 * @param       x:Ҫ�����x��ͨ��     
 * @param       dat[]:�ɼ�����������
 * @param       num:�ɼ����������Ԫ�ظ���  ������n��������
 * @retval      ��󷵻�ֵǿ��ת��Ϊuint16_t
 */
uint16_t my_get_value(uint8_t n,uint8_t x,uint16_t dat[],uint16_t num)
{
	uint8_t i = 0;
	uint32_t sum = 0;//������u16�������ݻᳬ�����Χ
	for (i = x - 1; i < num; i += n) /* �ۼ� */
	{
		sum += dat[i];
	}
 return (uint16_t)(sum / ( num / n));//sum����() ����ȥ��()��/�����ȼ�����
}


/**
 * @brief       ��ȡ����������ģ��ֵ   
 * @param       lsens_analog  ADC��ģ��ֵ,���4096(2^12)
 * @retval      0~100:0,�;100,����
 */
uint8_t lsens_get_val(uint16_t lsens_analog)
{
    //temp_val = adc3_get_result_average(LSENS_ADC3_CHX, 10);  /* ��ȡƽ��ֵ */
    lsens_analog /= 40;

    if (lsens_analog > 100)lsens_analog = 100;

    return (uint8_t)(100 - lsens_analog);
}


/**
 * @brief       ��ȡ��������������ģ��ֵ   
 * @param       airqu_analog  ADC��ģ��ֵ,���4096(2^12)   ��Ũ�ȵ�ѹ4V����
 * @retval      0~100:0,�;100,����
 */
uint8_t airqu_get_val(uint16_t airqu_analog)
{
    //temp_val = adc3_get_result_average(LSENS_ADC3_CHX, 10);  /* ��ȡƽ��ֵ */
    airqu_analog /=50;     // (4096/3.3*4)/100;

    if (airqu_analog > 100)airqu_analog = 100;

    return (uint8_t)(100 - airqu_analog);
}
