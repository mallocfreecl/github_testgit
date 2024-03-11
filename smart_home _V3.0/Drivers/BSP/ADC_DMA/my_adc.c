#include "./BSP/ADC_DMA/my_adc.h"
#include "./SYSTEM/delay/delay.h"

//使用ADC多通道DMA转运数据，ADC模拟通道:ADC3的通道5(PF7,MQ_135)和通道6(PF8,lsens)
//ADC:连续模式、扫描模式(一次性可以扫描多个通道)  用软件触发  
//DMA:循环模式、用ADC硬件触发

DMA_HandleTypeDef g_dma_nch_handle = {0};    /* 定义要搬运ADC多通道数据的DMA句柄 */
ADC_HandleTypeDef g_adc_nch_handle = {0};    /* 定义ADC（多通道DMA读取）句柄 */

/**
 * @brief       ADC N通道(2通道) DMA读取 初始化函数
 * @note        本函数还是使用adc_init对ADC进行大部分配置,有差异的地方再单独配置
 *              另外,由于本函数用到了ADC 2个通道, 宏定义会比较多内容, 因此,本函数就不采用宏定义的方式来修改通道了,
 *              直接在本函数里面修改, 这里我们使用ADC3的通道5(PF7,MQ_135)和通道6(PF8,lsens)。
 *
* @param        mar: 32位存储器地址 使用方法:adc_nch_dma_init((uint32_t)&g_adc_dma_buf);  uint16_t g_adc_dma_buf[50]
 * @retval      无   DMA转运是16位的，ADC转换的数据默认为12位。
 */
void my_adc_nch_dma_init(uint32_t mar)
{
	//定义要用到的结构体
    GPIO_InitTypeDef gpio_init_struct = {0};
    RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
    ADC_ChannelConfTypeDef adc_ch_conf = {0};
    
	//1.使能ADC3/GPIOF(PF7、PF8)/DMA时钟
    __HAL_RCC_ADC3_CLK_ENABLE();                                              /* 使能ADC1时钟 */
    __HAL_RCC_GPIOF_CLK_ENABLE();                                             /* 开启GPIOF时钟 */
		
    if ((uint32_t)ADC_DMA_CHx > (uint32_t)DMA1_Channel7)                      /* 大于DMA1_Channel7, 则为DMA2的通道了 */
    {
        __HAL_RCC_DMA2_CLK_ENABLE();                                          /* DMA2时钟使能 */ //本实验用的是DMA2
    }
    else
    {
        __HAL_RCC_DMA1_CLK_ENABLE();                                          /* DMA1时钟使能 */
    }

    /* 设置ADC时钟 */
    adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;                    /* ADC外设时钟 */
    adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;                       /* 分频因子6时钟为72M/6=12MHz */
    HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);                                 /* 设置ADC时钟 */
    
    /* 
        设置ADC3通道5、6对应的IO口模拟输入
        AD采集引脚模式设置,模拟输入
        PF7对应 ADC3_IN5
        PF8对应 ADC3_IN6
        
    */
	//2.初始化ADC的输入引脚
    gpio_init_struct.Pin = GPIO_PIN_7;                                        /* GPIOF7*/
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;                                 /* 模拟 */
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);
    
	gpio_init_struct.Pin = GPIO_PIN_8;                                        /* GPIOF8*/
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;                                 /* 模拟 */
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);
    //3.初始化DMA 
    g_dma_nch_handle.Instance = ADC_DMA_CHx;                              /* 设置DMA通道 */
    g_dma_nch_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;               /* 从外设到存储器模式 */
    g_dma_nch_handle.Init.PeriphInc = DMA_PINC_DISABLE;                   /* 外设非增量模式 */
    g_dma_nch_handle.Init.MemInc = DMA_MINC_ENABLE;                       /* 存储器增量模式 */
    g_dma_nch_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;  /* 外设数据长度:16位 */
    g_dma_nch_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;     /* 存储器数据长度:16位 */
    g_dma_nch_handle.Init.Mode = DMA_CIRCULAR;                            /* 循环模式 */ //循环模式可以转运两个数据到mar[2]数组后再次将数据转运                    
    g_dma_nch_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                 /* 中等优先级 */ //置数组mar[2],最新的转运值会覆盖旧的转运值
    HAL_DMA_Init(&g_dma_nch_handle);
    //将DMA与硬件连接起来
    __HAL_LINKDMA(&g_adc_nch_handle, DMA_Handle, g_dma_nch_handle);   /* 将DMA与adc联系起来 */

    //4.初始化ADC 
    g_adc_nch_handle.Instance = ADC3;                                     /* 选择哪个ADC */
    g_adc_nch_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                /* 数据对齐方式：右对齐 */
    g_adc_nch_handle.Init.ScanConvMode = ADC_SCAN_ENABLE;                 /* 使能扫描模式 */
    g_adc_nch_handle.Init.ContinuousConvMode = ENABLE;                    /* 使能连续转换 */
    g_adc_nch_handle.Init.NbrOfConversion = 2;                            /* 赋值范围是1~16，本实验用到6个规则通道序列 */
    g_adc_nch_handle.Init.DiscontinuousConvMode = DISABLE;                /* 禁止规则通道组间断模式 */
    g_adc_nch_handle.Init.NbrOfDiscConversion = 0;                        /* 配置间断模式的规则通道个数，禁止规则通道组间断模式后，此参数忽略 */
    g_adc_nch_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;          /* 软件触发 */
    HAL_ADC_Init(&g_adc_nch_handle);                                      /* 初始化 */
    //5.校准ADC
    HAL_ADCEx_Calibration_Start(&g_adc_nch_handle);                       /* 校准ADC */

    //6.配置ADC通道 
    adc_ch_conf.Channel = ADC_CHANNEL_5;                                  /* 配置使用的ADC通道 */ //PF7
    adc_ch_conf.Rank = ADC_REGULAR_RANK_1;                                /* 采样序列里的第1个 */
    adc_ch_conf.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;                /* 采样时间，设置最大采样周期:239.5个ADC周期 */
    HAL_ADC_ConfigChannel(&g_adc_nch_handle, &adc_ch_conf);               /* 通道配置 */
    
    adc_ch_conf.Channel = ADC_CHANNEL_6;                                  /* 配置使用的ADC通道 */ //PF8
    adc_ch_conf.Rank = ADC_REGULAR_RANK_2;                                /* 采样序列里的第2个 */
    HAL_ADC_ConfigChannel(&g_adc_nch_handle, &adc_ch_conf);               /* 配置ADC通道 */

    //7.启动DMA和ADC
    HAL_DMA_Start(&g_dma_nch_handle, (uint32_t)&ADC3->DR, mar, 0);        /* 启动DMA，且没有开启中断 */
    HAL_ADC_Start_DMA(&g_adc_nch_handle, &mar, 0);                        /* 开启ADC，通过DMA传输结果 */
}   //这两个函数最后一个参数应该与DMA_start的个数一致,设置为0,则暂时不开启DMA


