#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnddrv.h"


#define FND_DRIVER_NAME		"/dev/perifnd"

void doHelp(void)
{
	printf("Usage:\n");
	printf("fndtest [option] [displaynum] [maxcounter]  >\n");
	printf("option   s  : static display  , displaynum range 0 ~ 999999\n");
	printf("option   t  ; time display  \n"); 
	printf("option   c  : count from 0 to maxcounter .\n");
	printf("option   o  : fnd off\n");
	printf("ex) fndtest s '123456'  ; display  '123456' \n");
	printf("ex) fndtest t 		;display current time \n");
	printf("ex) fndtest c 10 ; display counting number  from  0  to  10  with 1 Second interval.\n");
	printf("ex) fndtest 0		;display off \n");
}

#define ONE_SEG_DISPLAY_TIME_USEC	1000
// return 1 => success  , 0 => error

#define MODE_STATIC_DIS		0
#define MODE_TIME_DIS		1
#define MODE_COUNT_DIS		2


int main(int argc , char **argv)
{
	int mode ;
	int number,counter;
	
	fndDisp(123456, 0);
	sleep(1);
	counter_10();
    sleep(1);

	
	timeDis();
	sleep(1);
	fndDisp(123456, 0);
	sleep(1);
	fndDisp(234567, 0);
	sleep(1);	
	fndDisp(345678, 0);
	sleep(1);	
	fndOff();
	
	return 0;
}
