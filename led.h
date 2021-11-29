#ifndef _LED_LIBRARY_H_
#define _LED_LIBRARY_H_

int ledLibInit(void);	//이 라이브러리는 LED를 켜기 전에 반드시 한 번 불러주어야 함
int ledLibOnOff(int ledNumber, int onOff); //이 함수는 ledNumber에는 0~7d을 넣으면, 그에 해당하는 led를 켜거나 끄거나 해준다.
int ledLibStatus(void);
int ledLibExt(void);
int ledLibRaw(char ledwannabe);
int ledLibBlink(int ledNumber, int nth, int msec);
int ledLibMorseBlink(int ledNumber, int nth, int msecOn, int msecOff);

#define LED_DRV_NODE	"/dev/periled"
#endif
