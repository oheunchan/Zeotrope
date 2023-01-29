
/*
##Zeotrope Project
2023.01.29
-HC06 TEST 노트북으로 통신 확인
-IR 동작이 안되서 IRREMOTE V3.9.0으로 다운그레이드 라이브러리 upgrade 하지 말것

2023.01.28
-HC06 TEST 중 아이폰에서 동작하지 않음.

2023.01.26
-리모컨으로 LED 동작 테스트

2023.01.25  
- Timer를 이용한 Task 구현
- LED / IR 구현 

2023.01.24  Start OEC 
*/

#include "string.h"
#include <IRremote.h> //v3.9.0
#include <IRremoteInt.h>  //v3.9.0
#include <SoftwareSerial.h>

#define IRPIN     8

#define RedPin    11
#define GreenPin  10
#define BluePin   9

#define BT_RXD    3
#define BT_TXD    2

#define CHMinus 0xFFA25D
#define CH      0xFF629D
#define CHPlus  0xFFE21D
#define OFF     0xFF22DD

#define DebugMode 1

//Tiemr variable
int timer_Led;
int timer_Ir;

//IR variable
IRrecv ir(IRPIN);
decode_results res;
//SoftwareSerial bluetooth(BT_RXD, BT_TXD);
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
 
  #if DebugMode
  Serial.begin(9600);
  #endif
  //bluetooth.begin(9600);
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


#if 1
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
#else
  if (ir.decode(&res))
  {
    switch(res.value)
    {
      case CHMinus:
        setColor(255, 0, 0);  Serial.println("red");  break;
      case CH:
        setColor(0, 255, 0);  Serial.println("Green");   break;
      case CHPlus:
        setColor(0, 0, 255);  Serial.println("blue"); break;
      case OFF:
        digitalWrite(RedPin, LOW);   digitalWrite(GreenPin, LOW);    digitalWrite(BluePin, LOW);
        Serial.println("OFF");
        break;

      default:   
      break; 

    }

    ir.resume(); 
  }
#endif

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
  //if(Led_task){ Task_LED(); Led_task=0;}  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  #if 1
  Task_Func();
  
  #else   //test
  if(bluetooth.available())
  {
   //Serial.write(bluetooth.read());
   Serial.print(bluetooth.read());
    switch(bluetooth.read())
    {
      case 0:
        setColor(255, 0, 0);  Serial.println("red");  break;
      case 1:
        setColor(0, 255, 0);  Serial.println("Green");   break;
      case 2:
        setColor(0, 0, 255);  Serial.println("blue"); break;
      case 3:
        digitalWrite(RedPin, LOW);   digitalWrite(GreenPin, LOW);    digitalWrite(BluePin, LOW);
        Serial.println("OFF");
        break;

      default:   
      break;  

    }
  

  }
  if(Serial.available())
  {
     bluetooth.write(Serial.read());
  }
  #endif
}
