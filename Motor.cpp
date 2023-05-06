#include <Stepper.h>
#include "Motor.h"
#include "Arduino.h"
#include "zDefine.h"





void Motor_init()
{
  _printf("Motor init\r\n");

  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_BRK, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_DIR,  OUTPUT);

  digitalWrite(MOTOR_EN, LOW);
  digitalWrite(MOTOR_BRK, LOW);
  digitalWrite(MOTOR_DIR, LOW);

 
}



void Motor_ON()
{
  digitalWrite(MOTOR_EN, LOW);
  digitalWrite(MOTOR_BRK, LOW);
}

void Motor_OFF()
{
  digitalWrite(MOTOR_EN, HIGH);
  digitalWrite(MOTOR_BRK, HIGH);
}

void Motor_SPD_DN(int _spd)
{
 

   //return 1;
}

void Motor_SPD_UP(int _spd)
{


   //return 1;
}