projectname := bittystring

CC := gcc
CCFLAGS := -std=c99

all: tests

lib: bittystring.o
	ar rcs bittystring.a bittystring.o

tests: tests.o bittystring.o
	$(CC) tests.o bittystring.o -o tests

tests.o: src/tests.c
	$(CC) $(CCFLAGS) -c src/tests.c

bittystring.o: src/bittystring.c
	$(CC) $(CCFLAGS) -c src/bittystring.c

clean:
	rm -f *.o *.a
	rm tests

