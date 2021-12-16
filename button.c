#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"
// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event" //실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
#define PROBE_FILE input"/proc/bus/input/devices" //PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static char inputDevPath[200]={0,};
static int fp;
int readSize,inputIndex;
struct input_event stEvent; //구조체
static int err;
static int msgID;
static int i; //에러확인용 변수
static int count = 0;
structMyMsg messageTxData;
pthread_t tid; //pthread 주소 return

typedef struct data {    //데이터 저장용 변수 선언
    char bank[1000];
    } data;

data databuffer; //데이터 저장

int Initialize_Button(void)
{
	// first read input device
	if (probeButtonPath(inputDevPath) == 0)  //버튼 실행
	{
		printf ("ERROR! File Not Found!\r\n");
		printf ("Did you insmod?\r\n");
		return 0;
	}
	printf ("inputDevPath: %s\r\n", inputDevPath);  //위에서 입력받은 event 번호 출력
	fp = open(inputDevPath, O_RDONLY);                //그 파일을 열고

	msgID = msgget ((key_t)9999, IPC_CREAT|0666);
    if (msgID == -1){                               //우체통 생성 확인
        printf("Cannot get msgQueueID\n"); 
        return -1;
    }
    
	err = pthread_create(&tid, NULL, &buttonThFunc, NULL);  //thread생성
	if (err != 0) 
		printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인

	pthread_join(tid,NULL); //Thread 종료시까지 wait

	return fp;
	}

	void* buttonThFunc(void *arg){	//Thread가 실행할 함수  
		while(1)
		{
			readSize = read(fp, &stEvent , sizeof(stEvent));  //button Device driver는 input_event 구조체로 읽는데 이름은 stEvent
			if (readSize != sizeof(stEvent))   //Read하는 크기가 정해져있다!
			{
				continue;                           //잘 읽었다면
			}
			if (stEvent.type == EV_KEY){
			printf("EV_KEY(");
			switch(stEvent.code)
			{
				case KEY_VOLUMEUP: 
					printf("Volume up key):"); 
					int button1 = 5;
					snprintf(messageTxData.bulk_message, sizeof(messageTxData.bulk_message)-1, "%d", button1);
					printf ("button %d\r\n",button1);
				break;
			
				case KEY_HOME:
					printf("Home key):"); 
					int button2 = 1;
					snprintf(messageTxData.bulk_message, sizeof(messageTxData.bulk_message)-1, "%d", button2);
					printf ("button %d\r\n",button2);
				break;
				
				case KEY_SEARCH: 
					printf("Search key):"); 
					int button3 = 3;
					snprintf(messageTxData.bulk_message, sizeof(messageTxData.bulk_message)-1, "%d", button3);
					printf ("button %d\r\n",button3);
				break;
	
				case KEY_BACK: 
					printf("Back key):"); 
					int button4 = 2;
					snprintf(messageTxData.bulk_message, sizeof(messageTxData.bulk_message)-1, "%d", button4);
					printf ("button %d\r\n",button4);
				break;
				
				case KEY_MENU: 
					printf("Menu key):"); 
					int button5 = 4;
					snprintf(messageTxData.bulk_message, sizeof(messageTxData.bulk_message)-1, "%d", button5);
					printf ("button %d\r\n",button5);
				break;
				
				case KEY_VOLUMEDOWN: 
					printf("Volume down key):"); 
					int button6 = 6;
					snprintf(messageTxData.bulk_message, sizeof(messageTxData.bulk_message)-1, "%d", button6);
					printf ("button %d\r\n",button6);
				break;
			}
			messageTxData.messageType = 1; //1 is good enough
			msgsnd(msgID, &messageTxData, sizeof(messageTxData.bulk_message), 0);


			if ( stEvent.value ){
				int button_pressed = 7;
				snprintf(messageTxData.bulk_message, sizeof(messageTxData.bulk_message)-1, "%d", button_pressed);
				printf("pressed\n");             //value == 1이면 key가 안눌렸다가 눌렸을 때, value==0이면 눌렀다가 땠을 때
				messageTxData.messageType = 1; //1 is good enough
				msgsnd(msgID, &messageTxData, sizeof(messageTxData.bulk_message), 0);
			}
			else {
				int button_released =8;
				snprintf(messageTxData.bulk_message, sizeof(messageTxData.bulk_message)-1, "%d", button_released);
				printf("released\n");
				messageTxData.messageType = 1; //1 is good enough
				msgsnd(msgID, &messageTxData, sizeof(messageTxData.bulk_message), 0);
			}
		}	// if ( stEvent.type == EV_KEY) 끝
	}	//while끝
}	//함수끝



// first read input device
int probeButtonPath (char *newPath){
	int returnValue = 0; //button에 해당하는 event#을 찾았나?
	int number = 0; //찾았다면 여기에 집어넣자
	FILE *fp = fopen("/proc/bus/input/devices","rt"); //파일을 열고  
	//PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일
	#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
	#define HAVE_TO_FIND_2 "H: Handlers=kbd event"
	while(!feof(fp)){ //끝까지 읽어들인다.
		char tmpStr[200]; //200자를 읽을 수 있게 버퍼
		fgets(tmpStr,200,fp); //최대 200자를 읽어봄
		//printf ("%s",tmpStr);
		if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0){
			printf("YES! I found!: %s\r\n", tmpStr);
			returnValue = 1; //찾음
		}

		if ((returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0)){ //찾은 상태에서 Event??을 찾았으면
			printf ("-->%s",tmpStr);
			printf("\t%c\r\n",tmpStr[strlen(tmpStr)-3]);
			number = tmpStr[strlen(tmpStr)-3] - '0';
			//Ascii character '0'-'9' (0x30-0x39)
			//to interger(0)
			break;
		}
	}
	fclose(fp);
	if (returnValue == 1)
		sprintf (newPath,"%s%d","/dev/input/event",number);    //newPath == /dev/input/event 만들어줌! 
		//실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
	return returnValue;
}


int which_Button_did_you_push(void){		
	while(1){
		readSize = read(fp, &stEvent , sizeof(stEvent));  //button Device driver는 input_event 구조체로 읽는데 이름은 stEvent
		if (readSize != sizeof(stEvent)){   //Read하는 크기가 정해져있다!
			continue;                           //잘 읽었다면
		}
		if ( stEvent.type == EV_KEY){
			printf("EV_KEY(");
			switch (stEvent.code){
				case KEY_VOLUMEUP: printf("Volume up key):"); break;
				case KEY_HOME: printf("Home key):"); break;
				case KEY_SEARCH: printf("Search key):"); break;
				case KEY_BACK: printf("Back key):"); break;
				case KEY_MENU: printf("Menu key):"); break;
				case KEY_VOLUMEDOWN: printf("Volume down key):"); break;
			}
			if ( stEvent.value ) 
				printf("pressed\n");             //value == 1이면 key가 안눌렸다가 눌렸을 때, value==0이면 눌렀다가 땠을 때
			else 
				printf("released\n");
		} //End of if
		else // EV_SYN
		; // do notthing
	} // End of While
}
