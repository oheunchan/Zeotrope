
/*
##Zeotrope Project
2023.02.06
- Step Motor Test로 구현

2023.01.30
- HC06 LED 동작 테스트
- bluetooth.read()가 1byte로 동작함 Protocol은 3byte이므로 수정 필요

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
#include <Stepper.h>



//LED
#define RedPin    5
#define GreenPin  6
#define BluePin   7

//Bluetooth
#define BT_RXD    4
#define BT_TXD    2

//IR
#define IRPIN     13
#define CHMinus 0xFFA25D
#define CH      0xFF629D
#define CHPlus  0xFFE21D
#define OFF     0xFF22DD

//Motor 
#define STEPS 200
#define RPM 15
#define IN1 11 // IN1
#define IN2 10 // IN2
#define IN3 9 // IN3
#define IN4 8 // IN4

#define DebugMode 1

//Tiemr variable
int timer_Led;
int timer_Ir;
int timer_blue;
int debug_timer;

//IR variable
IRrecv ir(IRPIN);
decode_results res;
SoftwareSerial bluetooth(BT_RXD, BT_TXD);
Stepper my28BJY48(2048, IN4, IN2, IN3, IN1);



//Flag variable
char Led_task;
char Ir_task;
char debug_flag;
char Blue_task;

char Motor_Speed;

ISR(TIMER0_COMPA_vect){
  timer_Led++;
  timer_Ir ++;
  debug_timer++;
  timer_blue++;
  if(timer_blue>7)   //30ms
  {
    Blue_task=1;
    timer_blue=0;
  }

  if(timer_Ir>12) //50ms
  {
    Ir_task=1;
    timer_Ir=0;
  }

  if(timer_Led>15) //60ms   60/4
  {
    Led_task=1;
    timer_Led=0;
   // TCNT0=0;
  }
  if(debug_timer>400)
  {
    debug_flag=1;
    debug_timer=0;
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
  bluetooth.begin(9600);
  ir.begin(IRPIN);

  //Timer init
  #if 1
  TCCR0A = 0; //TCCR0A initialize
  TCCR0B = 0; //TCCR0B initialize
  TCNT0 = 0;  //TCNT0 initialize
  OCR0A= 255; 
  TCCR0B |= (1<<WGM02);
  TCCR0B |= (1<<CS02) | (0<<CS00);
  TIMSK0 |= (1<<OCIE0A);
  sei();
  #endif
  my28BJY48.setSpeed(RPM);
  Motor_Speed=RPM;
}

void IR_Test()
{


#if 0
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

void Bluetooth()
{
  Serial.println("BluteToothOK");
   switch(bluetooth.read())
    {
      case 1:
        setColor(255, 0, 0);  Serial.println("red");  break;
      case 2:
        setColor(0, 255, 0);  Serial.println("Green");   break;
      case 3:
        setColor(0, 0, 255);  Serial.println("blue"); break;
      case 4:
        digitalWrite(RedPin, LOW);   digitalWrite(GreenPin, LOW);    digitalWrite(BluePin, LOW);
        Serial.println("OFF");
        break;
      case 5:
        my28BJY48.step(STEPS);  break;
      case 6:
        my28BJY48.step(-STEPS);  break;
      case 7:
        if(Motor_Speed<=15) 
        {Motor_Speed+=5;  my28BJY48.setSpeed(Motor_Speed);} break;
      case 8:
        if(Motor_Speed>=0) 
        {Motor_Speed-=5;  my28BJY48.setSpeed(Motor_Speed);} break;

      default:   
      break;  

    }
}


void Task_Func()
{

  if(Blue_task){  Bluetooth();  Blue_task=0;}
  if(Ir_task){  IR_Test();  Ir_task=0;}
  //if(Led_task){ Task_LED(); Led_task=0;}
    
}
const int BUFFER_SIZE = 255;
char buf[BUFFER_SIZE];

u16 b_cmd1=0;
u16 b_cmd2=0;
u16 b_cmd3=0;
unsigned int cmd=0;

void loop() {
  // put your main code here, to run repeatedly:
  byte test[20]={0,};
  char test0=0;
  int rlen=0;
  

  Task_Func();


//TEST Code
#if 0
  #if 0
  //Task_Func();
  if (bluetooth.available() > 0) {
    // read the incoming bytes:
    int rlen = bluetooth.readBytes(buf, BUFFER_SIZE);
  //Serial.print(rlen);    // prints the received data
    //Serial.print("I received: ");
    for(int i = 0; i < rlen; i++)
      Serial.print(buf[i]);
  }
  
  #else   //test


  if(bluetooth.available()>0)
  {
    
#if 0
    rlen = bluetooth.readBytes(buf, BUFFER_SIZE);

    for(int i = 0; i < rlen; i++)
    { 
      test[i]=buf[i];
      Serial.print(test[i]);
    }
#endif
  // Serial.write(bluetooth.read());
  // b_cmd1=bluetooth.read()>>16;
   //b_cmd2=bluetooth.read()>>8;
   //b_cmd3=bluetooth.read();

  
  //Serial.println(test[0]);
  //Serial.println(test[1]);
  //Serial.println(test[2]);

    //switch(bluetooth.readBytes(test,2));

    #if 0
    //switch(bluetooth.read())
    switch(bluetooth.read())
    {
      case 1:
        setColor(255, 0, 0);  Serial.println("red");  break;
      case 2:
        setColor(0, 255, 0);  Serial.println("Green");   break;
      case 3:
        setColor(0, 0, 255);  Serial.println("blue"); break;
      case 4:
        digitalWrite(RedPin, LOW);   digitalWrite(GreenPin, LOW);    digitalWrite(BluePin, LOW);
        Serial.println("OFF");
        break;

      default:   
      break;  

    }
  #endif  

#endif

  }
  //if(Serial.available())
 // {
  //   bluetooth.write(Serial.read());
  //}

  
  
  #endif
  //Serial.print(rlen);

  #if 0
  if(debug_flag)
  {
    //for(int i=0; i<3; i++)
    for(int i = 0; i < rlen; i++)
    {
      Serial.print(buf[i]);
    }
    debug_flag=0;
  }
  #else
  
  #endif




}
