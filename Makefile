all: *.c
	gcc *.c -Wall -Wno-unused-result -Wno-newline-eof -pedantic -std=c99 -o lab -O3

clean:
	rm -f lab
run: lab
	./lab
