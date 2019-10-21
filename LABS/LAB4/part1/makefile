COMPILE = gcc $(COMPILE_SWITCHES)

OFILES = president.o test1.o

test1: $(OFILES)
	$(COMPILE) -o test1 $(OFILES)

test1.o: test1.c test1.h
	$(COMPILE) -c test1.c

president.o: president.c president.h
	$(COMPILE) -c president.c



clean:
	/bin/rm -f *.o test1
