CFLAGS = -g -Wall 
CC = gcc
   
objects = rndgen.o fileIO.o

rndFile: $(objects)
	$(CC) -o rndFile $(objects) -lm

fileIO.o: fileIO.c rndgen.h
rndgen.o: rndgen.c rndgen.h

.PHONY: clean
clean:
	rm rndFile $(objects)