#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define COLOR_LED_DEV_R_ "/sys/class/pwm/pwmchip0/"
#define COLOR_LED_DEV_G_ "/sys/class/pwm/pwmchip1/"
#define COLOR_LED_DEV_B_ "/sys/class/pwm/pwmchip2/"
#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_DUTY "pwm0/duty_cycle"
#define PWM_PERIOD "pwm0/period"
#define PWM_ENABLE "pwm0/enable"
#define PWM_COLOR_R 0
#define PWM_COLOR_G 1
#define PWM_COLOR_B 2
#define PWM_PERIOD_NS 1000000 //ns. = 1ms = 1khz 

#include "colorled.h"

int main(void) 
{   
    //---입력한 온도 값이라고 생각---//
    double a = 100;
    double b = 70;
    double c = 50;
    double d = 30;
    
    //---led 초기셋팅---//
    pwmLedInit();

    //---개별 조명 컨트롤---//
    ColorLED_White();
    sleep(1);
    ColorLED_Red();
    sleep(1);
    ColorLED_Green();
    sleep(1);
    ColorLED_Blue();
    sleep(1);
    
    //---온도값에 따른 색상 변화 함수---//
    pwmLed_thermalcheckmode(a);
    sleep(2);
    pwmLed_thermalcheckmode(b);
    sleep(2);
    pwmLed_thermalcheckmode(c);
    sleep(2);
    pwmLed_thermalcheckmode(d);
    sleep(2);
    
    //---led끄기 및 종료---//
    pwmLedOff();

    return 0;
}
