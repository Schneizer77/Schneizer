#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include  <pthread.h>
#include  "button.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROB_FILE "proc/bus/input/devices"
#define HAVE_TO_FIND_1	"N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2	"H: Handlers=kbd event"
#define MUTEX_ENABLE 1

pthread_t tid[2];
int jobindex = 0;

pthread_mutex_t lock;

void* buttonThFunc(void *arg)
{
#if MUTEX_ENABLE
	pthread_mutex_lock(&lock)
#endif
	unsigned long i = 0;
	jobindex += 1;
	printf("\n Job %d finished\r\n", jobindex);
	
#if MUTEX_ENABLE
	pthread_mutex_unlock(&lock);
#endif
	return NULL;
}

int buttonInit(void)
{
	int i = 0;
	int err;
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("\n Mutes Init Failed!\r\n");
		return 1;
	}
	
	if (probeButtonPath(buttonPath) == 0)
		return 0;
	fd = open(buttonPath, O_RDONLY);
	msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
	pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
	return 1;
	
	pthread_join (tid[0], NULL);
	pthread_join (tid[1], NULL);
	return 0;
}
