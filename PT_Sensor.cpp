#include "Arduino.h"
#include "zDefine.h"
#include "PT_Sensor.h"

extern char read_val;

void PT_Sensor_Read(void)
{
 #if 0
	int read_val=0;
  	read_val=digitalRead(PHOTO_SENSOR);

	if(read_val)	digitalWrite(RedPin, HIGH);
	else		digitalWrite(RedPin, LOW);
#else
	read_val=1;
//	digitalWrite(RedPin, HIGH);
//	_printf("pt on\r\n");
#endif
}


