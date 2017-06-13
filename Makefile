OBJS = sniffer.o processing.o
CC = gcc
CFLAGS = -c -Wall

all: $(OBJS)
	$(CC) $(OBJS) -o sniffer

sniffer.o: sniffer.c processing.h
	$(CC) $(CFLAGS) sniffer.c

processing.o: processing.h processing.c 
	$(CC) $(CFLAGS) processing.c

clean:
	rm *.o sniffer
