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

void setColor(int power_on)
{

	if(power_on)
	{
		digitalWrite(BluePin, HIGH); 
		digitalWrite(RedPin, HIGH); 
		digitalWrite(GreenPin, HIGH); 
	}
	else
	{

		digitalWrite(GreenPin, LOW);  
		digitalWrite(RedPin, LOW); 
		digitalWrite(BluePin, LOW);
	}
}

