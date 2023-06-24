
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

char neopixel_task;

char motor_task;


char LED_Flag;
char Motor_Flag;


void Task_Func()
{

	if(Blue_task)	{	Bluetooth();  Blue_task=0;}
	if(Ir_task)		{	IR_Test();  Ir_task=0;}

#if 0
	if(led_rtask)	{	if(LED_Flag&&!Motor_Flag){	setColor(RED_ON);}			led_rtask=0;} 
	if(led_gtask)	{	if(LED_Flag&&!Motor_Flag){	setColor(GREEN_ON);}		led_gtask=0;} 
	if(led_btask)	{	if(LED_Flag&&!Motor_Flag){	setColor(BLUE_ON);}			led_btask=0;} 
#else

#endif

	if(motor_task)	{	Motor_Exec();	motor_task=0;}

	PT_Sensor_Read();	
//	setColor();		//TEST¿ë NeoPixel
}



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
	if(timer_motor>700)
	{
		motor_task=1;
		timer_motor=0;		
		TCNT0=0;
	}
	//RGB LED
#if 0
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
#else
	
	if(timer_Led>=450)
	{
		neopixel_task=1;
		timer_Led=0;
	}
#endif
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

	Timer_Init();
	sei();

	BT_Init();
	IR_Init();

	RGB_LED_Init();	
	NeoPixel_Init();
	Motor_init();

	_printf("FW Version: %s\r\n",FW_VER);

}



void loop() {
  // put your main code here, to run repeatedly:
 
	Task_Func();


}

