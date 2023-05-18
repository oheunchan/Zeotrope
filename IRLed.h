#ifndef __IRLed_H_
#define __IRLed_H_


#define IR_LED_ON       0xFFA25D
#define IR_LED_OFF      0xFF629D
#define IR_MOTOR_FOR    0xFFE21D
#define IR_MOTOR_BACK   0xFF22DD
#define IR_MOTOR_ON     0xFF02FD
#define IR_MOTOR_OFF    0xFFC23D
#define IR_MT_NORMAL	0xFFE01F
#define IR_MT_TABLE		0xFFA857
#define IR_ETC_CMD		0xFF906F
#define	IR_SOFR_RESET	0xFF6897


void _printf(const char *s, ...);
void IR_Init();
void IR_Test();
void test2();


#endif
