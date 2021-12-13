#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

int spi_init(void);
char * spi_read_lm74(int file);
double read_temperature(void);

#endif
