CC       = gcc
CFLAGS   = -std=c11 -Wall -Wextra -Wpedantic -g
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

EXEC = demo_matrices
TESTS = test_ex1 test_ex2 test_ex3

MODULES = matrice.c matrice_alloc.c matrice_io.c matrice_calcul.c
OBJS    = $(MODULES:.c=.o)
MAIN_OBJ = main.o

all: $(TESTS) $(EXEC)

$(EXEC): $(MAIN_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test_ex1: test_ex1.c matrice.c matrice_alloc.c
	$(CC) $(CFLAGS) -DMAT_TEST_ALLOC $^ -o $@

test_ex2: test_ex2.c matrice.c matrice_alloc.c matrice_io.c
	$(CC) $(CFLAGS) -DMAT_TEST_ALLOC $^ -o $@

test_ex3: test_ex3.c matrice.c matrice_alloc.c matrice_calcul.c
	$(CC) $(CFLAGS) -DMAT_TEST_ALLOC $^ -o $@

build_tests: $(TESTS)

test: $(TESTS)
	@echo "=== Execution de test_ex1 ==="
	./test_ex1
	@echo "\n=== Execution de test_ex2 ==="
	./test_ex2
	@echo "\n=== Execution de test_ex3 ==="
	./test_ex3

demo: $(EXEC)
	./$(EXEC) add donnees/A.txt donnees/B.txt R.txt

valgrind_ex1: test_ex1
	$(VALGRIND) ./test_ex1

valgrind_ex2: test_ex2
	$(VALGRIND) ./test_ex2

valgrind_ex3: test_ex3
	$(VALGRIND) ./test_ex3

valgrind_demo: $(EXEC)
	-$(VALGRIND) ./$(EXEC) add donnees/A.txt donnees/B.txt R.txt

valgrind_all: valgrind_ex1 valgrind_ex2 valgrind_ex3 valgrind_demo

clean:
	rm -f *.o

fclean: clean
	rm -f $(EXEC) $(TESTS) R.txt R2.txt resultat_add.txt test_ex2_sortie.txt

re: fclean all

.PHONY: all build_tests test demo valgrind_ex1 valgrind_ex2 valgrind_ex3 valgrind_demo valgrind_all clean fclean re
