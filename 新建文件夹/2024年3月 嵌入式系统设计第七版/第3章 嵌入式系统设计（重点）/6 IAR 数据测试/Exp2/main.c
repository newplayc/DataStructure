#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

#define LED1 P1_0
#define LED2 P1_1

uint counter=0;				//ͳ���������
uint TempFlag;				//������־�Ƿ�Ҫ��˸

void Initial(void);
void Delay(uint);

/****************************
//��ʱ����
***************************/
void Delay(uint n)
{
    uint i,t;
    for(i = 0;i<5;i++)
    for(t = 0;t<n;t++);
}

/****************************
//��ʼ������
***************************/
void Initial(void)
{
    //��ʼ��P1
    P1DIR = 0x03; 	//P1_0 P1_1Ϊ���
    LED1 = 1;
    LED2 = 1;		//Ϩ��LED
  
    //��ʼ��T1��ʱ��
    T1CTL = 0x0d;	//�ж���Ч,128��Ƶ;�Զ���װģʽ(0x0000->0xffff);
  }

/***************************
//������
***************************/
void main()
{
    Initial(); 	 //���ó�ʼ������
    LED1 = 0;	 //����LED1
    while(1)   	 //��ѯ���
    {
        if(IRCON > 0)
        {
            IRCON = 0;                //�������־
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
