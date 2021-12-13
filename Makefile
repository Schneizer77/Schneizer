all:main.elf
	
main.elf: libMyPeri.a main.o
	arm-linux-gnueabi-gcc main.o -lpthread -l MyPeri -L. -o main.elf

main.o : main.c
	arm-linux-gnueabi-gcc -c main.c -o main.o

libMyPeri.a: led.o button.o fnd.o textlcd.o colorled.o temperature.o accelMagGyro.o buzzer.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o fnd.o textlcd.o colorled.o temperature.o accelMagGyro.o buzzer.o

accelMagGyro.o : accelMagGyro.c accelMagGyro.h
	arm-linux-gnueabi-gcc -c accelMagGyro.c -o accelMagGyro.o

temperature.o : temperature.c temperature.h
	arm-linux-gnueabi-gcc -c temperature.c -o temperature.o

colorled.o : colorled.c colorled.h
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o
	
led.o: led.c led.h
	arm-linux-gnueabi-gcc -c led.c -o led.o

button.o : button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o

fnd.o : fnd.c fnd.h
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o

textlcd.o : textlcd.c textlcd.h
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o

buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc --static -c buzzer.c -o buzzer.o

clean:
	rm -rf *.o *.a *.el-
