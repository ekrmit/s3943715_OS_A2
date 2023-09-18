CC = g++
CFLAGS = -Wall -Werror -g

all: fifo sfj rr

fifo: fifo.o
	$(CC) $(CFLAGS) $? -o $@

sfj: sfj.cpp
	$(CC) $(CFLAGS) $? -o $@

rr: rr.cpp
	$(CC) $(CFLAGS) $? -o $@

clean: 
	rm -f *.o fifo sfj rr *.o
