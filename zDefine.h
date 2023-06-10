#ifndef __Define_H_
#define __Define_H_

#define FW_VER	"V1.13"

#if 0
#define RedPin    A0
#define GreenPin  A1
#define BluePin   A2
#else
#define RedPin    11
#define GreenPin  9
#define BluePin   6
#endif

//RESET
#define RESET_PIN	A3

//Bluetooth
#define BT_RXD    4
#define BT_TXD    2

#define IRPIN     13


//Motor 
#define MOTOR_EN    10
#define MOTOR_DIR   12
#define MOTOR_BRK   8
#define MOTOR_PWM   5

//PhotoSensor
#define PHOTO_SENSOR 3


#define DebugMode 1



//LED
enum{OFF=0,ON,RED_ON,GREEN_ON,BLUE_ON};





#endif
