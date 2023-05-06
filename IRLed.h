#ifndef __IRLed_H_
#define __IRLed_H_


#define IR_LED_ON       0xFFA25D
#define IR_LED_OFF      0xFF629D
#define IR_MOTOR_FOR    0xFFE21D
#define IR_MOTOR_BACK   0xFF22DD
#define IR_MOTOR_ON     0xFF02FD
#define IR_MOTOR_OFF    0xFFC23D
#define IR_MOTOR_SPDDN  0xFFE01F
#define IR_MOTOR_SPDUP  0xFFA857



void _printf(const char *s, ...);
void IR_Init();
void IR_Test();
void test2();


#endif
