CFLAGS = -g -Wall 
CC = gcc
   
objects = main.o calculations.o prioqueue.o fifoqueue.o server.o customer.o

queuesim: $(objects)
	$(CC) -o queuesim $(objects) -lm

main.o: main.c calculations.h prioqueue.h fifoqueue.h server.h customer.h
calculations.o: calculations.c calculations.h
customer.o: customer.c customer.h
prioqueue.o: prioqueue.c prioqueue.h
fifoqueue.o: fifoqueue.c fifoqueue.h
server.o: server.c server.h

.PHONY: clean
clean:
	rm queuesim $(objects)
