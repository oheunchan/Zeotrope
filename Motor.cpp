#include <Stepper.h>
#include "Motor.h"
#include "Arduino.h"
#include "zDefine.h"


extern char Motor_Flag;


void Motor_init()
{
  _printf("Motor init\r\n");

  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_BRK, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_DIR,  OUTPUT);

  digitalWrite(MOTOR_EN, LOW);
  digitalWrite(MOTOR_BRK, LOW);
  digitalWrite(MOTOR_DIR, LOW);

 
}



void Motor_ON()
{
	digitalWrite(MOTOR_EN, LOW);
	digitalWrite(MOTOR_BRK, LOW);

	digitalWrite(RedPin, HIGH);
	digitalWrite(GreenPin, LOW);
	digitalWrite(BluePin, LOW);
	
	Motor_Flag=ON;
}

void Motor_OFF()
{
	digitalWrite(MOTOR_EN, HIGH);
	digitalWrite(MOTOR_BRK, HIGH);
	Motor_Flag=OFF;
}

void Motor_SPD_DN(int spd)
{
 	if(OCR0B<=0)
 	{
 		spd=0;
		OCR0B-=spd;
 	}
	else
		OCR0B-=spd;
	_printf("[%d]\r\n",OCR0B);	
}

void Motor_SPD_UP(int spd)
{
	if(OCR0B>=240)
	{
		spd=240;
		OCR0B=spd;
	}
	else{OCR0B+=spd;}
		
	_printf("[%d]\r\n",OCR0B);
}


void Motor_Exec()
{
	static char step=0;

	if(Motor_Flag)
	{
		switch(step)
		{
			case Motor_IDLE:		step=Motor_1Step_SPD;								break;
			case Motor_1Step_SPD:	Motor_ON();	OCR0B=50;	step=Motor_2Step_SPD;		break;
			case Motor_2Step_SPD:	OCR0B=100;				step=Motor_3Step_SPD;		break;
			case Motor_3Step_SPD:	OCR0B=200;				step=Motor_Max_SPD;			break;
			case Motor_Max_SPD:		OCR0B=250;				step=Motor_Max_SPD;			break;
			default : break;

		}
	}
	else
	{
		switch(step)
		{
			case Motor_IDLE:		Motor_OFF();OCR0B=0;	step=Motor_IDLE;			break;
			case Motor_1Step_SPD:	OCR0B=50;				step=Motor_IDLE;			break;
			case Motor_2Step_SPD:	OCR0B=100;				step=Motor_1Step_SPD;		break;
			case Motor_3Step_SPD:	OCR0B=200;				step=Motor_2Step_SPD;		break;
			case Motor_Max_SPD:		OCR0B=250;				step=Motor_3Step_SPD;		break;
			default : break;

		}
	}
	_printf("speed :[%d] \r\n",OCR0B);

}
