CC = gcc
CFLAGS = -g -Wall

main:main.o cjson.o
	$(CC)  main.o cjson.o -o main -lm
cjson.o:cjson.c
	$(CC) $(CFLAGS) -lm  -c cjson.c -o cjson.o
clean:
	rm -rf *.o
