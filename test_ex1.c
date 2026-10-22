/*
 * test_ex1.c -- Tests de l'exercice 1 (modules matrice et matrice_alloc).
 *
 * FICHIER FOURNI -- Ne pas modifier.
 *
 * Compilation :
 *   gcc -std=c11 -Wall -Wextra -Wpedantic -g -DMAT_TEST_ALLOC \
 *       test_ex1.c matrice.c matrice_alloc.c -o test_ex1
 * Exécution :
 *   ./test_ex1
 */
#include <stdio.h>
#include <string.h>
#include "matrice.h"
#include "matrice_alloc.h"

static int nb_ok = 0, nb_total = 0;

/* Affiche [OK] ou [ECHEC] suivi de la description du test. */
static void verifier(int condition, const char *description)
{
    nb_total++;
    if (condition)
        nb_ok++;
    printf("%s %s\n", condition ? "[OK]   " : "[ECHEC]", description);
}

/* Vrai si m est exactement MATRICE_VIDE. */
static int est_vide(const Matrice *m)
{
    return m->coef == NULL && m->nb_lignes == 0 && m->nb_colonnes == 0;
}

int main(void)
{
    printf("=== Exercice 1 : matrice.c ===\n");
    verifier(strcmp(mat_message_erreur(MAT_ERR_DIMENSIONS),
                    "erreur inconnue") != 0,
             "(1.a) message pour MAT_ERR_DIMENSIONS");
    verifier(strcmp(mat_message_erreur(MAT_ERR_DEPASSEMENT),
                    "erreur inconnue") != 0,
             "(1.a) message pour MAT_ERR_DEPASSEMENT");

    int ligne[2] = { 0, 0 };
    int *lignes[1] = { ligne };
    Matrice ok = { lignes, 1, 2 };            /* matrice 1 x 2 valide */
    Matrice vide = MATRICE_VIDE;
    Matrice zero = { lignes, 0, 2 };          /* 0 ligne : invalide */
    verifier(mat_est_valide(&ok) == 1, "(1.b) une matrice 1 x 2 est valide");
    verifier(mat_est_valide(NULL) == 0, "(1.b) NULL n'est pas valide");
    verifier(mat_est_valide(&vide) == 0,
             "(1.b) MATRICE_VIDE n'est pas valide");
    verifier(mat_est_valide(&zero) == 0,
             "(1.b) une matrice de 0 ligne n'est pas valide");

    printf("=== Exercice 1 : matrice_alloc.c ===\n");
    Matrice m = MATRICE_VIDE;
    verifier(mat_allouer(&m, 0, 4) == MAT_ERR_ARGUMENT && est_vide(&m),
             "(1.c) mat_allouer refuse 0 ligne");
    verifier(mat_allouer(&m, 3, -2) == MAT_ERR_ARGUMENT && est_vide(&m),
             "(1.c) mat_allouer refuse -2 colonnes");
    verifier(mat_allouer(&m, MAT_DIM_MAX + 1, 2) == MAT_ERR_ARGUMENT,
             "(1.c) mat_allouer refuse une dimension > MAT_DIM_MAX");

    MatErreur err = mat_allouer(&m, 3, 4);
    verifier(err == MAT_OK, "(1.e) mat_allouer(&m, 3, 4) renvoie MAT_OK");
    int bonnes_dimensions = (m.coef != NULL && m.nb_lignes == 3
                             && m.nb_colonnes == 4);
    verifier(bonnes_dimensions, "(1.e) m a 3 lignes et 4 colonnes");
    if (err == MAT_OK && bonnes_dimensions) {
        int zeros = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++) {
                if (m.coef[i] == NULL || m.coef[i][j] != 0)
                    zeros = 0;
                else
                    m.coef[i][j] = 10 * i + j;   /* on peut écrire */
            }
        verifier(zeros, "(1.d) tous les coefficients valent 0");
    } else {
        verifier(0, "(1.d) tous les coefficients valent 0");
    }

    mat_detruire(&m);
    verifier(est_vide(&m), "(1.f) apres mat_detruire, m est vide");
    mat_detruire(&m);
    verifier(est_vide(&m), "(1.f) un second mat_detruire est sans danger");
    mat_detruire(NULL);
    verifier(1, "(1.f) mat_detruire(NULL) ne plante pas");

    printf("=== Exercice 1 : echecs d'allocation simules ===\n");
    /* Une matrice 3 x 5 demande 4 allocations (1 tableau + 3 lignes).
     * On fait échouer la 1re, puis la 2e, la 3e et la 4e. */
    int tous_propres = 1;
    for (int k = 0; k <= 3; k++) {
        mat_test_allocs_autorisees = k;
        Matrice t = MATRICE_VIDE;
        if (mat_allouer(&t, 3, 5) != MAT_ERR_ALLOCATION || !est_vide(&t))
            tous_propres = 0;
    }
    mat_test_allocs_autorisees = -1;
    verifier(tous_propres,
             "(1.d) chaque echec renvoie MAT_ERR_ALLOCATION et laisse *res vide");

    printf("\nBilan : %d / %d verifications reussies.\n", nb_ok, nb_total);
    if (nb_ok == nb_total)
        printf("Pensez a verifier l'absence de fuite : "
               "valgrind --leak-check=full ./test_ex1\n");
    return nb_ok == nb_total ? 0 : 1;
}
