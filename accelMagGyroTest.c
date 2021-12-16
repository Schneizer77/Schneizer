#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


#include "accelMagGyro.h"

int main (void)
{
    p_Accel();
    p_Magnet();
    p_Gyro();

    return 0;
}
