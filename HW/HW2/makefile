COMPILE = gcc -g


find_path: main.o load.o hexmaze.o
	$(COMPILE) -o find_path main.o load.o hexmaze.o

main.o: main.c load.h hexcell.h hexmaze.h
	$(COMPILE) -c main.c

load.o: load.c load.h hexmaze.h hexcell.h
	$(COMPILE) -c load.c

hexmaze.o: hexmaze.c load.h hexmaze.h hexcell.h
	$(COMPILE) -c hexmaze.c


clean:
	/bin/rm -f *.o find_path