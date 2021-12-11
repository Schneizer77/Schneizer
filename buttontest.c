#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

typedef struct
{
	long int messageType;
	char bulk_message[1000];
} structMyMsg;

static int cmp1, cmp2, cmp3,cmp4 ,cmp5, cmp6, cmp7, cmp8;  //두 문자열이 같으면 cmp = 0

int main (void)
{
	structMyMsg messageRxData;
	int msgID = msgget((key_t)9999, IPC_CREAT|0666);
		if(msgID == -1){                               //우체통 생성 확인
			printf("Cannot get msgQueueID\n"); 
			return -1;
		}

while (1) {
	int returnValue = 0;
	returnValue = msgrcv(msgID, &messageRxData, sizeof(messageRxData.bulk_message), 0, 0); //Wait here if no message

	cmp1 = strcmp(messageRxData.bulk_message, "1");
	cmp2 = strcmp(messageRxData.bulk_message, "2");
	cmp3 = strcmp(messageRxData.bulk_message, "3");
	cmp4 = strcmp(messageRxData.bulk_message, "4");
	cmp5 = strcmp(messageRxData.bulk_message, "5");
	cmp6 = strcmp(messageRxData.bulk_message, "6");
	cmp7 = strcmp(messageRxData.bulk_message, "7");
	cmp8 = strcmp(messageRxData.bulk_message, "8");


	if(cmp1==0)
		printf("button1 ");
	else if (cmp2==0)
		printf("button2 ");
	else if (cmp3==0)
		printf("button3 ");
	else if (cmp4==0)
		printf("button4 ");
	else if (cmp5==0)
		printf("button5 ");
	else if (cmp6==0)
		printf("button6 ");
	else if (cmp7==0)
		printf("pressed\n");
	else if (cmp8==0)
		printf("released\n");
}




}
