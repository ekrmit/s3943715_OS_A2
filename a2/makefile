//Make to seperatly generate FIFO, SFJ and RR executables

CC = gcc

CFLAGS = -Wall -g

all: fifo sfj rr

fifo: fifo.cpp pcb.h types.h
	$(CC) $(CFLAGS) -o fifo fifo.c

sfj: sfj.cpp pcb.h types.h

	$(CC) $(CFLAGS) -o sfj sfj.c

rr: rr.cpp pcb.h types.h
	$(CC) $(CFLAGS) -o rr rr.c

clean: 
	rm -f fifo sfj rr
