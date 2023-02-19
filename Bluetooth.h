#ifndef __Bluetooth_H_
#define __Bluetooth_H_

void _printf(const char *s, ...);
void BT_Init();
void Bluetooth();

#define BT_PHeader  0xFF

#define LED_ON      0xA2
#define LED_OFF     0x62

#define MT_FORWARD    0x02
#define MT_BACKWARD   0x22

typedef enum
{
  BT_HEADER,
  BT_CMD1,
  BT_CMD2,
  BT_CHKSUM,
};

#endif