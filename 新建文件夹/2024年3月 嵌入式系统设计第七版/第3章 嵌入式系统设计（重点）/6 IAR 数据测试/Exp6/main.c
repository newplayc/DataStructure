/* ����ͷ�ļ� */
/********************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "./uart/hal_board_cfg.h"
#include "./uart/hal_uart.h"
#include "./sht11/sht11.h"
/********************************************************************/
//������ƵƵĶ˿�
#define LED1 P1_0
#define LED2 P1_1

#define uint unsigned int
#define uchar unsigned char

void LedInit(void)
{
  P1DIR |= 0x03; //����LED
  LED1 = 1;
  LED2 = 1;
}
/*********************************************************************
 * �������ƣ�main
 * ��    �ܣ�main�������
 * ��ڲ�������
 * ���ڲ�������
 * �� �� ֵ����
 ********************************************************************/
void main(void)
{
    char temp_buf[10];
    char humi_buf[10];
    float humi,temp;
    
    LED1 = 0;       //LED1��������ʾ��������
    InitUart();     // ��ʼ������   bautrate:57600
    Sht11Init();   
    
    while(1)
    {
        if(GetHumiAndTemp(&humi,&temp) == 0)
        {
             sprintf(humi_buf, (char *)"%f", humi);
             sprintf(temp_buf, (char *)"%f", temp);
      
             prints("temp:");	 prints(temp_buf);	
             prints("     humi:");	 prints(humi_buf);	
             prints("\r\n");
             
             Sht11Delay(50000);  
             Sht11Delay(50000);   
             Sht11Delay(50000);  
             
             LED2 = !LED2;           //LED2��˸����ʾ��ʪ�Ȳ�������
        }
    }
}
