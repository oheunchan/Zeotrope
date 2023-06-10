#include "Arduino.h"
#include "zDefine.h"
#include "PT_Sensor.h"

extern char read_val;

void PT_Sensor_Read(void)
{

	#if 0
	read_val=1;
	#else
	read_val=!read_val;
	#endif
}


