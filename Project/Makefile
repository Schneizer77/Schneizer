CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all:
	libLibrary.a Piano.elf 

Piano.elf:
	Piano.c libLibrary.a 
	$(CC) Piano.c -o Piano.elf -l Library -L.
	scp Piano.elf ecube@192.168.219.195:/home/ecube/

libLibrary.a:
	led.o button.o buzzer.o fnd.o textlcd.o Touch.o
	$(AR) rc led.o libLibry.a button.o buzzer.o fnd.o textlcd.o Touch.o
	scp libLibrary.a ecube@192.168.219.195:/home/ecube/

led.o:
	led.c led.h
	
button.o:
	button.c button.h
	
buzzer.o:
	buzzer.c buzzer.h
	
fnd.o:
	fnd.c fnd.h
	
textlcd.o:
	textlcd.c textlcd.h

Touch.o:
	Touch.c Touch.h

clean:
	rm -f *.o *.a *.elf
