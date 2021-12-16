#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "led.h"

static int fd = 0;
static int ledStatus = 0;

int ledLibInit(void)	//이 라이브러리는 LED를 켜기 전에 반드시 한 번 불러주어야 함
{
	printf ("Led Library Initialize...\r\n");
	fd = open(LED_DRV_NODE, O_RDWR);
	printf ("FD: %d\r\n", fd);
	if (fd < 0)
	{
		printf("Device Open Error!\r\n");
		exit(1);
	}
	ledStatus = 0;
	ledLibRaw(ledStatus);
}

int ledLibOnOff(int ledNumber, int onOff) //이 함수는 ledNumber에는 0~7d을 넣으면, 그에 해당하는 led를 켜거나 끄거나 해준다.
{
	int lamp = 1;
	lamp = lamp << ledNumber;	//00010000 해당하는 전구비트만 1로 바뀜
	ledStatus = (ledStatus &(~lamp));	//해당하는 전구비트만 0으로 바꿈.
	if (onOff)
		ledStatus = ledStatus | lamp;	//해당하는 전구비트만 1로 바꾸고 나머지는 그대로.
	ledLibRaw(ledStatus);
	return 1;
}

int ledLibStatus(void)	//현재 LED상태 확인. 모든 LED가 켜져있으면 0xff를 리턴하고, 
{
	return ledStatus;
}

int ledLibExt(void)
{
	ledLibRaw(0);	//전부 끔.
	close(fd);
}

int ledLibRaw(char ledwannabe)
{
	if (fd > 0)
	{
		write(fd, &ledwannabe, 1);
	}
	else
	{
		printf("WRONG! you must open device NODE!\r\n");
		exit(2);
	}
	ledStatus = ledwannabe;
	return 1;
}

int ledLibBlink(int ledNumber, int nth, int msec) //1~8까지의 LED를 하나 골라서 msec주기로 n번 깜빡임.
{
	ledLibMorseBlink(ledNumber, nth, msec, msec);
}

int ledLibMorseBlink(int ledNumber, int nth, int msecOn, int msecOff)
{
	int i = 0;
	for(i = 0; i < nth; i++)
	{
		ledLibOnOff(ledNumber, 1); //ON.
		usleep(1000*msecOn);
		ledLibOnOff(ledNumber, 0); //OFF.
		usleep(1000*msecOff);	
	}
}
//출처: github.com/euleey/embedded_R
