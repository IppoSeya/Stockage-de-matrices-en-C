/*
 * test_ex2.c -- Tests de l'exercice 2 (module matrice_io).
 *
 * FICHIER FOURNI -- Ne pas modifier.
 * L'exercice 1 doit être terminé.
 *
 * Compilation :
 *   gcc -std=c11 -Wall -Wextra -Wpedantic -g -DMAT_TEST_ALLOC \
 *       test_ex2.c matrice.c matrice_alloc.c matrice_io.c -o test_ex2
 * Exécution (depuis le dossier qui contient test_ex2) :
 *   ./test_ex2
 * Le programme crée le fichier test_ex2_sortie.txt.
 */
#include <stdio.h>
#include <string.h>
#include "matrice.h"
#include "matrice_alloc.h"
#include "matrice_io.h"

static int nb_ok = 0, nb_total = 0;

static void verifier(int condition, const char *description)
{
    nb_total++;
    if (condition)
        nb_ok++;
    printf("%s %s\n", condition ? "[OK]   " : "[ECHEC]", description);
}

static int est_vide(const Matrice *m)
{
    return m->coef == NULL && m->nb_lignes == 0 && m->nb_colonnes == 0;
}

/* Vrai si x et y ont les mêmes dimensions et les mêmes coefficients. */
static int egales(const Matrice *x, const Matrice *y)
{
    if (x->coef == NULL || y->coef == NULL
        || x->nb_lignes != y->nb_lignes || x->nb_colonnes != y->nb_colonnes)
        return 0;
    for (int i = 0; i < x->nb_lignes; i++)
        for (int j = 0; j < x->nb_colonnes; j++)
            if (x->coef[i][j] != y->coef[i][j])
                return 0;
    return 1;
}

/* Lit une matrice depuis un texte, via un fichier temporaire. */
static MatErreur lire_texte(const char *texte, Matrice *m)
{
    FILE *f = tmpfile();
    if (f == NULL)
        return MAT_ERR_LECTURE;
    fputs(texte, f);
    rewind(f);
    MatErreur err = mat_lire(f, m);
    fclose(f);
    return err;
}

int main(void)
{
    const char *nom = "test_ex2_sortie.txt";

    printf("=== Exercice 2 : affichage (verification visuelle) ===\n");
    Matrice m = MATRICE_VIDE;
    if (mat_allouer(&m, 4, 3) != MAT_OK) {
        printf("mat_allouer echoue : terminez d'abord l'exercice 1.\n");
        return 1;
    }
    for (int i = 0; i < 4; i++)                  /* 1, 2, 3, ..., 12 */
        for (int j = 0; j < 3; j++)
            m.coef[i][j] = 3 * i + j + 1;
    mat_afficher("M", &m);
    printf("(2.a) Vous devez voir ci-dessus 4 lignes : 1 2 3 / 4 5 6 / "
           "7 8 9 / 10 11 12\n");

    printf("=== Exercice 2 : ecriture ===\n");
    FILE *f = fopen(nom, "w");
    verifier(f != NULL, "ouverture de test_ex2_sortie.txt en ecriture");
    if (f != NULL) {
        verifier(mat_ecrire(f, &m) == MAT_OK,
                 "(2.b) mat_ecrire renvoie MAT_OK");
        fclose(f);
    }
    char texte[128] = "";
    f = fopen(nom, "r");
    if (f != NULL) {
        size_t n = fread(texte, 1, sizeof texte - 1, f);
        texte[n] = '\0';
        fclose(f);
    }
    verifier(strcmp(texte, "4 3\n1 2 3\n4 5 6\n7 8 9\n10 11 12\n") == 0,
             "(2.b) le fichier contient exactement le format attendu");
    Matrice vide = MATRICE_VIDE;
    verifier(mat_ecrire(stdout, &vide) == MAT_ERR_ARGUMENT,
             "(2.b) mat_ecrire refuse une matrice vide");

    printf("=== Exercice 2 : relecture ===\n");
    Matrice relue = MATRICE_VIDE;
    f = fopen(nom, "r");
    if (f != NULL) {
        verifier(mat_lire(f, &relue) == MAT_OK,
                 "(2.f) mat_lire relit le fichier : MAT_OK");
        fclose(f);
    } else {
        verifier(0, "(2.f) mat_lire relit le fichier : MAT_OK");
    }
    verifier(egales(&m, &relue), "(2.e) la matrice relue est identique");
    mat_detruire(&relue);

    Matrice a = MATRICE_VIDE;
    verifier(lire_texte("2  3\n  1 -2\t3\n4 5\n   6\n", &a) == MAT_OK
             && a.coef != NULL && a.nb_lignes == 2 && a.nb_colonnes == 3
             && a.coef[0][1] == -2 && a.coef[1][2] == 6,
             "(2.e) espaces et sauts de ligne en trop sont toleres");
    mat_detruire(&a);

    printf("=== Exercice 2 : fichiers incorrects ===\n");
    struct { const char *texte; const char *description; } cas[] = {
        { "",                    "(2.c) fichier vide" },
        { "0 3\n",               "(2.c) dimension nulle" },
        { "-2 3\n1 2 3\n",       "(2.c) dimension negative" },
        { "2 2\n1 2 3\n",        "(2.e) coefficient manquant" },
        { "2 2\n1 x 3 4\n",      "(2.e) donnee non numerique" },
        { "1 2\n1 99999999999\n", "(2.e) entier trop grand pour un int" },
    };
    for (size_t k = 0; k < sizeof cas / sizeof cas[0]; k++) {
        Matrice t = MATRICE_VIDE;
        MatErreur err = lire_texte(cas[k].texte, &t);
        verifier(err == MAT_ERR_FORMAT && est_vide(&t), cas[k].description);
        mat_detruire(&t);
    }

    printf("=== Exercice 2 : echec d'allocation simule ===\n");
    int propre = 1;
    for (int k = 0; k <= 2; k++) {               /* 2 x 2 : 3 allocations */
        mat_test_allocs_autorisees = k;
        Matrice t = MATRICE_VIDE;
        if (lire_texte("2 2\n1 2\n3 4\n", &t) != MAT_ERR_ALLOCATION
            || !est_vide(&t))
            propre = 0;
        mat_detruire(&t);
    }
    mat_test_allocs_autorisees = -1;
    verifier(propre, "(2.d) mat_lire renvoie MAT_ERR_ALLOCATION proprement");

    mat_detruire(&m);
    printf("\nBilan : %d / %d verifications reussies.\n", nb_ok, nb_total);
    if (nb_ok == nb_total)
        printf("Pensez a verifier l'absence de fuite : "
               "valgrind --leak-check=full ./test_ex2\n");
    return nb_ok == nb_total ? 0 : 1;
}
