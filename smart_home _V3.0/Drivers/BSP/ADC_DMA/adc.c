#include "./BSP/ADC_DMA/adc.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"

//ADC采用扫描模式、连续模式  由软件触发
//DMA采用正常模式  由软件触发
//本程序采用中断的方式，转运指定个数通道后，DMA转运完成中断，ADC和DMA停止工作，处理完数据后在继续转运数据


//多通道ADC采集(DMA读取)实验代码

uint16_t my_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */
uint8_t g_adc_dma_sta;                       /* DMA传输状态标志, 0,未完成; 1, 已完成 */


DMA_HandleTypeDef g_dma_nch_adc_handle = {0};                               /* 定义要搬运ADC多通道数据的DMA句柄 */
ADC_HandleTypeDef g_adc_nch_dma_handle = {0};                               /* 定义ADC（多通道DMA读取）句柄 */

/**
 * @brief       ADC N通道(2通道) DMA读取 初始化函数
 *   @note      本函数还是使用adc_init对ADC进行大部分配置,有差异的地方再单独配置
 *              另外,由于本函数用到了2个通道, 宏定义会比较多内容, 因此,本函数就不采用宏定义的方式来修改通道了,
 *              直接在本函数里面修改, 这里我们默认使用PA0~PA5这6个通道.
 *
 *
 * @param       mar         : 存储器地址 
 * @retval      无
 */
