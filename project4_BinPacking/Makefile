CFLAGS = -g -Wall 
CC = gcc
   
objects = main.o bins.o packing.o

binPacking: $(objects)
	$(CC) -o binPacking $(objects) -lm

main.o: main.c bins.h packing.h
bins.o: bins.c bins.h
packing.o: packing.c packing.h

.PHONY: clean
clean:
	rm binPacking $(objects)
