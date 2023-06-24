#ifndef __RGB_LED_H_
#define __RGB_LED_H_

void _printf(const char *s, ...);
void setColor(int power_on);
void RGB_LED_Init();
void NeoPixel_Init();
void colorWipe(unsigned int c);
unsigned int Wheel(unsigned int WheelPos);


#endif
