#include "ioCC2530.h"

void Delay(unsigned char n)
{
  unsigned char i;
  unsigned int j;
  for(i=0;i<n;i++)
    for(j=1;j<1000;j++);
}

void main(void)
{
  P1SEL=0x00;     //P1.0Ϊ��ͨI/O��
  P1DIR=0x3;       //P1.0 P1.0���
  while(1)
  {
    P1_1=1;
    Delay(10);
    P1_0=0;
    Delay(10);
    P1_1=0;
    Delay(10);
    P1_0=1;
    Delay(10);
  }
}
