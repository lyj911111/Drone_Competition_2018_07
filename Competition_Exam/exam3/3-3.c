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
	// 3-3
	if(++cnt==2)
	{
		cnt=0;
		if(i<1000 && state2==0)
			i++;
		else if(i>=1000 && state2==0)
		{
			state2=1;
			i--;
		}
		else if(state2==1)
		{
			if(i>0)
				i--;
			else
			{
				state2=0;
				state++;
			}
		}
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

	//PORTA=0xff; // 4-1
	
    while (1) 
    {
		if(state==4)
		{
			cnt3++;
			if(cnt3==3)
			{
				state2=3;
				ROTOR_L_U = 0;		// OCR3B 값 대입. (비교매치값)
				ROTOR_R_U = 0;		// OCR1B 값 대입. (비교매치값)
				ROTOR_R_D = 0;		// OCR3A 값 대입. (비교매치값)
				ROTOR_L_D = 0;		// OCR3C 값 대입. (비교매치값)
				PORTA=0x00;
				state=5;
			}
			else
			state=0;
		}
		if(state==0)
		{
			ROTOR_L_U = i;
			PORTA=0b00110000;
		}
		
		if(state==1)
		{
			ROTOR_R_U = i;
			PORTA=0b11000000;
		}
		
		if(state==2)
		{
			ROTOR_R_D = i;
			PORTA=0b00000011;
		}
		if(state==3)
		{
			ROTOR_L_D = i;
			PORTA=0b00001100;
		}
	}
}

