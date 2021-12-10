include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
char gbuf[10];

#include "temperature.h"

int main(int argc, char **argv){
 read_temperature();
int main(void)
{
    double t;
    t = read_temperature();

    printf("이것은 read_temperature 함수의 출력값(온도)입니다 : %lf \n", t);
    return 0;
}
