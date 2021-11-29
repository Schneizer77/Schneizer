#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h> 

#define  INPUT_DEVICE_LIST	"/dev/input/event"
#define PROB_FILE	"/proc/bus/input/devices"

int probeButtonPath(char *newPath)
{
	int returnValue = 0;
	int number = 0;
	FILE *fp = fopen(PROBE_FILE, "rt");
#define HAVE_TO_FIND_1	"N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2	"H: Handlers=kbd event"
	while(!feof(fp))
	{
		char tmpStr[200];
		fgets(tmpStr, 200, fp);
		if (strcmp(tmpStr, HAVE_TO_FIND_1) == 0)
		{
			printf("YES! I found!: $s\r\n", tmpStr);
			returnValue = 1;
		}
		if((returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0))
		{
			printf ("-->%s", tmpStr);
			printf("\t%c\r\n", tmpStr[strlen(tmpStr) - 3]);
			number = tmpStr[strlen(tmpStr) - 3] - '0';
			break;
		}
	}
	fclose(fp);
	if (returnValue == 1)
	sprintf (newPath, "%s%d", INPUT_DEVICE_LIST, number);
	return returnValue;
}

int main(int argc, char *argv[])
{
	int    fp;
	int		readSize,inputIndex;
	struct input_event  stEvent;
	char inputDevPath[200] = {0,};
	if (probeButtonPath(inputDevPath) == 0)
	{
		printf ("ERROR! File Not Found!\r\n");
		printf ("Did you insmod?\r\n");
		return 0;
	}
	
	fp = open(INPUT_DEVICE_LIST, O_RDONLY);
	
	while(1)
	{
		readSize = read(fp, &stEvent , sizeof(stEvent));
		if (readSize != sizeof(stEvent))
		{
			continue;
		}

		if ( stEvent.type == EV_KEY)
		{
			printf("EV_KEY(");
			switch(stEvent.code)
			{
				case KEY_VOLUMEUP:	printf("Volume up key):");	break;
				case KEY_HOME:		printf("Home key):");		break;
				case KEY_SEARCH:	printf("Search key):");		break;
				case KEY_BACK:		printf("Back key):");		break;
				case KEY_MENU:		printf("Menu key):");		break;
				case KEY_VOLUMEDOWN:printf("Volume down key):");break;
			}
			if (stEvent.value)
				printf("pressed\n");
			else
				printf("released\n");
		}
		else 
		{
			// do notthing
		}
	}
	close(fp);		
}
