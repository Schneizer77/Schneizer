#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"
#include "buzzer.h"


//////////////////부저 초기 파일접근 관련 함수////////////////////////

char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨


int findBuzzerSysPath(){
	DIR* dir_info = opendir ("/sys/bus/platform/devices/");
	int ifNotFound = 1;
	if (dir_info != NULL){
		while (1){
			struct dirent *dir_entry;
			dir_entry = readdir (dir_info);
			if (dir_entry == NULL) break;
			if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0){
				ifNotFound = 0;
				sprintf(gBuzzerBaseSysDir,"%s%s/", "/sys/bus/platform/devices/",dir_entry->d_name);
			}
		}
	}
	printf("find %s\n",gBuzzerBaseSysDir);
	return ifNotFound;
}
//버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX 의 XX를 결정하는 것



//////////////////부저 동작 관련 함수////////////////////////////////
int buzzerInit (void){
    if (findBuzzerSysPath()){
		printf("Error!\n");
		return 1;
    }
}



void buzzerON(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME); 
	int fd=open(path,O_WRONLY);
	write(fd, &"1", 1);
	close(fd);
}


void buzzerOFF(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
	int fd=open(path,O_WRONLY);
	write(fd, &"0", 1);
	close(fd);
}

//////////////음계(주파수) 설정 관련 함수/////////////////
void F_DO(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", 262);
	close(fd);
}

void F_RE(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", 294);
	close(fd);
}

void F_MI(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", 330);
	close(fd);
}

void F_PA(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", 349);
	close(fd);
}

void F_SOL(void) {
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", 392);
	close(fd);
}

void F_RA(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", 440);
	close(fd);
}

void F_SI(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", 494);
	close(fd);
}

void F_DO_High(void){
	char path[200];
	sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
	int fd=open(path,O_WRONLY);
	dprintf(fd, "%d", 523);
	close(fd);
}


///////////////////사용자 제작 함수/////////////////////////
void buzzerTest(void){
    F_DO();
    buzzerON();
    usleep(800000);
    F_RE();
    usleep(800000);
    F_MI();
    usleep(800000);
    F_PA();
    usleep(800000);
    F_SOL();
    usleep(800000);
    F_RA();
    usleep(800000);
    F_SI();
    usleep(800000);
    F_DO_High();
    usleep(800000);
    buzzerOFF();
}

void buzzerSiren(void){
    while(1){
        F_DO();
        buzzerON();
        sleep(1);
        buzzerOFF();
        
        F_MI();
        buzzerON();
        sleep(1);
        buzzerOFF();
    }
}
//출처: github.com/euleey/embedded_R
