# Makefile pour le projet "TD Stockage de matrices en C"
#
# REGLES PRINCIPALES :
#   make          : Compile l'executable principal demo_matrices.
#   make test     : Compile et lance les trois programmes de tests unitaires.
#   make valgrind : Execute Valgrind sur tous les tests et la demonstration
#                   pour verifier l'absence de fuites memoire.
#   make clean    : Supprime tous les fichiers objets, executables et fichiers
#                   de sortie temporaires.
#
# DETAILS TECHNIQUES :
#   - Compile avec les options C11, -Wall, -Wextra, -Wpedantic et -g (debug).
#   - Les cibles de test (test_ex1, test_ex2, test_ex3) incluent la macro
#     -DMAT_TEST_ALLOC necessaire pour simuler les echecs d'allocation.

CC       = gcc
CFLAGS   = -std=c11 -Wall -Wextra -Wpedantic -g
VALGRIND = valgrind --leak-check=full

EXEC  = demo_matrices
TESTS = test_ex1 test_ex2 test_ex3
OBJS  = matrice.o matrice_alloc.o matrice_io.o matrice_calcul.o main.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test_ex1: test_ex1.c matrice.c matrice_alloc.c
	$(CC) $(CFLAGS) -DMAT_TEST_ALLOC test_ex1.c matrice.c matrice_alloc.c -o test_ex1

test_ex2: test_ex2.c matrice.c matrice_alloc.c matrice_io.c
	$(CC) $(CFLAGS) -DMAT_TEST_ALLOC test_ex2.c matrice.c matrice_alloc.c matrice_io.c -o test_ex2

test_ex3: test_ex3.c matrice.c matrice_alloc.c matrice_calcul.c
	$(CC) $(CFLAGS) -DMAT_TEST_ALLOC test_ex3.c matrice.c matrice_alloc.c matrice_calcul.c -o test_ex3

test: $(TESTS)
	./test_ex1
	./test_ex2
	./test_ex3

valgrind: $(TESTS) $(EXEC)
	$(VALGRIND) ./test_ex1
	$(VALGRIND) ./test_ex2
	$(VALGRIND) ./test_ex3
	$(VALGRIND) ./$(EXEC) add donnees/A.txt donnees/B.txt R.txt

clean:
	rm -f *.o $(EXEC) $(TESTS) R.txt R2.txt resultat_add.txt test_ex2_sortie.txt[cite: 23, 36, 37]

.PHONY: all test valgrind clean 
