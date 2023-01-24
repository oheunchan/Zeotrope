/*
##Zeotrope Project

2023.01.24  Start OEC 
*/

#include "string.h"
#include <MsTimer2.h>

int Timer;
int Sec_s;

void ISR_Timer()
{
  Timer ++;
  Sec_s ++;
  if(Timer>1000)
  {
    Serial.print("1Sec\n");
    Timer=0;
  }
  
  if(Sec_s>3000)
  {
    Serial.print("3Sec\n");
    Sec_s=0;
  }

}


void setup() {
  // put your setup code here, to run once:
  MsTimer2::set(1, ISR_Timer);
  MsTimer2::start();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}
