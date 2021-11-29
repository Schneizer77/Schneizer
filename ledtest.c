#include <stdio.h>
#include "led.h"

int main (void)
{
	ledLibInit();
	
	ledLibRaw(0xFF);
	sleep(1);	
	ledLibRaw(0xAA);
	sleep(1);	
	ledLibRaw(0x55);
	sleep(1);
	ledLibRaw(0x0);
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		ledLibOnOff(i, 1);
		sleep(1);
		printf("0x%02X--ok?\r\n", ledLibStatus());
		
		ledLibOnOff(i, 0);
		sleep(1);
	}
	ledLibBlink(5, 10, 100); //1번 LED를 100ms로 10번 깜빡임.
	
	ledLibMorseBlink(2, 3, 500, 500);	//0.5초 on, 0.5초 off, 3회 깜빡임 == S
	ledLibMorseBlink(2, 3, 1500, 1500);	//1.5초 on, 1.5초 off, 3회 깜빡임 == O
	ledLibMorseBlink(2, 3, 500, 500);	//0.5초 on, 0.5초 off, 3회 깜빡임 == S
	
	sleep(2);
	ledLibExt();

}
