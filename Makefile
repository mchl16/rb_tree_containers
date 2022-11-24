CC=g++
CFLAGS_DEBUG=-g -Wall -Werror -std=c++2a
CFLAGS=-O2 -std=c++2a

default:
	$(CC) $(CFLAGS) main.cpp -o main.exe

debug:
	$(CC) $(CFLAGS_DEBUG) main.cpp -o main.exe

clean:
	rm -rf *.o *.exe