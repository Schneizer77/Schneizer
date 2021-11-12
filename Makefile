all: final.elf
	
final.elf: 1.o 2.o
	gcc 1.o 2.o -o final.elf

1.o: 1.c
	gcc -c 1.c -o 1.o

2.o: 2.c
	gcc -c 2.c -o 2.o
