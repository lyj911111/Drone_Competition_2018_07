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
int state3=0;
int state2=0;
int i=0;

ISR(TIMER0_COMP_vect)
{	
	if(state2==0)
	{
		if(++cnt==500)
		{
			cnt=0;
			PORTA<<=1;
			if(PORTA==0x00)
			{
				state2=1;
				PORTA=0x80;
				ROTOR_L_U = 205;		// OCR3B 값 대입. (비교매치값) -> 0~1023이므로 20%는 약 205
				ROTOR_R_U = 205;		// OCR1B 값 대입. (비교매치값)
				ROTOR_R_D = 205;		// OCR3A 값 대입. (비교매치값)
				ROTOR_L_D = 205;
			}
		}
	}
	if(state2==1)
	{
		if(++cnt==200)
		{
			cnt=0;
			if(PORTA==0x01)
			PORTA=0X80;
			else
			PORTA>>=1;
		}
		if(++cnt2==3000)
		{
			ROTOR_L_U = 0;		// OCR3B 값 대입. (비교매치값)
			ROTOR_R_U = 0;		// OCR1B 값 대입. (비교매치값)
			ROTOR_R_D = 0;		// OCR3A 값 대입. (비교매치값)
			ROTOR_L_D = 0;		// OCR3C 값 대입. (비교매치값)
			state2=2;
			cnt=0;
			cnt2=0;
			state=0;
		}
	}
	if(state2==2)
	{
		if(++cnt==200)
		{
			cnt=0;
			if(PORTA==0x01)
			PORTA=0X80;
			else
			PORTA>>=1;
		}
		if(++cnt2==2)
		{
			cnt2=0;
			if(i<500 && state3==0)
			i++;
			else if(i>=500 && state3==0)
			{
				state3=1;
				i--;
			}
			else if(state3==1)
			{
				if(i>0)
				i--;
				else
				{
					state3=0;
					state++;
				}
			}
		}
	}
}

int main(void)
{
	DDRA = 0xFF;
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

	PORTA=0xFF; 
	
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
			//PORTA=0b00110000;
		}
		
		if(state==1)
		{
			ROTOR_R_U = i;
			//PORTA=0b11000000;
		}
		
		if(state==2)
		{
			ROTOR_R_D = i;
			//PORTA=0b00000011;
		}
		if(state==3)
		{
			ROTOR_L_D = i;
			//PORTA=0b00001100;
		}
	}
}

