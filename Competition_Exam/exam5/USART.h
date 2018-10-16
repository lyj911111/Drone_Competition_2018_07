#include <avr/io.h>
#include <stdio.h>

#ifndef _USART_H_
#define _USART_H_

void USART0_ini(unsigned long int bitrate)				//9600,14400,19200,28800,38400,57600,76800,115200
{
	UCSR0A = 0x00;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

	if(bitrate==9600){
		UBRR0H = 0x00;
		UBRR0L = 103;
	}
	else if(bitrate==14400){
		UBRR0H = 0x00;
		UBRR0L = 68;
	}
	else if(bitrate==19200){
		UBRR0H = 0x00;
		UBRR0L = 51;
	}
	else if(bitrate==28800){
		UBRR0H = 0x00;
		UBRR0L = 34;
	}
	else if(bitrate==38400){
		UBRR0H = 0x00;
		UBRR0L = 25;
	}
	else if(bitrate==57600){
		UBRR0H = 0x00;
		UBRR0L = 16;
	}
	else if(bitrate==76800){
		UBRR0H = 0x00;
		UBRR0L = 12;
	}
	else if(bitrate==115200){
		UBRR0H = 0x00;
		UBRR0L = 8;
	}
	else;
}
void USART1_ini(unsigned long int bitrate)				//9600,14400,19200,28800,38400,57600,76800,115200
{
	UCSR1A = 0x00;
	UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);

	if(bitrate==9600){
		UBRR1H = 0x00;
		UBRR1L = 103;
	}
	else if(bitrate==14400){
		UBRR1H = 0x00;
		UBRR1L = 68;
	}
	else if(bitrate==19200){
		UBRR1H = 0x00;
		UBRR1L = 51;
	}
	else if(bitrate==28800){
		UBRR1H = 0x00;
		UBRR1L = 34;
	}
	else if(bitrate==38400){
		UBRR1H = 0x00;
		UBRR1L = 25;
	}
	else if(bitrate==57600){
		UBRR1H = 0x00;
		UBRR1L = 16;
	}
	else if(bitrate==76800){
		UBRR1H = 0x00;
		UBRR1L = 12;
	}
	else if(bitrate==115200){
		UBRR1H = 0x00;
		UBRR1L = 8;
	}
	else;
}

char USART0_getch()
{
	while(!(UCSR0A&(1<<RXC0)));
	return UDR0;
}
void USART0_put(char c)
{
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=c;
}
void USART0_puts(char* string)
{
	while(*string)
	USART0_put(*(string++));
}
char USART1_getch()
{
	while(!(UCSR1A&(1<<RXC1)));
	return UDR1;
}
void USART1_gets(char str[])
{
	/*while(*str!=0x00){
		USART1_getch(* str);
		str++;
	}*/
	int i=0;
	do{
		str[i]=USART1_getch();
	}while(str[i++]!='\r');
	str[i-1]='0';
}
void USART1_put(char c)
{
	while(!(UCSR1A&(1<<UDRE1)));
	UDR1=c;
}
void USART1_puts(char* string)
{
	while(*string)
	USART1_put(*(string++));
}

#endif


