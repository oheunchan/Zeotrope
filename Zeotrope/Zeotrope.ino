
/*
##Zeotrope Project

2023.01.24  Start OEC 
*/

#include "string.h"
#include <MsTimer2.h>
#include <IRremote.h>
#include <IRremoteInt.h>

#define IRPIN     8

#define RedPin    11
#define GreenPin  10
#define BluePin   9


#define _10ms 10
#define _1Sec 1000



//Tiemr variable
int Timer;
int Test_timer;
int timer_Led;
int timer_Ir;


//IR variable
IRrecv ir(IRPIN);
decode_results res;

//Flag variable
char Led_task;
char Ir_task;


void ISR_Timer()
{
  Timer ++;
  Test_timer ++;

  timer_Led ++;
  timer_Ir ++;

  if(Timer > 1000)
  {
   // Serial.print("1Sec\n");

    Timer=0;
  }
  
  if(Test_timer> 2000)
  {
  // Serial.print("3Sec\n");
    Test_timer=0;
  }

#if 1
  if(timer_Led>30)
  {
    Led_task=1;
    timer_Led=0;
  }
  
  if(timer_Ir>100)
  {
      Ir_task=1;
      timer_Ir=0;
  }
#endif


}


void setup() {
  // put your setup code here, to run once:
  MsTimer2::set(1, ISR_Timer);  //Timer init
  MsTimer2::start();            //Timer Start

  Serial.begin(9600);           //Uart init
  ir.enableIRIn();              //IR Init     

  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT); 


 
}

void IR_Test()
{
  //Serial.print("IR\n");
   if (ir.decode(&res))
    {
      #if 1
      Serial.print("decode_type : ");
      Serial.print(res.decode_type);

      Serial.print("\tvalue : ");
      Serial.print(res.value, HEX);

      Serial.print("\tbits : ");
      Serial.println(res.bits);

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
  //setColor(255, 0, 0); // red
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

    Serial.print("LEd\n");  
      
}


void Task_Func()
{
  if(Led_task){ Task_LED(); Led_task=0;}  
  if(Ir_task){  IR_Test();  Ir_task=0;}
}

void loop() {
  // put your main code here, to run repeatedly:
   
 // Task_Func();

 
  IR_Test();
  Task_LED();

  
}
