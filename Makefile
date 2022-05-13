EXEC = dijkstra
CC = g++
CFLAGS = -c -Wall

$(EXEC) : main.o util.o heap.o graph.o
	$(CC) -o $(EXEC) main.o util.o heap.o graph.o

main.o  : main.cpp util.o heap.o graph.o
	$(CC) $(CFLAGS) main.cpp

graph.o	: graph.h graph.cpp
	$(CC) $(CFLAGS) graph.cpp

util.o  : util.h util.cpp
	$(CC) $(CFLAGS) util.cpp

heap.o  : heap.h heap.cpp
	$(CC) $(CFLAGS) heap.cpp

clean   :
	rm *.o dijkstra
