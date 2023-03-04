#ifndef __Bluetooth_H_
#define __Bluetooth_H_

void _printf(const char *s, ...);
void BT_Init();
void Bluetooth();


#define BT_PHeader  0xFF

#define LED_ON      0xA2
#define LED_OFF     0x62

#define MT_FORWARD    0xE2
#define MT_BACKWARD   0x22

#define MT_SPD_UP     0x02
#define MT_SPD_DN     0xC2
#define MT_POWER_OFF  0xE0


typedef enum
{
  BT_HEADER,
  BT_CMD1,
  BT_CMD2,
  BT_CHKSUM,
};

#endif