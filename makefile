CC = gcc
CFLAGS = -c

all: exec

exec: exec.c
	$(CC) $(CFLAGS) exec.c
	$(CC) -o exec exec.o


clean:
	rm -f exec 
	rm *.o
