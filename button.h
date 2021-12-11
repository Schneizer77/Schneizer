#ifndef _BUTTON_H_
#define _BUTTON_H_
#define MESSAGE_ID 1122
typedef struct
{
	long int messageNum;
	int keyInput;
	int pressed;
} BUTTON_MSG_T;

int Initialize_Button(void);
int probeButtonPath(char *newPath);
int which_Button_did_you_push(void);
void* buttonThFunc(void *arg);
int buttonExit(void);

#ifndef _MY_MESSAGE_H_
#define _MY_MESSAGE_H_
#define MY_MESSAGE_ID 9999
typedef struct
{
	long int messageType;
	char bulk_message[1000];
} structMyMsg;
#endif

#endif
