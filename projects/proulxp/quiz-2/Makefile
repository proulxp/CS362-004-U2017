CFLAGS = -Wall -fpic -coverage -lm

all: testme runTest

testme: testme.o
	gcc -g testme.o -o testme $(CFLAGS)

testme.o: testme.c
	gcc -c testme.c  $(CFLAGS)

runTest: testme
	./testme


clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out
