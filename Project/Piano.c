#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/kd.h> //touchscreen
#include <sys/ioctl.h> //touchscreen
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/input.h>
#include "Touch.h"
#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "fnd.h"
#include "textlcd.h"

static int msgID = 0;
static int msgIDTouch = 0;
int Messageclean = 0;
static int ledvalue;
void *piano();
int play;
int x,y;
int state;
int check;


int main(void)
{   
    /*터치스크린 깨짐방지*/
    int conFD = open ("/dev/tty0", O_RDWR);
    ioctl(conFD, KDSETMODE, KD_GRAPHICS);
    close (conFD);
    
    /*init*/
    textlcdinit();
    msgID=buttonLibInit();
    buzzerInit();
    ledLibInit();
    msgIDTouch=TouchLibInit();
    Colorledinit();

    while(1){}
    TouchLibExit();
    buttonLibExit();
    ledLibExit();
    buzzerExit();
    textlcdexit();
    return 1;
}

void *piano()
{
    lcdtextwrite("1", "     PIANO     ");
    lcdtextwrite("2", "===============");
    print_bmp("./bmp/piano.bmp");

    while(check==1){
		if((x > 0) && (x < 100) && (y > 0) && (y < 200)){	//건반 범위, 도
			system("aplay -d 1  ./파일위치/파일이름"); //system명령을 수행, 
			Colorledwrite(100, 0, 100);
		}
		else if((x > 100) && (x < 200) && (y > 0) && (y < 200)){//레
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(90, 0, 100);
		}
		else if((x > 200) && (x < 300) && (y > 0) && (y < 200)){//미
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(80, 0, 100);
		}
		else if((x > 300) && (x < 400) && (y > 0) && (y < 200)){//파
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(70, 0, 100);
		}
		else if((x > 400) && (x < 500) && (y > 0) && (y < 200)){//솔
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(60, 0, 100);
		}
		else if((x > 500) && (x < 600) && (y > 0) && (y < 200)){//라
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(50,0,100);
		}
		else if((x > 600) && (x < 700) && (y > 0) && (y < 200)){//시
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(40, 0, 100);
		}
		else if((x > 700) && (x < 800) && (y > 0) && (y < 200)){//도
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(30, 0, 100);
		}
		else if((x > 800) && (x < 900) && (y > 0) && (y < 200)){//레
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(20,0,100);
		}
		else if((x > 900) && (x < 1000) && (y > 0) && (y < 200)){//미
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(100, 0, 90);
		}      
		else if((x > 60) && (x < 126) && (y > 200) && (y < 600)){//도#
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(100, 0, 80);
		}      
		else if((x > 180) && (x < 245) && (y > 200) && (y < 600)){//레#
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(100, 0, 70);
		}      
		else if((x > 370) && (x < 435) && (y > 200) && (y < 600)){//파#
			system("aplay  -d 1 ./파일위치/파일이름");
			Colorledwrite(100, 0, 60);
		}      
		else if((x > 490) && (x < 545) && (y > 200) && (y < 600)){//솔#
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(100, 0, 50);
		}      
		else if((x > 600) && (x < 655) && (y > 200) && (y < 600)){//라#
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(100, 0, 40);
		}      
		else if((x > 770) && (x < 825) && (y > 200) && (y < 600)){//도#
			system("aplay  -d 1 ./파일위치/파일이름");
			Colorledwrite(100, 0, 30);
		}
		else if((x > 890) && (x < 950) && (y > 200) && (y < 600)){//레#
			system("aplay -d 1  ./파일위치/파일이름");
			Colorledwrite(100,0,20);
		}
	}
	printf("피아노 종료\n");
	pthread_exit(NULL); 
}


void *statethFunc()
{
    while(1){ //터치가 현재 눌려있는 상태인지 확인하는 코드
		if(state == 0){
			x=0;
			y=0;
		}
        usleep(10000);
	}
}
