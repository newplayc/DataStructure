#include "ioCC2530.h"
#include "./uart/hal_uart.h"
#define uint unsigned int

#define ConversionNum 20

//������ƵƵĶ˿�
#define led1 P1_0
#define led2 P1_1

void Delay(uint);
void InitialAD(void);

char adcdata[]=" 0.0V ";

/****************************
//��ʱ����
*****************************/
void Delay(uint n)
{
    uint i,t;
    for(i = 0;i<5;i++)
    for(t = 0;t<n;t++);
}

/****************************************************************
*�������� ����ʼ��ADC						*
*��ڲ��� ����					        	*
*�� �� ֵ ����							*
*˵    �� ���ο���ѹAVDD��ת��������AVDD			*
****************************************************************/
void InitialAD(void)
{
    P1DIR = 0x03; 	//P1����LED
    led1 = 1;
    led2 = 1;		//��LED

    ADCCON1 &= ~0X80;	//��EOC��־	
    ADCCON3=0xbf;	//����ת��,�ο���ѹΪ��Դ��ѹ����1/3 AVDD����A/Dת��
						//12λ�ֱ���
    ADCCON1 = 0X30;	//ֹͣA/D
    ADCCON1 |= 0X40;	//����A/D
}

/****************************************************************
*�������� ��������						*
*��ڲ��� ����							*
*�� �� ֵ ����							*
*˵    �� ����							*
****************************************************************/
void main(void)
{	
    char temp[2];
    float num;
    InitUart();               //  baudrate: 57600
    InitialAD();              //  ��ʼ��ADC

    led1 = 1;
    while(1)
    {
        if(ADCCON1>=0x80)
        {
            led1 = 1;	  		//ת�����ָʾ
            temp[1] = ADCL;
            temp[0] = ADCH;
            ADCCON1 |= 0x40;	  	//��ʼ��һת��

            temp[1] = temp[1]>>2;           //���ݴ���
            temp[1] |= temp[0]<<6;

            temp[0] = temp[0]>>2;	
            temp[0] &= 0x3f;

            num = (temp[0]*256+temp[1])*3.3/4096;  //12λ�� ȡ2^12;
            num = num/2+0.05;           //�� �����봦��
            //���ο���ѹΪ3.3V��12λ��ȷ��
            adcdata[1] = (char)(num)%10+48;
            adcdata[3] = (char)(num*10)%10+48;

            prints(adcdata);   //��ģ���ѹֵ���͵�����
            
            Delay(30000);
            led1 = 0;                       //������ݴ���
            Delay(30000);  	
        }
    }
}

