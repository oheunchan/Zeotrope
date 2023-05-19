
/*
##Zeotrope Project
2023.05.06
- Release Motor 구동 및 코드 정리
- 모터 가감속 및 LED 동작 제어 

2023.03.05
- IR/BT 프로토콜 추가

2023.02.19
- 코드 리팩토링 및 모듈화 작업중

2023.02.06
- Step Motor Test로 구현

2023.01.30
- HC06 LED 동작 테스트
- bluetooth.read()가 1byte로 동작함 Protocol은 3byte이므로 수정 필요

2023.01.29
-HC06 TEST 노트북으로 통신 확인
-IR 동작이 안되서 IRREMOTE V3.9.0으로 다운그레이드 라이브러리 upgrade 하지 말것

2023.01.28
-HC06 TEST 중 아이폰에서 동작하지 않음.

2023.01.26
-리모컨으로 LED 동작 테스트

2023.01.25  
- Timer를 이용한 Task 구현
- LED / IR 구현 

2023.01.24  Start OEC 
*/


#include "zInclude.h"


extern void IR_Test();
extern void Bluetooth();



//Tiemr variable
int timer_Led;
int timer_Ir;
int timer_blue;
int timer_motor;
int debug_timer;


//Flag variable
char Ir_task;
char debug_flag;
char Blue_task;

char led_rtask;
char led_gtask;
char led_btask;

char motor_task;


char LED_Flag;
char Motor_Flag;


ISR(TIMER0_COMPA_vect){
	timer_Led++;
	timer_Ir ++;
	debug_timer++;
	timer_blue++;
	timer_motor++;
	
	//BLUETOOTH
	if(timer_blue>7)   //30ms
	{
		Blue_task=1;
		timer_blue=0;
	}
	//IR
	if(timer_Ir>12) //50ms
	{
		Ir_task=1;
		timer_Ir=0;
	}
	//motor
#if 1	
	if(timer_motor>700)
	{
		motor_task=1;
		timer_motor=0;		
		TCNT0=0;
	}
#endif
	//RGB LED
	if(timer_Led>=150) //60ms   60/4
	{
		led_rtask=1;

	}
	if(timer_Led>=300)
	{
		led_gtask=1;

	}
	if(timer_Led>=450)
	{
		led_btask=1;
		timer_Led=0;
	}

//	if(debug_timer>400)
	if(debug_timer>=550)
	{
		debug_flag=1;
		debug_timer=0;
//		TCNT0=0;
	}
	
  
}


void setup() {
	// put your setup code here, to run once:
	Port_init();
#if DebugMode
	Serial.begin(9600);
#endif
	RGB_LED_Init();

	Timer_Init();
	sei();

	BT_Init();
	IR_Init();

	RGB_LED_Init();
	Motor_init();

	//OCR0B= 255/2; 
	_printf("FW Version: %s\r\n",FW_VER);
}


void Task_Func()
{

	if(Blue_task){  Bluetooth();  Blue_task=0;}
	if(Ir_task){  IR_Test();  Ir_task=0;}


	if(led_rtask){	if(LED_Flag&&!Motor_Flag){	setColor(RED_ON);}			led_rtask=0;} 
	if(led_gtask){	if(LED_Flag&&!Motor_Flag){	setColor(GREEN_ON);}		led_gtask=0;} 
	if(led_btask){	if(LED_Flag&&!Motor_Flag){	setColor(BLUE_ON);}			led_btask=0;} 

	if(motor_task){	Motor_Exec();	motor_task=0;}
}

void loop() {
  // put your main code here, to run repeatedly:
 
	Task_Func();
  
	    


}

