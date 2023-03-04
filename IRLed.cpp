#include <SoftwareSerial.h>
#include <IRremote.h> //v3.9.0
#include <IRremoteInt.h>  //v3.9.0
#include "IRLed.h"
#include "Motor.h"
#include "RGB_Led.h"
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
      case IR_LED_ON:     setColor(255, 255, 255);  _printf("LED ON");  break;
      case IR_LED_OFF:    RGB_LED_OFF();  _printf("LED OFF");  break;
      case IR_MOTOR_FOR:  Motor_SetStep(1000); _printf("MOTOR FORWARD");  break;
      case IR_MOTOR_BACK: Motor_SetStep(-1000); _printf("MOTOR BACKWARD");  break;

      default:
      break;

    }

    ir.resume();
  }

}

