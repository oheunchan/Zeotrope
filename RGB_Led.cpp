#include <SoftwareSerial.h>
#include "RGB_Led.h"
#include "Arduino.h"
#include "zDefine.h"

extern char LED_Flag;

void RGB_LED_Init()
{
	pinMode(RedPin, OUTPUT);
	pinMode(GreenPin, OUTPUT);
	pinMode(BluePin, OUTPUT);

	setColor(ON);
	delay(100);
	setColor(OFF);
	LED_Flag=1;
}

int led_en=0;
	
void setColor(int power_on)
{

	if(!led_en)
		power_on=OFF;
		
	switch(power_on)
	{
		case OFF:		digitalWrite(GreenPin, LOW);  	digitalWrite(RedPin, LOW); 		digitalWrite(BluePin, LOW);		break;
		case ON: 		digitalWrite(GreenPin, HIGH);  	digitalWrite(RedPin, HIGH); 	digitalWrite(BluePin, HIGH);	break;
		case RED_ON	:	digitalWrite(GreenPin, LOW);  	digitalWrite(RedPin, HIGH); 	digitalWrite(BluePin, LOW);		break;
		case GREEN_ON:	digitalWrite(GreenPin, HIGH);  	digitalWrite(RedPin, LOW); 		digitalWrite(BluePin, LOW);		break;
		case BLUE_ON:	digitalWrite(GreenPin, LOW);  	digitalWrite(RedPin, LOW); 		digitalWrite(BluePin, HIGH);	break;

		default : break;
		
	}

}


