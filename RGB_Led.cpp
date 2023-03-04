#include <SoftwareSerial.h>
#include "RGB_Led.h"
#include "Arduino.h"
#include "zDefine.h"


void setColor(int rgain, int ggain, int bgain)
{
  analogWrite(RedPin, rgain);
  analogWrite(GreenPin, ggain);
  analogWrite(BluePin, bgain); 
  
}

void RGB_LED_OFF()
{
  digitalWrite(RedPin, LOW);   digitalWrite(GreenPin, LOW);    digitalWrite(BluePin, LOW); 
}