/**
 * @brief       使能一次ADC DMA传输
 * @note        该函数用寄存器来操作，防止用HAL库操作对其他参数有修改,也为了兼容性
 * @param       ndtr: DMA传输的次数
 * @retval      无
 */
void my_adc_dma_enable(uint16_t cndtr)//使能一次DMA,之后就一直传输 //其实也可以直接在init函数规定次数后直接开始转运
{
    ADC3->CR2 &= ~(1 << 0);                    /* 先关闭ADC */
    DMA2_Channel5->CCR &= ~(1 << 0);           /* 关闭DMA传输 */
    
	while (DMA2_Channel5->CCR & (1 << 0));    /* 确保DMA可以被设置 */
    DMA2_Channel5->CNDTR = cndtr;              /* DMA传输数据量 */
    
	DMA2_Channel5->CCR |= 1 << 0;              /* 开启DMA传输 */
    ADC3->CR2 |= 1 << 0;                       /* 重新启动ADC */
    ADC3->CR2 |= 1 << 22;                      /* 启动规则转换通道 */
} 

/**
 * @brief       对数组数据进行平均处理
 * @note        当数组元素较多时，注意sum不要超界
 *  
 * @param       n:ADC使用的通道数
 * @param       x:要计算第x个通道     
 * @param       dat[]:采集的数据数组
 * @param       num:采集数据数组的元素个数  必须是n的整数倍
 * @retval      最后返回值强制转换为uint16_t
 */
uint16_t my_get_value(uint8_t n,uint8_t x,uint16_t dat[],uint16_t num)
{
	uint8_t i = 0;
	uint32_t sum = 0;//不能是u16否则数据会超过最大范围
	for (i = x - 1; i < num; i += n) /* 累加 */
	{
		sum += dat[i];
	}
 return (uint16_t)(sum / ( num / n));//sum的外() 不能去，()比/的优先级更高
}


/**
 * @brief       读取光敏传感器模拟值   
 * @param       lsens_analog  ADC的模拟值,最大4096(2^12)
 * @retval      0~100:0,最暗;100,最亮
 */
uint8_t lsens_get_val(uint16_t lsens_analog)
{
    //temp_val = adc3_get_result_average(LSENS_ADC3_CHX, 10);  /* 读取平均值 */
    lsens_analog /= 40;

    if (lsens_analog > 100)lsens_analog = 100;

    return (uint8_t)(100 - lsens_analog);
}


/**
 * @brief       读取空气质量传感器模拟值   
 * @param       airqu_analog  ADC的模拟值,最大4096(2^12)   高浓度电压4V左右
 * @retval      0~100:0,最暗;100,最亮
 */
uint8_t airqu_get_val(uint16_t airqu_analog)
{
    //temp_val = adc3_get_result_average(LSENS_ADC3_CHX, 10);  /* 读取平均值 */
    airqu_analog /=50;     // (4096/3.3*4)/100;

    if (airqu_analog > 100)airqu_analog = 100;

    return (uint8_t)(100 - airqu_analog);
}
