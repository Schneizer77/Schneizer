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



int main(void)
{   
    int one = 1;
    int two = 2;
    char abc[10] = "Hello";
    char xyz[10] = "embeded";

    lcdtextInit();

    lcdtextWrite(one, abc);
    lcdtextWrite(two, xyz);
    sleep(5);
    
    lcdtextOff();

    return 0;
}
