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
extern int led_en;
extern int motor_mode;



void test2()
{

        int i =0;
	
	_printf("test ok");
}


void IR_Init()
{
  ir.begin(IRPIN);
}
void RestFunc()
{
	_printf("SOFT RESET\r\n"); 
  digitalWrite(RESET_PIN,LOW);
  delay(100);
  digitalWrite(RESET_PIN,HIGH);
}


void IR_Test()
{

  if (ir.decode(&res))
  {
    switch(res.value)
    {

		case IR_LED_ON:		led_en=1;						_printf("LED ON\r\n");				break;
		case IR_LED_OFF:	led_en=0;						_printf("LED OFF\r\n");				break;
		case IR_MOTOR_FOR:  digitalWrite(MOTOR_DIR, LOW); 	_printf("MOTOR FORWARD\r\n"); 	 	break;
		case IR_MOTOR_BACK: digitalWrite(MOTOR_DIR, HIGH); 	_printf("MOTOR BACKWARD\r\n"); 	 	break;
		case IR_MOTOR_ON:   Motor_Flag=ON; 					_printf("MOTOR ON\r\n");  			break;
		case IR_MOTOR_OFF:  Motor_Flag=OFF;  				_printf("MOTOR OFF\r\n"); 			break;
		case IR_MT_NORMAL:	motor_mode=Motor_Mode_Normal;	_printf("MOTOR NORMAL Mode\r\n"); 	break;
		case IR_MT_TABLE:	motor_mode=Motor_Mode_TB;		_printf("MOTOR Table Mode\r\n");	break;
		case IR_ETC_CMD:									_printf("ETC COMMAND\r\n"); 		break;
		case IR_SOFR_RESET:	RestFunc();															break;
			
      default:
      break;

    }

    ir.resume();
  }

}

