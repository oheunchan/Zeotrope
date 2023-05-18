#include <Stepper.h>
#include "Motor.h"
#include "Arduino.h"
#include "zDefine.h"
#include "RGB_Led.h"


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
//	digitalWrite(MOTOR_BRK, LOW);

	setColor(0);
	
	Motor_Flag=ON;
}

void Motor_OFF()
{
	digitalWrite(MOTOR_EN, HIGH);
//	digitalWrite(MOTOR_BRK, HIGH);
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

int motor_mode=0;

void Motor_Exec()
{
	static char step=0;

	if(motor_mode==Motor_Mode_TB)
	{
		if(Motor_Flag)
		{
			switch(step)
			{
				case Motor_IDLE:								step=Motor_1Step_SPD;		break;
				case Motor_1Step_SPD:	Motor_ON();	OCR0B=20;	step=Motor_2Step_SPD;		break;
				case Motor_2Step_SPD:	OCR0B=60;				step=Motor_3Step_SPD;		break;
				case Motor_3Step_SPD:	OCR0B=100;				step=Motor_4Step_SPD;		break;
				case Motor_4Step_SPD:	OCR0B=140;				step=Motor_5Step_SPD;		break;
				case Motor_5Step_SPD:	OCR0B=180;				step=Motor_6Step_SPD;		break;
				case Motor_6Step_SPD:	OCR0B=220;				step=Motor_Max_SPD;			break;
				case Motor_Max_SPD:		OCR0B=250;				step=Motor_Max_SPD;			break;
				default : break;

			}
		}
		else
		{
			switch(step)
			{
				case Motor_IDLE:		Motor_OFF();OCR0B=0;	step=Motor_IDLE;			break;
				case Motor_1Step_SPD:	OCR0B=15;				step=Motor_IDLE;			break;
				case Motor_2Step_SPD:	OCR0B=30;				step=Motor_1Step_SPD;		break;
				case Motor_3Step_SPD:	OCR0B=70;				step=Motor_2Step_SPD;		break;
				case Motor_4Step_SPD:	OCR0B=100;				step=Motor_3Step_SPD;		break;
				case Motor_5Step_SPD:	OCR0B=160;				step=Motor_4Step_SPD;		break;
				case Motor_6Step_SPD:	OCR0B=220;				step=Motor_5Step_SPD;		break;
				case Motor_Max_SPD:		OCR0B=250;				step=Motor_6Step_SPD;		break;
				default : break;

			}
		}
		_printf("speed :[%d] \r\n",OCR0B);
	}
	else	//Motor Mode NORMAL
	{
		if(Motor_Flag)
		{
			Motor_ON(); OCR0B=250;
		}
		else
		{
			Motor_OFF();OCR0B=0;
		}
		_printf("speed :[%d] \r\n",OCR0B);
	}



}
