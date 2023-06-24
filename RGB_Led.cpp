#include <SoftwareSerial.h>
#include "RGB_Led.h"
#include "Arduino.h"
#include "zDefine.h"
#include <Adafruit_NeoPixel.h>

extern char LED_Flag;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, NeoPixel, NEO_GRBW + NEO_KHZ800);


void RGB_LED_Init()
{
#if 0
	pinMode(RedPin, OUTPUT);
	pinMode(GreenPin, OUTPUT);
	pinMode(BluePin, OUTPUT);

	setColor(ON);
	delay(100);
	setColor(OFF);
	LED_Flag=1;
#else
	
#endif
}

int led_en=0;

#if 0

void setColor(int power_on)
{

	if(!led_en)
		power_on=OFF;
	switch(power_on)
	{
		case OFF:		digitalWrite(GreenPin, LOW);  	digitalWrite(RedPin, LOW); 		digitalWrite(BluePin, LOW);		break;
		case ON: 		digitalWrite(GreenPin, HIGH);  	digitalWrite(RedPin, HIGH); 	digitalWrite(BluePin, HIGH);	break;
		case RED_ON	:	digitalWrite(GreenPin, LOW);  	digitalWrite(RedPin, HIGH); 	digitalWrite(BluePin, LOW);		break;
		case GREEN_ON:	digitalWrite(GreenPin, HIGH);  	digitalWrite(RedPin, LOW); 		digitalWrite(BluePin, LOW);		break;
		case BLUE_ON:	digitalWrite(GreenPin, LOW);  	digitalWrite(RedPin, LOW); 		digitalWrite(BluePin, HIGH);	break;

		default : break;
		
	}


}
#else
void setColor(int power_on)
{

	if(!led_en)
		power_on=OFF;


	colorWipe(strip.Color(0, 0, 0, 255)); // 하얀색
	colorWipe(strip.Color(255, 0, 0, 0)); // 빨간색
	colorWipe(strip.Color(255, 50, 0, 0)); // 주황색
	colorWipe(strip.Color(255, 100, 0, 0)); // 노랑색
	colorWipe(strip.Color(0, 255, 0, 0)); // 초록색
	colorWipe(strip.Color(0, 165, 235, 0)); // 파란색
	colorWipe(strip.Color(0, 0, 255, 0)); // 남색
	colorWipe(strip.Color(105, 0, 105, 0)); // 보라색
	
}

#endif


void NeoPixel_Init()
{
	
	
	strip.begin();
	strip.show();
	
}

// 입력한 색으로 LED를 채워주는 함수
void colorWipe(unsigned int c) {
  for(unsigned int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}

// 255가지의 색을 표현하는 함수
unsigned int Wheel(unsigned int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}




