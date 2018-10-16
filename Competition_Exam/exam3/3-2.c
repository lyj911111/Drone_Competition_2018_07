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

//128분주비, 125
// OCRnX : 타이머/카운터 비교출력 레지스터
#define ROTOR_L_U  OCR3B		// 3번카운터 Compare Output Resistor (16bit),
#define ROTOR_R_U  OCR1B		// 1번카운터 비교매치 B 값 변수
#define ROTOR_L_D  OCR3A		// 3번카운터 비교매치 A
#define ROTOR_R_D  OCR3C		// 3번카운터 비교매치 C

int cnt;
int cnt2=1;			// 4-3
int cnt3=0;
int state=5;		// 3-3, 4-2
int state2=0;		// 3-3
int state3=0;
int i=0;			// 3-3

ISR(TIMER0_COMP_vect)
{
	//3-2
	if(++cnt==cnt2)
	{
		if(cnt2!=500)
			cnt2++;
		else
			TIMSK=0X00;
		cnt=0;
		if(PORTA==0x00)
			PORTA=0X80;
		else
			PORTA>>=1;
	}
}

int main(void)
{
	DDRA = 0xff;
	DDRB = 0xFF;
	DDRE = 0xFF;
	
	TCCR0 = 0b00001101; // 128분주비, ctc
	OCR0 = 124;			// 1ms
	TIMSK = 0x02;

	TCCR1A = 0b00100011;	// Fast PWM 10bit (1024 까지 사용), 타이머 1의 B 비교매치 클리어.
	TCCR1B = 0b00001011;	// 64분주 사용.
	
	// 타이머3 사용.(16bit짜리)
	TCCR3A = 0b10101011;	// Fast PWM 10bit (1024 까지 사용), 타이머 3의 A,B,C를 비교매치 클리어.
	TCCR3B = 0b00001011;	// 64분주 사용.
	ROTOR_L_U = 0;		// OCR3B 값 대입. (비교매치값)
	ROTOR_R_U = 0;		// OCR1B 값 대입. (비교매치값)
	ROTOR_R_D = 0;		// OCR3A 값 대입. (비교매치값)
	ROTOR_L_D = 0;		// OCR3C 값 대입. (비교매치값)
	sei();
	
	PORTA=0X80;//3-1, 3-2
	//PORTA=0xff; // 4-1
	
    while (1) 
    {

	}
}

