
COMPILE = gcc -g


main: main.o airport.o ll.o tree.o
	$(COMPILE) -o main main.o airport.o ll.o tree.o

main.o: main.c airport.h ll.h tree.h
	$(COMPILE) -c main.c

airport.o: airport.c airport.h
	$(COMPILE) -c airport.c

ll.o: ll.c ll.h
	$(COMPILE) -c ll.c

tree.o: tree.c tree.h
	$(COMPILE) -c tree.c

lean: clean #ahh yes
clean:
	/bin/rm -f *.o run

production: airport.o ll.o tree.o
	gcc -O3 -o main main.o airport.o ll.o tree.o
