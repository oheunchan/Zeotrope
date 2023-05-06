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
      case IR_MOTOR_FOR:  digitalWrite(MOTOR_DIR, LOW); _printf("MOTOR FORWARD");  break;
      case IR_MOTOR_BACK: digitalWrite(MOTOR_DIR, HIGH); _printf("MOTOR BACKWARD");  break;
      case IR_MOTOR_ON:   Motor_ON();  _printf("MOTOR ON");  break;
      case IR_MOTOR_OFF:  Motor_OFF();  _printf("MOTOR OFF");  break;
      case IR_MOTOR_SPDDN: OCR0B -=30; _printf("MOTOR SPD DN");  break;
      case IR_MOTOR_SPDUP: OCR0B +=30;  _printf("MOTOR SPD UP");  break;
      default:
      break;

    }

    ir.resume();
  }

}

