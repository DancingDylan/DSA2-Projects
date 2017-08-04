CFLAGS = -g -Wall 
CC = gcc

EXE = tspBruteForce tspGenetic                       #Executables
OBJ = tspBruteForce.o tspGenetic.o citygraph.o route.o       #Object Files
SRC1 = tspBruteForce.o citygraph.o                   #Source Files for tspBruteForce
SRC2 = tspGenetic.o citygraph.o	route.o					 #Source Files for tspGenetic

all: $(EXE)

tspBruteForce: $(SRC1)
	$(CC) -o tspBruteForce $(SRC1) -lm
	
tspGenetic: $(SRC2)
	$(CC) -o tspGenetic $(SRC2) -lm

.PHONY: clean
clean:
	rm $(EXE) $(OBJ)
