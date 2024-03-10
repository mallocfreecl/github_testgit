#include "./SYSTEM/sys/sys.h"
#include "./BSP/USART/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/DHT11/dht11.h"
#include "./BSP/ADC_DMA/my_adc.h"
#include "./BSP/B_TIMER/btim.h"
#include "./BSP/GTIM/gtim.h"
#include "./BSP/SERVO/servo.h"
#include "./BSP/KEY_EXTI/key_exti.h"
#include "./BSP/TOUCH/touch.h"
#include "./BSP/24CXX/24cxx.h"
#include "./BSP/RTC/rtc.h"

#include "esp8266.h"
#include "onenet.h"

#define DATA_NUM 60

uint8_t alarm_flag;
uint8_t alarm_is_free = 10;
uint16_t g_adc_dma_buf[DATA_NUM]; 

uint8_t Temperature;
uint8_t Humidity;
uint8_t Light;      
uint8_t AirQuality;
uint8_t TemperatureMax = 30;//����(������)�����ֵ//������ֵ����
uint8_t HumidityMax = 70;
uint8_t LightMax = 50;      
uint8_t AirQualityMin = 50;//����(������)����Сֵ//�͹���ֵ����

//������־λ
uint8_t Lcd_Page = 1;//LCD����ҳ��
uint8_t changeflag;
uint8_t Curtain_Status;
uint8_t lastmove = 2;//�������״̬��0:��ת 1:��ת 2:���ֹͣ Ĭ��ֹͣ
uint32_t pulse = 64*64;//pulse = int(double)(angle/5.625)*64(angleΪ��Ҫ��ת�ĽǶȣ�64*64����360��
uint8_t Windows_Status = 1;//=1Ĭ�ϴ�������
uint8_t HomeMode;

uint8_t LED1_Status;//�ƵƵ�״̬  1:��  0:Ϩ��       
uint8_t BEEP1_Status;//�Ǳ���������״̬ 0:��  1:����  
char* weekdays[]={"Sunday","Monday","Tuesday","Wednesday",
                  "Thursday","Friday","Saterday"};


char PUB_BUF[256];//�ϴ����ݵ�buf
const char *devSubTopic[] = {"/mysmarthome_stm32_8266/sub"};//���ĵ�������
const char devPubTopic[] = {"/mysmarthome_stm32_8266/pub"}; //������������
	
