#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制LED灯的端口
#define LED1 P1_0	//定义LED1为P10口控制
#define LED2 P1_1	//定义LED2为P11口控制

//函数声明
void Delay(uint);		//延时函数
void Initial(void);		//初始化P1口

/****************************
//延时函数
*****************************/
void Delay(uint n)
{
	uint i,t;
        for(i = 0;i<5;i++)
	for(t = 0;t<n;t++);
}

/****************************
//初始化程序
*****************************/
void Initial(void)
{
	P1DIR |= 0x03; //P1_0、P1_1定义为输出

	LED1 = 1;       //LED1灯熄灭
	LED2 = 1;	//LED2灯熄灭
}

/***************************
//主函数
***************************/
void main(void)
{
	Initial();		//调用初始化函数
	LED1 = 0;		//LED1点亮
	LED2 = 0;		//LED2点亮
	while(1)
	{
           LED2 = !LED2;        //LED2闪烁
           Delay(50000);
	}
}
