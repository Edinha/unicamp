all: *.c
	gcc *.c -Wall -pedantic -std=c99 -o lab

clean:
	rm -f lab
run: lab
	./lab