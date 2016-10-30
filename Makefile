all: *.c
	gcc *.c -Wall -Wno-newline-eof -pedantic -std=c99 -o lab

clean:
	rm -f lab
run: lab
	./lab
