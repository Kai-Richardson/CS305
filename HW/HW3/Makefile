
COMPILE = gcc -g


run: main.o printer.o printJob.o
	$(COMPILE) -o run main.o printer.o printJob.o

main.o: main.c printer.h printJob.h
	$(COMPILE) -c main.c

printer.o: printer.c printer.h printJob.h
	$(COMPILE) -c printer.c

printJob.o: printJob.c printer.h printJob.h
	$(COMPILE) -c printJob.c

lean: clean #ahh yes
clean:
	/bin/rm -f *.o run
