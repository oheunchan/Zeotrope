#include <SoftwareSerial.h>
#include "Bluetooth.h"
#include "Motor.h"
#include "zDefine.h"


SoftwareSerial bluetooth(BT_RXD, BT_TXD);


const int BUFFER_SIZE = 255;
unsigned char BT_RX_Buf[BUFFER_SIZE];

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
      _printf("len:%d %d data:%x\r\n",rlen,i,bt_rx[i]);
    }
    _printf("chksum: %x\r\n",Chksum);
    if(bt_rx[BT_HEADER]==BT_PHeader){  bt_protocol_flag=1;  Chksum=bt_rx[BT_CMD1]+bt_rx[BT_CMD2]; } //Header Check

    if(bt_protocol_flag)
    {
        switch(bt_rx[BT_CMD1])
        {
          case LED_ON:
            if(bt_rx[BT_CMD2]==0x5D && bt_rx[BT_CHKSUM]==Chksum) _printf("LED ON");  break;
          case LED_OFF:
            if(bt_rx[BT_CMD2]==0x9D && bt_rx[BT_CHKSUM]==Chksum) _printf("LED OFF");  break;
          case MT_FORWARD: 
            if(bt_rx[BT_CMD2]==0xFD && bt_rx[BT_CHKSUM]==Chksum)   Motor_SetStep(1000); _printf("MOTOR FORWARD");  break;
          case MT_BACKWARD:
            if(bt_rx[BT_CMD2]==0xDD && bt_rx[BT_CHKSUM]==Chksum)   Motor_SetStep(-1000); _printf("MOTOR BACKWARD");  break;
          
            
          default: break;
        }
    }

  }

}