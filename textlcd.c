#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "textlcd.h"



#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

void doHelp(void)
{
	printf("usage: textlcdtest <linenum> <'string'>\n");
	printf("       linenum => 1 ~ 2\n");	
	printf("  ex) textlcdtest 2 'test hello'\n");
	
}


//-------------------디스플레이모드 Enable----------------//
int lcdtextInit(void)
{   
    stTextLCD  stlcd; 
	memset(&stlcd,0,sizeof(stTextLCD));
    int fd;
	stlcd.cmd = CMD_DISPLAY_MODE;               //cmd : display mode
    stlcd.cmdData= 0x04;						//cmdData : Enable
    
    fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));

    close(fd);

	return 0;

}


//-------------------Write String 하는 함수----------------//
int lcdtextWrite(unsigned int linenum, char *data)  //입력은 linenum : 1 또는 2(몇째줄에 쓸지) , char *은 쓸 스트링 주소값 넣기
{   
    stTextLCD  stlcd; 
	memset(&stlcd,0,sizeof(stTextLCD));

    int fd;
	int len; 

    if(linenum == 1)
        stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
    else if (linenum == 2)
        stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
    else{
        printf("linenum: %d wrong. range (1~2)\n", linenum);
        return 1;
    }

    len = strlen(data);

	if ( len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],data,COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],data,len);
	}

	stlcd.cmd = CMD_WRITE_STRING;
    
     fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));

    close(fd);

	return 0;
  
}



//-------------------디스플레이모드 Disalbe----------------//
int lcdtextOff(void)
{   
    stTextLCD  stlcd; 
	memset(&stlcd,0,sizeof(stTextLCD));
    int fd;
	stlcd.cmd = CMD_DISPLAY_MODE;					//cmd : display mode
    stlcd.cmdData= 0x00;							//cmdData : disnable
    
    fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));

    close(fd);

	return 0;

}
// 출처: github.com/euleey/embedded_R
