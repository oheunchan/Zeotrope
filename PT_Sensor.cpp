#include "Arduino.h"
#include "zDefine.h"
#include "PT_Sensor.h"

void PT_Sensor_Read(void)
{

	if(digitalRead(PHOTO_SENSOR))		digitalWrite(A4,HIGH);
	else								  digitalWrite(A4,LOW);

}


