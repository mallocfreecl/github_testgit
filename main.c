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
uint8_t TemperatureMax = 30;//允许(不报警)的最大值//超过该值报警
uint8_t HumidityMax = 70;
uint8_t LightMax = 50;      
uint8_t AirQualityMin = 50;//允许(不报警)的最小值//低过该值报警

//新增标志位
uint8_t Lcd_Page = 1;//LCD功能页面
uint8_t changeflag;
uint8_t Curtain_Status;
uint8_t lastmove = 2;//步进电机状态，0:正转 1:反转 2:电机停止 默认停止
uint32_t pulse = 64*64;//pulse = int(double)(angle/5.625)*64(angle为需要旋转的角度）64*64就是360度
uint8_t Windows_Status = 1;//=1默认窗户关着
uint8_t HomeMode;

uint8_t LED1_Status;//黄灯的状态  1:亮  0:熄灭       
uint8_t BEEP1_Status;//非报警蜂鸣器状态 0:响  1:不响  
char* weekdays[]={"Sunday","Monday","Tuesday","Wednesday",
                  "Thursday","Friday","Saterday"};


char PUB_BUF[256];//上传数据的buf
const char *devSubTopic[] = {"/mysmarthome_stm32_8266/sub"};//订阅的主题名
const char devPubTopic[] = {"/mysmarthome_stm32_8266/pub"}; //发布的主题名
	
