#include "./BSP/LCD/lcd.h"
#include "./BSP/TOUCH/touch.h"

//初始化tp_dev，tp_dev属于_m_tp_dev类型结构体(可以右击查看结构体的具体成员)，这里指定了前三个成员，后面的初始化为0
_m_tp_dev tp_dev =
{
    tp_init,
    tp_scan,
    0,//tp_adjust,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

uint8_t tp_scan(uint8_t mode)
{
    return tp_dev.sta & TP_PRES_DOWN; /* 返回当前的触屏状态 */
}


/**
 * @brief       触摸屏初始化
 * @param       无
 * @retval      0,没有进行校准
 *              1,进行过校准
 */
uint8_t tp_init(void)
{    
    tp_dev.touchtype = 0;                   /* 默认设置(电阻屏 & 竖屏) */
    tp_dev.touchtype |= lcddev.dir & 0X01;  /* 根据LCD判定是横屏还是竖屏 */

    if (lcddev.id == 0X5510)  /* 电容触摸屏,4.3寸/10.1寸屏 */
    {
        gt9xxx_init();
        tp_dev.scan = gt9xxx_scan;      /* 扫描函数指向GT9147触摸屏扫描 */
        tp_dev.touchtype |= 0X80;       /* 电容屏 */
		//printf("lcddev:%x\r\n", lcddev.id);          /* 打印ID */
        return 0;
    }

    return 1;
}
