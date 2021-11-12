all: final.elf
	
final.elf: main.o 1.o 2.o
	gcc main.o 1.o 2.o -o final.elf

main.o: myProject.h
	gcc -c main.c -o main.o

1.o: 1.c myProject.h
	gcc -c 1.c -o 1.o

2.o: 2.c myProject.h
	gcc -c 2.c -o 2.o
clean:
	rm -rf *.o