void adc_nch_dma_init(uint32_t mar)
{
    GPIO_InitTypeDef gpio_init_struct;
    RCC_PeriphCLKInitTypeDef adc_clk_init = {0};
    ADC_ChannelConfTypeDef adc_ch_conf = {0};

    ADC_ADCX_CHY_CLK_ENABLE();                                                /* 使能ADCx时钟 */
    __HAL_RCC_GPIOF_CLK_ENABLE();                                             /* 开启GPIOF时钟 */

    if ((uint32_t)ADC_ADCX_DMACx > (uint32_t)DMA1_Channel7)                   /* 大于DMA1_Channel7, 则为DMA2的通道了 */
    {
        __HAL_RCC_DMA2_CLK_ENABLE();                                          /* DMA2时钟使能 */
    }
    else
    {
        __HAL_RCC_DMA1_CLK_ENABLE();                                          /* DMA1时钟使能 */
    }

    /* 设置ADC时钟 */
    adc_clk_init.PeriphClockSelection = RCC_PERIPHCLK_ADC;                    /* ADC外设时钟 */
    adc_clk_init.AdcClockSelection = RCC_ADCPCLK2_DIV6;                       /* 分频因子6时钟为72M/6=12MHz */
    HAL_RCCEx_PeriphCLKConfig(&adc_clk_init);                                 /* 设置ADC时钟 */

    /*设置模拟输入引脚*/
    gpio_init_struct.Pin = GPIO_PIN_7|GPIO_PIN_8;                             /* GPIOF7~8 */
    gpio_init_struct.Mode = GPIO_MODE_ANALOG;                                 /* 模拟 */
    HAL_GPIO_Init(GPIOF, &gpio_init_struct);

    /* 初始化DMA */ 
    g_dma_nch_adc_handle.Instance = ADC_ADCX_DMACx;                           /* 设置DMA通道 */
    g_dma_nch_adc_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;               /* 从外设到存储器模式 */
    g_dma_nch_adc_handle.Init.PeriphInc = DMA_PINC_DISABLE;                   /* 外设非增量模式 */
    g_dma_nch_adc_handle.Init.MemInc = DMA_MINC_ENABLE;                       /* 存储器增量模式 */
    g_dma_nch_adc_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;  /* 外设数据长度:16位 */
    g_dma_nch_adc_handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;     /* 存储器数据长度:16位 */
    g_dma_nch_adc_handle.Init.Mode = DMA_NORMAL;                              /* 外设流控模式 */
    g_dma_nch_adc_handle.Init.Priority = DMA_PRIORITY_MEDIUM;                 /* 中等优先级 */
    HAL_DMA_Init(&g_dma_nch_adc_handle);

    __HAL_LINKDMA(&g_adc_nch_dma_handle, DMA_Handle, g_dma_nch_adc_handle);   /* 将DMA与adc联系起来 */

    /* 初始化ADC */
    g_adc_nch_dma_handle.Instance = ADC_ADCX;                                 /* 选择哪个ADC */
    g_adc_nch_dma_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;                /* 数据对齐方式：右对齐 */
    g_adc_nch_dma_handle.Init.ScanConvMode = ADC_SCAN_ENABLE;                 /* 使能扫描模式 */
    g_adc_nch_dma_handle.Init.ContinuousConvMode = ENABLE;                    /* 使能连续转换 */
    g_adc_nch_dma_handle.Init.NbrOfConversion = 2;                            /* 赋值范围是1~16，本实验用到6个规则通道序列 */
    g_adc_nch_dma_handle.Init.DiscontinuousConvMode = DISABLE;                /* 禁止规则通道组间断模式 */
    g_adc_nch_dma_handle.Init.NbrOfDiscConversion = 0;                        /* 配置间断模式的规则通道个数，禁止规则通道组间断模式后，此参数忽略 */
    g_adc_nch_dma_handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;          /* 软件触发 */
    HAL_ADC_Init(&g_adc_nch_dma_handle);                                      /* 初始化 */

    HAL_ADCEx_Calibration_Start(&g_adc_nch_dma_handle);                       /* 校准ADC */

    /* 配置ADC通道 */
    adc_ch_conf.Channel = ADC_CHANNEL_5;                                      /* 配置使用的ADC通道 */
    adc_ch_conf.Rank = ADC_REGULAR_RANK_1;                                    /* 采样序列里的第1个 */
    adc_ch_conf.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;                    /* 采样时间，设置最大采样周期:239.5个ADC周期 */
    HAL_ADC_ConfigChannel(&g_adc_nch_dma_handle, &adc_ch_conf);               /* 通道配置 */
    
    adc_ch_conf.Channel = ADC_CHANNEL_6;                                      /* 配置使用的ADC通道 */
    adc_ch_conf.Rank = ADC_REGULAR_RANK_2;                                    /* 采样序列里的第2个 */
    HAL_ADC_ConfigChannel(&g_adc_nch_dma_handle, &adc_ch_conf);               /* 配置ADC通道 */

    /* 配置DMA数据流请求中断优先级 */
    HAL_NVIC_SetPriority(ADC_ADCX_DMACx_IRQn, 1, 3);
    HAL_NVIC_EnableIRQ(ADC_ADCX_DMACx_IRQn);

    HAL_DMA_Start_IT(&g_dma_nch_adc_handle, (uint32_t)&ADC1->DR, mar, 0);     /* 启动DMA，并开启中断 */
    HAL_ADC_Start_DMA(&g_adc_nch_dma_handle, &mar, 0);                        /* 开启ADC，通过DMA传输结果 */
}


/**
 * @brief       使能一次ADC DMA传输
 *   @note      该函数用寄存器来操作，防止用HAL库操作对其他参数有修改,也为了兼容性
 * @param       ndtr: DMA传输的次数
 * @retval      无
 */
void adc_dma_enable(uint16_t cndtr)
{
	
    ADC_ADCX->CR2 &= ~(1 << 0);                 /* 先关闭ADC */

    ADC_ADCX_DMACx->CCR &= ~(1 << 0);           /* 关闭DMA传输 */
    while (ADC_ADCX_DMACx->CCR & (1 << 0));     /* 确保DMA可以被设置 */
    ADC_ADCX_DMACx->CNDTR = cndtr;              /* DMA传输数据量 */
    ADC_ADCX_DMACx->CCR |= 1 << 0;              /* 开启DMA传输 */

    ADC_ADCX->CR2 |= 1 << 0;                    /* 重新启动ADC */
    ADC_ADCX->CR2 |= 1 << 22;                   /* 启动规则转换通道 */
	
}



