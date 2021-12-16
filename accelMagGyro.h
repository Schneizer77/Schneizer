#ifndef _ACCELMAGGYRO_H_
#define _ACCELMAGGYRO_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

void p_Accel(void);
void p_Magnet(void);
void p_Gyro(void);

#endif
