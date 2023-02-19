#include <IRremote.h> //v3.9.0
#include <IRremoteInt.h>  //v3.9.0
#include "IRLed.h"
#include "zDefine.h"


IRrecv ir(IRPIN);
decode_results res;

void test2()
{

        int i =0;
	
	_printf("test ok");
}


void IR_Init()
{
  ir.begin(IRPIN);
}


void IR_Test()
{

  if (ir.decode(&res))
  {
    switch(res.value)
    {
      case CHMinus:
        //setColor(255, 0, 0);  Serial.println("red");  break;
      case CH:
        //setColor(0, 255, 0);  Serial.println("Green");   break;
      case CHPlus:
        //setColor(0, 0, 255);  Serial.println("blue"); break;
      case OFF:
        digitalWrite(RedPin, LOW);   digitalWrite(GreenPin, LOW);    digitalWrite(BluePin, LOW);
        //Serial.println("OFF");
        break;

      default:
      break;

    }

    ir.resume();
  }

}

