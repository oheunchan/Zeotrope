
/*
##Zeotrope Project

2023.01.25  
- Timer를 이용한 Task 구현
- LED / IR 구현 

2023.01.24  Start OEC 
*/

#include "string.h"
#include <IRremote.h>
#include <IRremoteInt.h>

#define IRPIN     8

#define RedPin    11
#define GreenPin  10
#define BluePin   9

//Tiemr variable
int timer_Led;
int timer_Ir;

//IR variable
IRrecv ir(IRPIN);
decode_results res;

//Flag variable
char Led_task;
char Ir_task;


ISR(TIMER0_COMPA_vect){
  timer_Led++;
  timer_Ir ++;

  if(timer_Ir>12) //50ms
  {
    Ir_task=1;
    timer_Ir=0;
  }

  if(timer_Led>15) //60ms   60/4
  {
    Led_task=1;
    timer_Led=0;
    TCNT0=0;
  }

}


void setup() {
  // put your setup code here, to run once:

  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
 

  Serial.begin(9600);
  ir.begin(IRPIN);

  //Timer init
  TCCR0A = 0; //TCCR0A initialize
  TCCR0B = 0; //TCCR0B initialize
  TCNT0 = 0;  //TCNT0 initialize
  OCR0A= 255; 
  TCCR0B |= (1<<WGM02);
  TCCR0B |= (1<<CS02) | (0<<CS00);
  TIMSK0 |= (1<<OCIE0A);
  sei();
  
  
}

void IR_Test()
{


    if (ir.decode(&res))
    {
      #if 1
      //Serial.print("decode_type : ");
      //Serial.print(res.decode_type);

     // Serial.print("\tvalue : ");
      Serial.println(res.value, HEX);

     // Serial.print("\tbits : ");
     // Serial.println(res.bits);

      ir.resume();    //  다음 값
      #endif

    }
  
}


void setColor(int rgain, int ggain, int bgain)
{
  analogWrite(RedPin, rgain);
  analogWrite(GreenPin, ggain);
  analogWrite(BluePin, bgain); 
}

void Task_LED()
{
  setColor(255, 0, 0); // red
  //delay(3000);
  //setColor(0, 255, 0); // green
 // delay(3000);
  //setColor(0, 0, 255); // blue
  //delay(3000);

  //setColor(255, 255, 0);// yellow
  //delay(3000);
  //setColor(80, 0, 80); // purple
  //delay(3000);
  //setColor(0, 255, 255);// aqua
  //delay(3000);
      
}


void Task_Func()
{

  if(Ir_task){  IR_Test();  Ir_task=0;}
  if(Led_task){ Task_LED(); Led_task=0;}  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Task_Func();
  
}
