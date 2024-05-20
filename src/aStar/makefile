CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=testastar
SRC= $(wildcard *.c) ../heap/myheap.c ../list/mylist.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(EXEC).o: astar.h
astar.o: astar.h
../heap/myheap.o: ../heap/heap.h
../list/mylist.o: ../list/list.h



%.o: %.c
	$(CC) -o $@ -c $<


clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f $(EXEC)
	rm -f *.svg

