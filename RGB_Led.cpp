#include <SoftwareSerial.h>
#include "RGB_Led.h"
#include "Arduino.h"
#include "zDefine.h"


void setColor(int rgain, int ggain, int bgain)
{

  digitalWrite(BluePin, HIGH); 
  digitalWrite(RedPin, HIGH); 
  digitalWrite(GreenPin, HIGH); 

  
}

void RGB_LED_OFF()
{
   digitalWrite(GreenPin, LOW);  digitalWrite(RedPin, LOW); digitalWrite(BluePin, LOW); 
}
