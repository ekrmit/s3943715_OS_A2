CC = g++
CFLAGS = -Wall -Werror -g

all: fifo sjf rr

fifo: fifo.cpp pcb.o
	$(CC) $(CFLAGS) $? -o $@

sjf: sjf.cpp pcb.o
	$(CC) $(CFLAGS) $? -o $@

rr: rr.cpp pcb.o
	$(CC) $(CFLAGS) $? -o $@

clean: 
	rm -f *.o fifo sjf rr *.o
