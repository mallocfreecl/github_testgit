#include "./BSP/LCD/lcd.h"
#include "./BSP/TOUCH/touch.h"

//��ʼ��tp_dev��tp_dev����_m_tp_dev���ͽṹ��(�����һ��鿴�ṹ��ľ����Ա)������ָ����ǰ������Ա������ĳ�ʼ��Ϊ0
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
    return tp_dev.sta & TP_PRES_DOWN; /* ���ص�ǰ�Ĵ���״̬ */
}


/**
 * @brief       ��������ʼ��
 * @param       ��
 * @retval      0,û�н���У׼
 *              1,���й�У׼
 */
uint8_t tp_init(void)
{    
    tp_dev.touchtype = 0;                   /* Ĭ������(������ & ����) */
    tp_dev.touchtype |= lcddev.dir & 0X01;  /* ����LCD�ж��Ǻ����������� */

    if (lcddev.id == 0X5510)  /* ���ݴ�����,4.3��/10.1���� */
    {
        gt9xxx_init();
        tp_dev.scan = gt9xxx_scan;      /* ɨ�躯��ָ��GT9147������ɨ�� */
        tp_dev.touchtype |= 0X80;       /* ������ */
		//printf("lcddev:%x\r\n", lcddev.id);          /* ��ӡID */
        return 0;
    }

    return 1;
}
