#include "Arduino.h"
#include "zDefine.h"
#include "PT_Sensor.h"

void PT_Sensor_Read(void)
{

	if(digitalRead(PHOTO_SENSOR))
		digitalWrite(STROBE_LED,LOW);
	else
		digitalWrite(STROBE_LED,HIGH);
}


