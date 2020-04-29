CF = -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -lglib-2.0
LF = -lglib-2.0 -lm
CC = gcc -O4 -g
SRCS = main.c graph.c dijkstra.c
OBJS = main.o graph.o dijkstra.o

routeFinder: $(OBJS) main.h graph.h
	$(CC) -o routeFinder $(OBJS) $(LF)

main.o:	main.c graph.c graph.h
	$(CC) -c main.c $(CF) $(LF)

graph.o: graph.c graph.h
	$(CC) -c graph.c $(CF) $(LF)

dijkstra.o: dijkstra.c graph.h main.h
	$(CC) -c dijkstra.c $(CF) $(LF)

# A rule to clean up the directory of all object files and executable
# file.
clean:
	/bin/rm -f *.o routeFinder

