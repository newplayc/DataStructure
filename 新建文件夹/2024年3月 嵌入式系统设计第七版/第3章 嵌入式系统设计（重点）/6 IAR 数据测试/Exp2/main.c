#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

#define LED1 P1_0
#define LED2 P1_1

uint counter=0;				//统计溢出次数
uint TempFlag;				//用来标志是否要闪烁

void Initial(void);
void Delay(uint);

/****************************
//延时程序
***************************/
void Delay(uint n)
{
    uint i,t;
    for(i = 0;i<5;i++)
    for(t = 0;t<n;t++);
}

/****************************
//初始化程序
***************************/
void Initial(void)
{
    //初始化P1
    P1DIR = 0x03; 	//P1_0 P1_1为输出
    LED1 = 1;
    LED2 = 1;		//熄灭LED
  
    //初始化T1定时器
    T1CTL = 0x0d;	//中断无效,128分频;自动重装模式(0x0000->0xffff);
  }

/***************************
//主函数
***************************/
void main()
{
    Initial(); 	 //调用初始化函数
    LED1 = 0;	 //点亮LED1
    while(1)   	 //查询溢出
    {
        if(IRCON > 0)
        {
            IRCON = 0;                //清溢出标志
            TempFlag = !TempFlag;
        }
        if(TempFlag)
        {
            LED2 = LED1;
            LED1 = !LED1;
            Delay(6000);
        }
    }
}
