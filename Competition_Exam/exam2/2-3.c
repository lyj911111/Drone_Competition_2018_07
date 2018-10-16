/*
 * 드론 경진 대회 문제.
 *
 * Created: 2018-07-12 오전 9:03:00
 *  팀원 : 이원재, 박유빈, 최재운
 */ 
#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__ 1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// OCRnX : 타이머/카운터 비교출력 레지스터
#define ROTOR_L_U  OCR3B		// 3번카운터 Compare Output Resistor (16bit),
#define ROTOR_R_U  OCR1B		// 1번카운터 비교매치 B 값 변수
#define ROTOR_L_D  OCR3A		// 3번카운터 비교매치 A
#define ROTOR_R_D  OCR3C		// 3번카운터 비교매치 C

int main(void)
{
    DDRA=0xFF;
	
	PORTA=0x80;
	
	DDRB = 0xFF;		// B포트 모드 output 설정
	DDRE = 0xFF;		// E포트 모두 output 설정
	TCCR1A = 0b00100011;	// Fast PWM 10bit (1024 까지 사용), 타이머 1의 B 비교매치 클리어.
	TCCR1B = 0b00001011;	// 64분주 사용.
	
							// 타이머3 사용.(16bit짜리)
    TCCR3A = 0b10101011;	// Fast PWM 10bit (1024 까지 사용), 타이머 3의 A,B,C를 비교매치 클리어.
    TCCR3B = 0b00001011;	// 64분주 사용
	
   ROTOR_L_U = 0;		// OCR3B 값 대입. (비교매치값)
   ROTOR_R_U = 0;		// OCR1B 값 대입. (비교매치값)
   ROTOR_R_D = 0;		// OCR3A 값 대입. (비교매치값) 
   ROTOR_L_D = 0;		// OCR3C 값 대입. (비교매치값)
	
	/* Replace with your application code */
    while (1) 
    {
		//2-3
		for(int i=0;i<1000;i++)
		{
			ROTOR_L_U = i;

			_delay_ms(2);
		}
		for(int i=999;i>=0;i--)
		{
			ROTOR_L_U = i;
			_delay_ms(2);
		}
		
		for(int i=0;i<1000;i++)
		{
			ROTOR_R_U = i;

			_delay_ms(2);
		}
		for(int i=999;i>=0;i--)
		{
			ROTOR_R_U = i;
			_delay_ms(2);
		}
		
		for(int i=0;i<1000;i++)
		{
			ROTOR_R_D = i;

			_delay_ms(2);
		}
		for(int i=999;i>=0;i--)
		{
			ROTOR_R_D = i;
			_delay_ms(2);
		}
		
		for(int i=0;i<1000;i++)
		{
			ROTOR_L_D = i;

			_delay_ms(2);
		}
		for(int i=999;i>=0;i--)
		{
			ROTOR_L_D = i;
			_delay_ms(2);
		}
	}
    }
}

