#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//�������LED�ƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���
#define LED2 P1_1	//����LED2ΪP11�ڿ���

//��������
void Delay(uint);		//��ʱ����
void Initial(void);		//��ʼ��P1��

/****************************
//��ʱ����
*****************************/
void Delay(uint n)
{
	uint i,t;
        for(i = 0;i<5;i++)
	for(t = 0;t<n;t++);
}

/****************************
//��ʼ������
*****************************/
void Initial(void)
{
	P1DIR |= 0x03; //P1_0��P1_1����Ϊ���

	LED1 = 1;       //LED1��Ϩ��
	LED2 = 1;	//LED2��Ϩ��
}

/***************************
//������
***************************/
void main(void)
{
	Initial();		//���ó�ʼ������
	LED1 = 0;		//LED1����
	LED2 = 0;		//LED2����
	while(1)
	{
           LED2 = !LED2;        //LED2��˸
           Delay(50000);
	}
}
