#ifndef _COLORLED_H_
#define _COLORLED_H_

int pwmActiveAll(void);
int pwmInactiveAll(void);
int pwmSetDuty(int dutyCycle, int pwmIndex);
int pwmSetPeriod(int Period, int pwmIndex);
int pwmSetPercent(int percent);
int pwmStartAll(void);
int pwmLedInit(void);

int pwmSetPercent_RED(int percent);
int pwmSetPercent_GREEN(int percent);
int pwmSetPercent_BLUE(int percent);
int ColorLED_Blue(void);
int ColorLED_Green(void);
int ColorLED_Red(void);
int ColorLED_White(void);


int pwmLedOff(void);
int pwmLed_thermalcheckmode(double a);

#endif
