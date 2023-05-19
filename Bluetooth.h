#ifndef __Bluetooth_H_
#define __Bluetooth_H_

void _printf(const char *s, ...);
void BT_Init();
void Bluetooth();


#define BT_PHeader  		0xFF

//LED
#define LED_ON      		0xA2
#define LED_OFF     		0x62

//MOTOR
#define MT_FORWARD    		0xE2
#define MT_BACKWARD   		0x22
#define MOTOR_ON     		0x02
#define MOTOR_OFF    		0xC2
#define MT_NORMAL_MODE		0xE0
#define MT_TB_MODE			0xA8

//RESET
#define SOFT_RESET			0x68

//ETC
#define ETC_CMD				0x90



typedef enum
{
  BT_HEADER,
  BT_CMD1,
  BT_CMD2,
  BT_CHKSUM,
};

#endif