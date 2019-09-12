COMPILE = gcc -g

main: main.o item.o inventory.o
	$(COMPILE) -o main main.o item.o inventory.o

main.o: main.c inventory.h item.h
	$(COMPILE) -c main.c

item.o: item.h item.c
	$(COMPILE) -c item.c

inventory.o: inventory.h inventory.c
	$(COMPILE) -c inventory.c


clean:
	/bin/rm -f *.o main