/**
 * @brief       ADC DMA采集中断服务函数
 * @param       无 
 * @retval      无
 */
void ADC_ADCX_DMACx_IRQHandler(void)
{
	
    if (ADC_ADCX_DMACx_IS_TC())
    {
        g_adc_dma_sta = 1;                      /* 标记DMA传输完成 */
        ADC_ADCX_DMACx_CLR_TC();                /* 清除DMA1 数据流7 传输完成中断 */
    }
	
}

/**
 * @brief       对ADC_DMA采集的数据进行平均处理
 * @note        使用该函数需要一个全局缓冲数组uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];
                ADC_DMA_BUF_SIZE必须为通道数的整数倍，次数也不能过多，要不然影响转化效率
                需要在本文件开头建立一个全局变量g_adc_dma_sta  自定义DMA转运完成标志
                要在main函数中主循环中不断调用adc_get_value()函数
 * @param       传一个最终数据的数组名,该数组的个数为ADC通道数，该数组里的值都是转运后
                平均的值，可以直接取出来用，且该数据实时更新。该数组要在main函数中建立为全局变量
                如：uint16_t data[2];//最后平均的数据存放的数组
 * @param       ADC通道总数 
 * @retval      无
 */

void  adc_get_value(uint16_t* dat,uint8_t n)  
{
	uint8_t i = 0, j = 0;
	uint32_t sum = 0;
	if (g_adc_dma_sta == 1)
		{
            for(j = 0; j < n; j++)
			{
                sum = 0; /* 清零 */
                for (i = 0; i < ADC_DMA_BUF_SIZE / n; i++)  /* 每个通道采集了ADC_DMA_BUF_SIZE / n次数据,进行累加 */
                {
                    sum += my_adc_dma_buf[(n * i) + j];      /* 相同通道的转换数据累加 */
                }
                *(dat+j) = sum / (ADC_DMA_BUF_SIZE / n);    /* 取平均值 */
                
			} 
            g_adc_dma_sta = 0;                      /* 清除DMA采集完成状态标志 */
            adc_dma_enable(ADC_DMA_BUF_SIZE);       /* 启动下一次ADC DMA采集 */
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
//uint16_t data[2];//最后平均的数据存放的数组
//int main(void)
//{
//	uint8_t t = 0;
//    HAL_Init();                                 /* 初始化HAL库 */
//    sys_stm32_clock_init(RCC_PLL_MUL9);         /* 设置时钟, 72Mhz */
//    delay_init(72);                             /* 延时初始化 */
//    usart_init(115200);                         /* 串口初始化为115200 */
//    //usmart_dev.init(72);                        /* 初始化USMART */
//    led_init();                                 /* 初始化LED */
//    lcd_init();                                 /* 初始化LCD */
//    key_init();                                 /* 初始化按键 */
//	beep_init();                                /*初始化蜂鸣器*/
//    dac_init();	                                /* 初始化DAC1_OUT1/OUT2通道 */ 
//    adc_nch_dma_init((uint32_t)&my_adc_dma_buf); /* 初始化ADC3 */
//    //adc_dma_enable(ADC_DMA_BUF_SIZE);      此程序有问题
//	while (1)
//    {
//		adc_get_value(data,2);
//        lcd_show_xnum(30, 50, data[0], 4, 16, 0, BLUE);           /* 显示电压值整数部分 */
//		
//        lcd_show_xnum(30, 70, data[1], 4, 16, 0, BLUE);           /* 显示电压值整数部分 */
//		t++;
//		delay_ms(20);
//		if(t==10)
//		{
//			LED0_TOGGLE();
//			t=0;
//		}
//     } 
//}

