#include <SoftwareSerial.h>
#include "Arduino.h"
#include "Bluetooth.h"
#include "Motor.h"
#include "RGB_Led.h"
#include "zDefine.h"
#include "System.h"

SoftwareSerial bluetooth(BT_RXD, BT_TXD);



const int BUFFER_SIZE = 255;
unsigned char BT_RX_Buf[BUFFER_SIZE];
extern char Motor_Flag;
extern int led_en;
extern int motor_mode;


void BT_Init()
{
  bluetooth.begin(9600);
  bluetooth.setTimeout(30);  
  _printf("Bt Init OK\r\n");
}

void Bluetooth()
{
 
  int bt_rx[20]={0,};
  int rlen=0;
  int CMD_1,CMD_2,Chksum=0;
  unsigned char bt_protocol_flag=0;
  
  if(bluetooth.available()>0)
  {
  
    rlen = bluetooth.readBytes(BT_RX_Buf, BUFFER_SIZE);

    for(int i = 0; i < rlen; i++)
    { 
      bt_rx[i]=BT_RX_Buf[i];
//      _printf("len:%d %d data:%x\r\n",rlen,i,bt_rx[i]);
    }
//    _printf("chksum: %x\r\n",Chksum);
    if(bt_rx[BT_HEADER]==BT_PHeader){  bt_protocol_flag=1;  Chksum=bt_rx[BT_CMD1]+bt_rx[BT_CMD2]; } //Header Check
 
    if(bt_protocol_flag)
    {
        switch(bt_rx[BT_CMD1])
        {
     
			case LED_ON:			led_en=1;						_printf("LED ON\r\n");				break;
			case LED_OFF:			led_en=0;						_printf("LED OFF\r\n");				break;
			
			case MT_FORWARD:		digitalWrite(MOTOR_DIR, LOW); 	_printf("MOTOR FORWARD\r\n");		break;
			case MT_BACKWARD:		digitalWrite(MOTOR_DIR, HIGH); 	_printf("MOTOR BACKWARD\r\n");		break;
			case MOTOR_ON:			Motor_Flag=ON; 					_printf("MOTOR ON\r\n");  			break;
			case MOTOR_OFF:			Motor_Flag=OFF;  				_printf("MOTOR OFF\r\n"); 			break;
			case MT_NORMAL_MODE:	motor_mode=Motor_Mode_Normal;	_printf("MOTOR NORMAL Mode\r\n"); 	break;
			case MT_TB_MODE:		motor_mode=Motor_Mode_TB;		_printf("MOTOR Table Mode\r\n");	break;
			
			case SOFT_RESET:		RestFunc();															break;
			case ETC_CMD:											_printf("ETC COMMAND\r\n"); 		break;
			
          default: break;
        }
    }

  }

}
