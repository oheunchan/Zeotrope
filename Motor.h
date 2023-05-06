#ifndef __MOTOR_H_
#define __MOTOR_H_

enum{
	Motor_IDLE=0x00,
	Motor_1Step_SPD,
	Motor_2Step_SPD,
	Motor_3Step_SPD,
 	Motor_Max_SPD,
};


void _printf(const char *s, ...);
void Motor_init();
void Motor_ON();
void Motor_OFF();
void Motor_SPD_DN(int spd);
void Motor_SPD_UP(int spd);

void Motor_Exec();

#endif
