all: rand.o
	gcc -o test rand.c

rand.o: rand.c
	gcc -c rand.c

run:
	./test

clear:
	rm *.o
