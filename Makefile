all: main

main:
		gcc -std=c99 -o main main.c -pthread -Wall

clean:
		rm main
