#include <Stepper.h>
#include "Motor.h"
#include "zDefine.h"

Stepper my28BJY48(2048, IN4, IN2, IN3, IN1);



void Motor_init()
{
  _printf("Motor init\r\n");
  my28BJY48.setSpeed(RPM);
  my28BJY48.step(STEPS);
}

long Motor_SetSpeed(long _RPM)
{
  
  my28BJY48.setSpeed(_RPM);
  return _RPM;
}

int Motor_SetStep(int _step)
{
  my28BJY48.step(_step);
  return _step;
}