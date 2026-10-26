CC       = gcc
CFLAGS   = -std=c11 -Wall -Wextra -Wpedantic -g
TFLAGS   = -DMAT_TEST_ALLOC
VALGRIND = valgrind --leak-check=full

HDRS = matrice.h matrice_alloc.h matrice_io.h matrice_calcul.h

all: demo_matrices test_ex1 test_ex2 test_ex3

demo_matrices: main.o matrice.o matrice_alloc.o matrice_io.o matrice_calcul.o
	$(CC) $(CFLAGS) main.o matrice.o matrice_alloc.o matrice_io.o matrice_calcul.o -o demo_matrices

test_ex1: test_ex1.test.o matrice.test.o matrice_alloc.test.o
	$(CC) $(CFLAGS) test_ex1.test.o matrice.test.o matrice_alloc.test.o -o test_ex1

test_ex2: test_ex2.test.o matrice.test.o matrice_alloc.test.o matrice_io.test.o
	$(CC) $(CFLAGS) test_ex2.test.o matrice.test.o matrice_alloc.test.o matrice_io.test.o -o test_ex2

test_ex3: test_ex3.test.o matrice.test.o matrice_alloc.test.o matrice_calcul.test.o
	$(CC) $(CFLAGS) test_ex3.test.o matrice.test.o matrice_alloc.test.o matrice_calcul.test.o -o test_ex3

main.o: main.c $(HDRS)
	$(CC) $(CFLAGS) -c main.c

matrice.o: matrice.c $(HDRS)
	$(CC) $(CFLAGS) -c matrice.c

matrice_alloc.o: matrice_alloc.c $(HDRS)
	$(CC) $(CFLAGS) -c matrice_alloc.c

matrice_io.o: matrice_io.c $(HDRS)
	$(CC) $(CFLAGS) -c matrice_io.c

matrice_calcul.o: matrice_calcul.c $(HDRS)
	$(CC) $(CFLAGS) -c matrice_calcul.c

test_ex1.test.o: test_ex1.c $(HDRS)
	$(CC) $(CFLAGS) $(TFLAGS) -c test_ex1.c -o test_ex1.test.o

test_ex2.test.o: test_ex2.c $(HDRS)
	$(CC) $(CFLAGS) $(TFLAGS) -c test_ex2.c -o test_ex2.test.o

test_ex3.test.o: test_ex3.c $(HDRS)
	$(CC) $(CFLAGS) $(TFLAGS) -c test_ex3.c -o test_ex3.test.o

matrice.test.o: matrice.c $(HDRS)
	$(CC) $(CFLAGS) $(TFLAGS) -c matrice.c -o matrice.test.o

matrice_alloc.test.o: matrice_alloc.c $(HDRS)
	$(CC) $(CFLAGS) $(TFLAGS) -c matrice_alloc.c -o matrice_alloc.test.o

matrice_io.test.o: matrice_io.c $(HDRS)
	$(CC) $(CFLAGS) $(TFLAGS) -c matrice_io.c -o matrice_io.test.o

matrice_calcul.test.o: matrice_calcul.c $(HDRS)
	$(CC) $(CFLAGS) $(TFLAGS) -c matrice_calcul.c -o matrice_calcul.test.o

test: test_ex1 test_ex2 test_ex3
	./test_ex1
	./test_ex2
	./test_ex3

valgrind: test_ex1 test_ex2 test_ex3
	$(VALGRIND) ./test_ex1
	$(VALGRIND) ./test_ex2
	$(VALGRIND) ./test_ex3

clean:
	rm -f *.o demo_matrices test_ex1 test_ex2 test_ex3 R.txt R2.txt resultat_add.txt test_ex2_sortie.txt

.PHONY: all test valgrind clean
