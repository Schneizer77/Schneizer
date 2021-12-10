#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

int spi_init(char filename[40]);
int spi_init(void);
char * spi_read_lm74(int file);
void read_temperature(void);
double read_temperature(void);

#endif 