int main(void)
{
    uint16_t t = 0;
	uint8_t tbuf[40];
    
	unsigned short timeCount = 0;	            //���ͼ������	
	unsigned char *dataPtr = NULL;

    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
	Usart1_Init(115200);                //DEBUG ����1
	Usart2_Init(115200);                //STM32_8266ͨѶ����
    led_init();                         /* ��ʼ��LED */
	beep_init();                        /* ��ʼ��BEEP */   
    lcd_init();                         /* ��ʼ��LCD */
    my_adc_nch_dma_init((uint32_t)&g_adc_dma_buf); /* ��ʼ��ADC3 */
	my_adc_dma_enable(DATA_NUM);
	btim_tim6_int_init(7200-1, 5000);//������ʱ��,0.5s��ʱ������жϣ������ж�ִ�е���alarm_flag������
	Servo_Init();
	key_extix_init();
	dht11_init();
    tp_dev.init();  //������
    at24cxx_init();	
	Servo_Init();
	rtc_init();
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	
	ESP8266_Init();					//��ʼ��ESP8266
	while(OneNet_DevLink())			//����OneNET//���ӷ������ĺ���,���ӳɹ�����0
		delay_ms(500);
	
	BEEP(1);				//������ʾ����ɹ�
	delay_ms(250);
	BEEP(0);
	
	OneNet_Subscribe(devSubTopic, 1);//��������
	
	//ϵͳ�״��ϵ磬��ʼ������
	if(at24cxx_read_one_byte(80)!= 0xA0)
	{
		//��EEPROM��д���豣�������
		at24cxx_write_one_byte(60,TemperatureMax);
		at24cxx_write_one_byte(61,HumidityMax);
		at24cxx_write_one_byte(62,LightMax);
		at24cxx_write_one_byte(63,AirQualityMin);

		at24cxx_write_one_byte(80,0xA0);
	}
	//������������ݣ�ʵ�ֵ��籣�湦��
	TemperatureMax = at24cxx_read_one_byte(60);
	HumidityMax = at24cxx_read_one_byte(61);
	LightMax = at24cxx_read_one_byte(62);
	AirQualityMin = at24cxx_read_one_byte(63);

	 //**********���dht11��ʪ�ȴ������Ƿ�����**********
//	if(dht11_init()) /* DHT11��ʼ�� */
//		{
//			lcd_show_string(30, 50, 200, 16, 16, "DHT11 Error", RED);
//			//delay_ms(200);//������������ʾdht11δ����
//			lcd_fill(30, 50, 239, 70 + 16, WHITE);//30, 50, 239, 70 + 20, WHITE
//			//delay_ms(200);
//		}
//        else
//		{
//			lcd_show_string(30, 50, 200, 16, 16, "DHT11 OK", RED);
//		    lcd_show_string(30, 70, 200, 16, 16, "Temp:  C", BLUE);
//			lcd_show_string(30, 90, 200, 16, 16, "Humi:  %", BLUE);
//		}
//	lcd_show_string(30, 110, 200, 16, 16, "Ligh:   ", BLUE);
//	lcd_show_string(30, 130, 200, 16, 16, "Airq:   ", BLUE);
	
	while(1)
   {
	
	    /**********��������ֵ��ʾ����**********/	
//		if(t % 12 == 0)  //300msִ��һ��  300/25=12
//		{
//			lcd_show_num(30 + 40, 70, Temperature, 2, 16, RED); /* ��ʾ�¶� */
//			lcd_show_num(30 + 40, 90, Humidity, 2, 16, RED);    /* ��ʾʪ�� */
//			lcd_show_num(30 + 40, 110, Light, 3, 16, RED); /* ��ʾ����ǿ�� */
//			lcd_show_num(30 + 40, 130, AirQuality, 3, 16, RED);    /* ��ʾ�������� */
//		}
	    LED1_Status =((uint8_t)HAL_GPIO_ReadPin(LED1_GPIO_PORT, LED1_GPIO_PIN));     /* ��ȡLED1���� */
		BEEP1_Status =((uint8_t)HAL_GPIO_ReadPin(BEEP1_GPIO_PORT, BEEP1_GPIO_PIN));  /* ��ȡBEEP1���� */
		/**********1s��ȡһ�λ���ֵ���жϱ���***********/  //��������Ҳ���Ե�������   
		if(t % 40 == 0) //  1000/25=40
		{
			dht11_read_data(&Temperature, &Humidity);             /* ��ȡ��ʪ��ֵ */
			Light = lsens_get_val(my_get_value(2, 2, g_adc_dma_buf, DATA_NUM)); 
			AirQuality = airqu_get_val(my_get_value(2, 1, g_adc_dma_buf, DATA_NUM)); 
			UsartPrintf(USART_DEBUG,"��ǰ�¶�Ϊ:%dC\n��ǰʪ��Ϊ:%d%%",Temperature,Humidity);
			UsartPrintf(USART_DEBUG,"��ǰ����ǿ��Ϊ:%d\n��ǰ��������Ϊ:%d",Light,AirQuality);
			/*****************�ж��Ƿ񱨾�***************/ //���°���key0����alarm_is_freeΪ0��������������10s�󻷾���������ֵ����������
			if(alarm_is_free == 10)
			{
				if((Temperature < TemperatureMax) && (Humidity < HumidityMax) && (Light < LightMax) && (AirQuality > AirQualityMin)) alarm_flag = 0;
				else alarm_flag = 1;		
			}		
			if(alarm_is_free < 10) alarm_is_free++;	//ÿ��1s alarm_is_free+1		
			
		}
		
		/*****************���ڳ�����֤***************/  //���ڽ�����������
//		unsigned char ch1[]="USART1YES";
//		unsigned char ch2[]="USART2YES";
//		if(t % 10 == 0) 
//		{
//			Usart_SendString(USART1,ch1,9);
//			Usart_SendString(USART2,ch2,9);//Ҫͨ��PA2��PA3��TTLת���ڲ��ܼ�⵽�Ƿ��յ�����
//			USART_SendData(USART1,122);
//			USART_SendData(USART2,0);			
//			UsartPrintf(USART1,"usart%dyes",1);
//			UsartPrintf(USART2,"usart%dyes",2);		
//		}
		/*****************XXXXXXXXXX***************/		
		/*****************MQTT����/������������***************/  //�������
		dataPtr = ESP8266_GetIPD(3);   //��������·�ָ��  ִ����һ��������Ҫ15ms,��ôִ��һ��while(1)��Ҫ25ms
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
		
		if(++timeCount >= 120)		//���ͼ��5s   5s�ϴ�һ������  5000/25=200    �Ӵ���Ƶ�ʣ������������
		{
			UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");
			sprintf(PUB_BUF,"{\"Humi\":%d,\"Temp\":%d,\"Light\":%d,\"Airq\":%d,\"Led\":%d,\"Beep\":%d}",Humidity,
			Temperature,Light,AirQuality,LED1_Status ? 0 : 1,BEEP1_Status ? 0 : 1);
			OneNet_Publish(devPubTopic, PUB_BUF);
			//OneNet_Publish(devPubTopic, "MQTT Publish Test");
			timeCount = 0;
			ESP8266_Clear();
		}
		if(tp_dev.scan(0))
        {           
            //DEBUG_LOG("�жϳɹ�����������Ϊ��x:%d,y:%d\r\n",tp_dev.x[0],tp_dev.y[0]);
            //while(tp_dev.scan(0)) delay_ms(30);//ֻ��ȡһ�δ��������꣬�𵽷�������  //�ȴ����ɿ�ִ���������
			while(tp_dev.sta & 0x80) delay_ms(50);
            if(Lcd_Page >= 1 && Lcd_Page <= 4)//ֻ�����л�һ������ҳ���ʱ����������ã�Ŀǰһ����7��ģ�飩
            {
                changeflag=1;//ҳ���л�������־λ,������жϺ�����LCD_Clear(WHITE)�������õ�BUG
                if(tp_dev.x[0] > 60 && tp_dev.x[0] < 108 && tp_dev.y[0] > 210 && tp_dev.y[0] < 258)//����������
                {
                    lcd_clear(WHITE);
                    Lcd_Page--;//LCD����ҳ��
                    if(Lcd_Page<1)
                    Lcd_Page=4;
                }
                else if(tp_dev.x[0]>340 && tp_dev.x[0]<388 && tp_dev.y[0] > 210 && tp_dev.y[0] < 258)//��������Ҽ�
                {
                        lcd_clear(WHITE);
                        Lcd_Page++;//LCD����ҳ��
                        if(Lcd_Page>4)
                        Lcd_Page=1;
                }
                else if(tp_dev.x[0]>160 &&tp_dev.x[0]<288 && tp_dev.y[0]>160&&tp_dev.y[0]<288)//���ѡ�ж�Ӧ����ҳ��
                {
                    if(Lcd_Page==1)
                    {
                        lcd_clear(WHITE);
                        Lcd_Page=5;
                    }
                    if(Lcd_Page==2)
                    {
                        lcd_clear(WHITE);
                        Lcd_Page=6;
                    }
                    if(Lcd_Page==3)
                    {
                        lcd_clear(WHITE);
                        Lcd_Page=7;
                    }
                    if(Lcd_Page==4)
                    {
                        lcd_clear(WHITE);
                        Lcd_Page=8;
                    }
                }
             
            }
            if(Lcd_Page == 5)
            {
                if(tp_dev.x[0]>300 && tp_dev.x[0]<332 && tp_dev.y[0]>128 && tp_dev.y[0]<160)
                {
                    if(LED1_Status == 1 )
                    {
                        LED1_Status = 0;
                        LED1(0);
                    }
                    else
                    {
                        LED1_Status = 1;
                        LED1(1);
                    }
                }
                else if(tp_dev.x[0]>300&&tp_dev.x[0]<332 && tp_dev.y[0]>178&&tp_dev.y[0]<210)
                {
                    if(Curtain_Status == 1 )
                    {
                        Curtain_Status = 0;
                        lastmove = 1;
                    }
                    else
                    {
                        Curtain_Status = 1;
                        lastmove = 0;
                    }
                }
                else if(tp_dev.x[0]>300&&tp_dev.x[0]<332 && tp_dev.y[0]>228&&tp_dev.y[0]<260)
                {
                    if(Windows_Status == 1 )
                    {
                        Windows_Status = 0;
                        Servo_SetAngle(90);
                    }
                    else
                    {
                        Windows_Status = 1;
                        Servo_SetAngle(0);
                    }
                }
                else if(tp_dev.x[0]>300&&tp_dev.x[0]<332 && tp_dev.y[0]>278&&tp_dev.y[0]<310)
                {
                    if(BEEP1_Status == 1 )
                    {
                        BEEP1_Status = 0;
                        BEEP1(0);
                    }
                    else
                    {
                        BEEP1_Status = 1;
                        BEEP1(1);
                    }
                }
                else if(tp_dev.x[0]>60 && tp_dev.x[0]<108 && tp_dev.y[0]>362 && tp_dev.y[0]<410)//������ҳ��
                {
                    lcd_clear(WHITE);
                    changeflag=1;//ҳ���л�������־λ,������жϺ�����LCD_Clear(WHITE)�������õ�BUG
                    Lcd_Page=1;
                }
            }
            if(Lcd_Page == 6)
            {
                if(tp_dev.x[0]>80 && tp_dev.x[0]<200 && tp_dev.y[0]>110 && tp_dev.y[0]<340)
                {
                        HomeMode = 1;
                }
                if(tp_dev.x[0]>240 &&tp_dev.x[0]<360 && tp_dev.y[0]>110&&tp_dev.y[0]<340)
                {
                        HomeMode = 0;
                }
                else if(tp_dev.x[0]>60&&tp_dev.x[0]<108 && tp_dev.y[0]>362&&tp_dev.y[0]<410)//������ҳ��
                {
                    lcd_clear(WHITE);
                    changeflag=1;//ҳ���л�������־λ,������жϺ�����LCD_Clear(WHITE)�������õ�BUG
                    Lcd_Page=2;
                }
            }
            if(Lcd_Page == 7)
            {
				
                if(tp_dev.x[0]>300&&tp_dev.x[0]<320 && tp_dev.y[0]>128&&tp_dev.y[0]<152)
                    AirQualityMin++;
                else if(tp_dev.x[0]>320&&tp_dev.x[0]<340 && tp_dev.y[0]>128&&tp_dev.y[0]<152)
                    AirQualityMin--;
                else if(tp_dev.x[0]>300&&tp_dev.x[0]<320 && tp_dev.y[0]>178&&tp_dev.y[0]<202)
                    TemperatureMax++;
                else if(tp_dev.x[0]>320&&tp_dev.x[0]<340 && tp_dev.y[0]>178&&tp_dev.y[0]<202)
                    TemperatureMax--;
                else if(tp_dev.x[0]>300&&tp_dev.x[0]<320 && tp_dev.y[0]>228&&tp_dev.y[0]<252)
                    HumidityMax++;
                else if(tp_dev.x[0]>230&&tp_dev.x[0]<340 && tp_dev.y[0]>228&&tp_dev.y[0]<252)
                    HumidityMax--;
                else if(tp_dev.x[0]>300&&tp_dev.x[0]<320 && tp_dev.y[0]>278&&tp_dev.y[0]<302)
                    LightMax++;
                else if(tp_dev.x[0]>230&&tp_dev.x[0]<340 && tp_dev.y[0]>278&&tp_dev.y[0]<302)
                    LightMax--;
                else if(tp_dev.x[0]>60&&tp_dev.x[0]<108 && tp_dev.y[0]>362&&tp_dev.y[0]<410)//������ҳ��
                {
                    lcd_clear(WHITE);
                    changeflag=1;//ҳ���л�������־λ,������жϺ�����LCD_Clear(WHITE)�������õ�BUG
                    Lcd_Page=3;
                }
				//��AT24C02��д��Ķ������ֵ
				at24cxx_write_one_byte(60,TemperatureMax);
				at24cxx_write_one_byte(61,HumidityMax);
				at24cxx_write_one_byte(62,LightMax);
				at24cxx_write_one_byte(63,AirQualityMin);
            }
            if(Lcd_Page == 8)
            {
//                if(tp_dev.x[0]>200&&tp_dev.x[0]<232 && tp_dev.y[0]>128&&tp_dev.y[0]<160)
//                {
//                    if(LED1_Status == 1 )
//                    {
//                        LED1_Status = 0;
//                        LED1(0);
//                    }
//                    else
//                    {
//                        LED1_Status = 1;
//                        LED1(1);
//                    }
//                } else
                if(tp_dev.x[0]>60&&tp_dev.x[0]<108 && tp_dev.y[0]>362&&tp_dev.y[0]<410)//������ҳ��
                {
                    lcd_clear(WHITE);
                    changeflag=1;//ҳ���л�������־λ,������жϺ�����LCD_Clear(WHITE)�������õ�BUG
                    Lcd_Page=3;
                }
            }
        }
		if(changeflag==1)
		{
			changeflag=0;
			lcd_clear(WHITE);
		}		
        LCD_ShowPage(Lcd_Page);
		lcd_show_string(170, 400, 200, 16, 16, "STM32", RED);
        lcd_show_string(170, 420, 200, 16, 16, "RTC TEST", RED);
        lcd_show_string(170, 440, 200, 16, 16, "ATOM@ALIENTEK", RED);
		
		rtc_get_time();
        sprintf((char *)tbuf, "Time:%02d:%02d:%02d", calendar.hour,
        calendar.min, calendar.sec);
        lcd_show_string(170, 470, 210, 16, 16, (char *)tbuf, RED);
        sprintf((char *)tbuf, "Date:%04d-%02d-%02d", calendar.year,
        calendar.month, calendar.date);
        lcd_show_string(170, 490, 210, 16, 16, (char *)tbuf, RED);
        sprintf((char *)tbuf, "Week:%s", weekdays[calendar.week]);
        lcd_show_string(170, 510, 210, 16, 16, (char *)tbuf, RED);
		if(t % 40 == 0) LED0_TOGGLE(); //LED0���,1s�л�״̬����ʾ�������� 1000/25=40
       	  	
		delay_ms(10);
		t++;
		 if (t == 120)//���Ҫȡ���ϸ���tȡ��������С������
        {
            t = 0;         
        }
    
	}		
}
 
