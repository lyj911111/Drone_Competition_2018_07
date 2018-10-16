/*
 * 드론 경진 대회 문제.
 *
 * Created: 2018-07-12 오전 9:03:00
 *  팀원 : 이원재, 박유빈, 최재운
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "USART.h"
int i;
int cnt;
int cnt2;

int main(void)
{
	char str1[10] = "0";
	char str2[10] = "LED 1 ON";
	char str3[10] = "LED 1 OFF";
	DDRA=0xff;
	USART1_ini(115200);
	while (1)
	{
		i=0;
		USART1_gets(str1);
		
		while(str1[i]!=0)
		{
			if(str1[i]==str2[i])
			cnt++;
			if(str1[i]==str3[i])
			cnt2++;
			i++;
			if(i==4)
			i++;
		}
		if(cnt==7)
		{
			PORTA |= (1 << str1[4]);
		}
		if(cnt2==8)
		{
			PORTA &= ~(1 << str1[4]);
		}
		cnt=0;
		cnt2=0;
	}
}

