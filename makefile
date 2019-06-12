CFLAGS = -Wall -pedantic -std=c99 -g

a2:	a2.c encryptDecrypt.o
	mpicc $(CFLAGS) -o a2 encryptDecrypt.o a2.c

encryptDecrypt.o:	encryptDecrypt.h encryptDecrypt.c
	mpicc $(CFLAGS) encryptDecrypt.c -o encryptDecrypt.o -c

run:
	mpiexec -n 2 ./a2

run2:
	mpiexec ./a2 -n 2

run3:
	mpiexec -n 4 ./a2

run4:
	mpiexec -n 5 ./a2

memory:
	valgrind --leak-check=yes --track-origins=yes ./a2

save:
	tar czf CIS3090A2moranski.tar.gz a2.c encryptDecrypt.h encryptDecrypt.c makefile README.txt

delete:
	rm -f *.gz