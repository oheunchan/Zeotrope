#include "Arduino.h"
#include "zDefine.h"
#include "System.h"
#include "PT_Sensor.h"
#include "Motor.h"

void RestFunc()
{
	
	_printf("SOFT RESET\r\n"); \
	Motor_OFF();
	OCR0B=0;
	delay(1000);
	
	digitalWrite(RESET_PIN,LOW);
	delay(100);
	digitalWrite(RESET_PIN,HIGH);
	
}



void _printf(const char *s, ...){

    va_list args;

    va_start(args, s);

    int n = vsnprintf(NULL, 0, s, args);//문자열 길이를 먼저 구함

    char *str = new char[n+1]; //메모리 할당

    vsprintf(str, s, args);//실제 내용을 복사

    va_end(args);

    Serial.print(str);

    delete [] str; //메모리 해제

}

void Timer_Init()
{

//	TCCR0A = 0; //TCCR0A initialize
	TCCR0A |= 0x20;//TCCR0A initialize
	TCCR0B = 0; //TCCR0B initialize
	TCNT0 = 0;  //TCNT0 initialize
	OCR0A= 255;
	OCR0B=0;  
	TCCR0B |= (1<<WGM02);
	TCCR0B |= (1<<CS02) | (0<<CS00);
	TIMSK0 |= (1<<OCIE0A);

}
void Port_init()
{
	digitalWrite(RESET_PIN,HIGH);	//RESET PIN
	pinMode(RESET_PIN,OUTPUT);
//	pinMode(PHOTO_SENSOR,INPUT);
	pinMode(PHOTO_SENSOR, INPUT);
	attachInterrupt(digitalPinToInterrupt(PHOTO_SENSOR), PT_Sensor_Read, RISING); 
	//attachInterrupt(digitalPinToInterrupt(PHOTO_SENSOR), PT_Sensor_OFF, LOW); 
	
	
//	delay(100);
	
}

