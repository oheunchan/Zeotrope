#include <SoftwareSerial.h>
#include <IRremote.h> //v3.9.0
#include <IRremoteInt.h>  //v3.9.0
#include "IRLed.h"
#include "Motor.h"
#include "RGB_Led.h"
#include "zDefine.h"


IRrecv ir(IRPIN);
decode_results res;

extern char LED_Flag;
extern char Motor_Flag;


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
      case IR_LED_ON:     setColor(ON); LED_Flag=1; _printf("LED ON\r\n");  break;
      case IR_LED_OFF:    setColor(OFF); LED_Flag=0;  _printf("LED OFF\r\n");  break;
      case IR_MOTOR_FOR:  digitalWrite(MOTOR_DIR, LOW); _printf("MOTOR FORWARD\r\n");  break;
      case IR_MOTOR_BACK: digitalWrite(MOTOR_DIR, HIGH); _printf("MOTOR BACKWARD\r\n");  break;
      case IR_MOTOR_ON:   /*Motor_ON();*/ Motor_Flag=ON; _printf("MOTOR ON\r\rn");  break;
      case IR_MOTOR_OFF:  /*Motor_OFF();*/Motor_Flag=OFF;  _printf("MOTOR OFF\r\rn");  break;
      case IR_MOTOR_SPDDN: Motor_SPD_DN(30); _printf("MOTOR SPD DN\r\n");  break;
      case IR_MOTOR_SPDUP: Motor_SPD_UP(30);  _printf("MOTOR SPD UP\r\n");  break;
      default:
      break;

    }

    ir.resume();
  }

}