int main(void)
{
    uint16_t t = 0;
	uint8_t tbuf[40];
    
	unsigned short timeCount = 0;	            //发送间隔变量	
	unsigned char *dataPtr = NULL;

    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
	Usart1_Init(115200);                //DEBUG 串口1
	Usart2_Init(115200);                //STM32_8266通讯串口
    led_init();                         /* 初始化LED */
	beep_init();                        /* 初始化BEEP */   
    lcd_init();                         /* 初始化LCD */
    my_adc_nch_dma_init((uint32_t)&g_adc_dma_buf); /* 初始化ADC3 */
	my_adc_dma_enable(DATA_NUM);
	btim_tim6_int_init(7200-1, 5000);//基本定时器,0.5s的时间更新中断，更新中断执行的是alarm_flag的内容
	Servo_Init();
	key_extix_init();
	dht11_init();
    tp_dev.init();  //有问题
    at24cxx_init();	
	Servo_Init();
	rtc_init();
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	
	ESP8266_Init();					//初始化ESP8266
	while(OneNet_DevLink())			//接入OneNET//连接服务器的函数,连接成功返回0
		delay_ms(500);
	
	BEEP(1);				//鸣叫提示接入成功
	delay_ms(250);
	BEEP(0);
	
	OneNet_Subscribe(devSubTopic, 1);//订阅主题
	
	//系统首次上电，初始化数据
	if(at24cxx_read_one_byte(80)!= 0xA0)
	{
		//向EEPROM中写入需保存的数据
		at24cxx_write_one_byte(60,TemperatureMax);
		at24cxx_write_one_byte(61,HumidityMax);
		at24cxx_write_one_byte(62,LightMax);
		at24cxx_write_one_byte(63,AirQualityMin);

		at24cxx_write_one_byte(80,0xA0);
	}
	//读出保存的数据，实现掉电保存功能
	TemperatureMax = at24cxx_read_one_byte(60);
	HumidityMax = at24cxx_read_one_byte(61);
	LightMax = at24cxx_read_one_byte(62);
	AirQualityMin = at24cxx_read_one_byte(63);

	 //**********检测dht11温湿度传感器是否连接**********
//	if(dht11_init()) /* DHT11初始化 */
//		{
//			lcd_show_string(30, 50, 200, 16, 16, "DHT11 Error", RED);
//			//delay_ms(200);//字体闪动，提示dht11未连接
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
	
	    /**********传感器数值显示部分**********/	
//		if(t % 12 == 0)  //300ms执行一次  300/25=12
//		{
//			lcd_show_num(30 + 40, 70, Temperature, 2, 16, RED); /* 显示温度 */
//			lcd_show_num(30 + 40, 90, Humidity, 2, 16, RED);    /* 显示湿度 */
//			lcd_show_num(30 + 40, 110, Light, 3, 16, RED); /* 显示光照强度 */
//			lcd_show_num(30 + 40, 130, AirQuality, 3, 16, RED);    /* 显示空气质量 */
//		}
	    LED1_Status =((uint8_t)HAL_GPIO_ReadPin(LED1_GPIO_PORT, LED1_GPIO_PIN));     /* 读取LED1引脚 */
		BEEP1_Status =((uint8_t)HAL_GPIO_ReadPin(BEEP1_GPIO_PORT, BEEP1_GPIO_PIN));  /* 读取BEEP1引脚 */
		/**********1s读取一次环境值并判断报警***********/  //报警部分也可以单独出来   
		if(t % 40 == 0) //  1000/25=40
		{
			dht11_read_data(&Temperature, &Humidity);             /* 读取温湿度值 */
			Light = lsens_get_val(my_get_value(2, 2, g_adc_dma_buf, DATA_NUM)); 
			AirQuality = airqu_get_val(my_get_value(2, 1, g_adc_dma_buf, DATA_NUM)); 
			UsartPrintf(USART_DEBUG,"当前温度为:%dC\n当前湿度为:%d%%",Temperature,Humidity);
			UsartPrintf(USART_DEBUG,"当前光照强度为:%d\n当前空气质量为:%d",Light,AirQuality);
			/*****************判断是否报警***************/ //按下按键key0，清alarm_is_free为0，清除警报，如果10s后环境量超过阈值，继续报警
			if(alarm_is_free == 10)
			{
				if((Temperature < TemperatureMax) && (Humidity < HumidityMax) && (Light < LightMax) && (AirQuality > AirQualityMin)) alarm_flag = 0;
				else alarm_flag = 1;		
			}		
			if(alarm_is_free < 10) alarm_is_free++;	//每隔1s alarm_is_free+1		
			
		}
		
		/*****************串口程序验证***************/  //串口接收数据正常
//		unsigned char ch1[]="USART1YES";
//		unsigned char ch2[]="USART2YES";
//		if(t % 10 == 0) 
//		{
//			Usart_SendString(USART1,ch1,9);
//			Usart_SendString(USART2,ch2,9);//要通过PA2，PA3接TTL转串口才能检测到是否收到数据
//			USART_SendData(USART1,122);
//			USART_SendData(USART2,0);			
//			UsartPrintf(USART1,"usart%dyes",1);
//			UsartPrintf(USART2,"usart%dyes",2);		
//		}
		/*****************XXXXXXXXXX***************/		
		/*****************MQTT接收/发布主题内容***************/  //放在最后
		dataPtr = ESP8266_GetIPD(3);   //检查有无下发指令  执行这一条程序需要15ms,那么执行一次while(1)需要25ms
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
		
		if(++timeCount >= 120)		//发送间隔5s   5s上传一次数据  5000/25=200    加大发送频率，更快更新数据
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
            //DEBUG_LOG("中断成功，触摸坐标为：x:%d,y:%d\r\n",tp_dev.x[0],tp_dev.y[0]);
            //while(tp_dev.scan(0)) delay_ms(30);//只获取一次触摸屏坐标，起到防抖功能  //等待手松开执行下面程序
			while(tp_dev.sta & 0x80) delay_ms(50);
            if(Lcd_Page >= 1 && Lcd_Page <= 4)//只有在切换一级功能页面的时候可以起作用（目前一共有7个模块）
            {
                changeflag=1;//页面切换清屏标志位,解决在中断函数中LCD_Clear(WHITE)不起作用的BUG
                if(tp_dev.x[0] > 60 && tp_dev.x[0] < 108 && tp_dev.y[0] > 210 && tp_dev.y[0] < 258)//如果按下左键
                {
                    lcd_clear(WHITE);
                    Lcd_Page--;//LCD功能页面
                    if(Lcd_Page<1)
                    Lcd_Page=4;
                }
                else if(tp_dev.x[0]>340 && tp_dev.x[0]<388 && tp_dev.y[0] > 210 && tp_dev.y[0] < 258)//如果按下右键
                {
                        lcd_clear(WHITE);
                        Lcd_Page++;//LCD功能页面
                        if(Lcd_Page>4)
                        Lcd_Page=1;
                }
                else if(tp_dev.x[0]>160 &&tp_dev.x[0]<288 && tp_dev.y[0]>160&&tp_dev.y[0]<288)//如果选中对应功能页面
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
                else if(tp_dev.x[0]>60 && tp_dev.x[0]<108 && tp_dev.y[0]>362 && tp_dev.y[0]<410)//返回主页面
                {
                    lcd_clear(WHITE);
                    changeflag=1;//页面切换清屏标志位,解决在中断函数中LCD_Clear(WHITE)不起作用的BUG
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
                else if(tp_dev.x[0]>60&&tp_dev.x[0]<108 && tp_dev.y[0]>362&&tp_dev.y[0]<410)//返回主页面
                {
                    lcd_clear(WHITE);
                    changeflag=1;//页面切换清屏标志位,解决在中断函数中LCD_Clear(WHITE)不起作用的BUG
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
                else if(tp_dev.x[0]>60&&tp_dev.x[0]<108 && tp_dev.y[0]>362&&tp_dev.y[0]<410)//返回主页面
                {
                    lcd_clear(WHITE);
                    changeflag=1;//页面切换清屏标志位,解决在中断函数中LCD_Clear(WHITE)不起作用的BUG
                    Lcd_Page=3;
                }
				//向AT24C02中写入改动后的阈值
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
                if(tp_dev.x[0]>60&&tp_dev.x[0]<108 && tp_dev.y[0]>362&&tp_dev.y[0]<410)//返回主页面
                {
                    lcd_clear(WHITE);
                    changeflag=1;//页面切换清屏标志位,解决在中断函数中LCD_Clear(WHITE)不起作用的BUG
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
		if(t % 40 == 0) LED0_TOGGLE(); //LED0红灯,1s切换状态，提示程序运行 1000/25=40
       	  	
		delay_ms(10);
		t++;
		 if (t == 120)//这个要取以上各个t取余对象的最小公倍数
        {
            t = 0;         
        }
    
	}		
}
 
