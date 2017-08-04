CFLAGS = -g -Wall 
CC = gcc
   
objects = main.o document.o chkgets.o dictionary.o word.o freqword.o frequency.o

docusim: $(objects)
	$(CC) -o docusim $(objects) -lm

main.o: main.c document.h chkgets.h dictionary.h word.h freqword.h frequency.h
document.o: document.c document.h
chkgets.o: chkgets.c chkgets.h
dictionary.o: dictionary.c dictionary.h
word.o: word.c word.h
freqword.o: freqword.c freqword.h
frequency.o: frequency.c frequency.h

.PHONY: clean
clean:
	rm docusim $(objects)
