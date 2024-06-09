#include "ioCC2530.h"
#include "./uart/hal_uart.h"
#define uint unsigned int

#define ConversionNum 20

//定义控制灯的端口
#define led1 P1_0
#define led2 P1_1

void Delay(uint);
void InitialAD(void);

char adcdata[]=" 0.0V ";

/****************************
//延时函数
*****************************/
void Delay(uint n)
{
    uint i,t;
    for(i = 0;i<5;i++)
    for(t = 0;t<n;t++);
}

/****************************************************************
*函数功能 ：初始化ADC						*
*入口参数 ：无					        	*
*返 回 值 ：无							*
*说    明 ：参考电压AVDD，转换对象是AVDD			*
****************************************************************/
void InitialAD(void)
{
    P1DIR = 0x03; 	//P1控制LED
    led1 = 1;
    led2 = 1;		//关LED

    ADCCON1 &= ~0X80;	//清EOC标志	
    ADCCON3=0xbf;	//单次转换,参考电压为电源电压，对1/3 AVDD进行A/D转换
						//12位分辨率
    ADCCON1 = 0X30;	//停止A/D
    ADCCON1 |= 0X40;	//启动A/D
}

/****************************************************************
*函数功能 ：主函数						*
*入口参数 ：无							*
*返 回 值 ：无							*
*说    明 ：无							*
****************************************************************/
void main(void)
{	
    char temp[2];
    float num;
    InitUart();               //  baudrate: 57600
    InitialAD();              //  初始化ADC

    led1 = 1;
    while(1)
    {
        if(ADCCON1>=0x80)
        {
            led1 = 1;	  		//转换完毕指示
            temp[1] = ADCL;
            temp[0] = ADCH;
            ADCCON1 |= 0x40;	  	//开始下一转换

            temp[1] = temp[1]>>2;           //数据处理
            temp[1] |= temp[0]<<6;

            temp[0] = temp[0]>>2;	
            temp[0] &= 0x3f;

            num = (temp[0]*256+temp[1])*3.3/4096;  //12位， 取2^12;
            num = num/2+0.05;           //四 舍五入处理
            //定参考电压为3.3V。12位精确度
            adcdata[1] = (char)(num)%10+48;
            adcdata[3] = (char)(num*10)%10+48;

            prints(adcdata);   //将模拟电压值发送到串口
            
            Delay(30000);
            led1 = 0;                       //完成数据处理
            Delay(30000);  	
        }
    }
}

