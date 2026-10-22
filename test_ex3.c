/*
 * test_ex3.c -- Tests de l'exercice 3 (module matrice_calcul).
 *
 * FICHIER FOURNI -- Ne pas modifier.
 * L'exercice 1 doit être terminé.
 *
 * Compilation :
 *   gcc -std=c11 -Wall -Wextra -Wpedantic -g -DMAT_TEST_ALLOC \
 *       test_ex3.c matrice.c matrice_alloc.c matrice_calcul.c -o test_ex3
 * Exécution :
 *   ./test_ex3
 */
#include <limits.h>
#include <stdio.h>
#include "matrice.h"
#include "matrice_alloc.h"
#include "matrice_calcul.h"

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

/* Crée une matrice n x p à partir d'un tableau de valeurs (ligne par
 * ligne). Renvoie MATRICE_VIDE si l'allocation échoue. */
static Matrice creer(int n, int p, const int *valeurs)
{
    Matrice m = MATRICE_VIDE;
    if (mat_allouer(&m, n, p) != MAT_OK)
        return MATRICE_VIDE;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            m.coef[i][j] = valeurs[i * p + j];
    return m;
}

/* Vrai si m est n x p et contient les valeurs données. */
static int contient(const Matrice *m, int n, int p, const int *valeurs)
{
    if (m->coef == NULL || m->nb_lignes != n || m->nb_colonnes != p)
        return 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            if (m->coef[i][j] != valeurs[i * p + j])
                return 0;
    return 1;
}

int main(void)
{
    const int va[] = { 1, 2, 3, 4, 5, 6 };          /* 2 x 3 */
    const int vb[] = { 10, 20, 30, 40, 50, 60 };    /* 2 x 3 */
    const int vs[] = { 11, 22, 33, 44, 55, 66 };    /* a + b */
    const int vc[] = { 7, 8, 9, 10, 11, 12 };       /* 3 x 2 */
    const int vp[] = { 58, 64, 139, 154 };          /* a x c */

    Matrice a = creer(2, 3, va), b = creer(2, 3, vb), c = creer(3, 2, vc);
    if (a.coef == NULL || b.coef == NULL || c.coef == NULL) {
        printf("mat_allouer echoue : terminez d'abord l'exercice 1.\n");
        mat_detruire(&a); mat_detruire(&b); mat_detruire(&c);
        return 1;
    }
    Matrice r = MATRICE_VIDE;

    printf("=== Exercice 3 : addition ===\n");
    verifier(mat_additionner(&a, &c, &r) == MAT_ERR_DIMENSIONS
             && est_vide(&r),
             "(3.a) (2 x 3) + (3 x 2) : MAT_ERR_DIMENSIONS");
    verifier(mat_additionner(&a, &b, &r) == MAT_OK,
             "(3.d) (2 x 3) + (2 x 3) : MAT_OK");
    verifier(contient(&r, 2, 3, vs), "(3.c) a + b est correct");
    verifier(contient(&a, 2, 3, va) && contient(&b, 2, 3, vb),
             "a et b n'ont pas ete modifiees");
    verifier(r.coef != a.coef && r.coef != b.coef,
             "(3.b) le resultat possede sa propre memoire");
    mat_detruire(&r);

    const int vmax[] = { INT_MAX }, vun[] = { 1 };
    Matrice x = creer(1, 1, vmax), y = creer(1, 1, vun);
    verifier(mat_additionner(&x, &y, &r) == MAT_ERR_DEPASSEMENT
             && est_vide(&r),
             "(3.c) INT_MAX + 1 : MAT_ERR_DEPASSEMENT");
    mat_detruire(&x);
    mat_detruire(&y);

    printf("=== Exercice 3 : multiplication ===\n");
    verifier(mat_multiplier(&a, &b, &r) == MAT_ERR_DIMENSIONS
             && est_vide(&r),
             "(3.e) (2 x 3) x (2 x 3) : MAT_ERR_DIMENSIONS");
    verifier(mat_multiplier(&a, &c, &r) == MAT_OK,
             "(3.h) (2 x 3) x (3 x 2) : MAT_OK");
    verifier(contient(&r, 2, 2, vp), "(3.g) a x c = (58 64 / 139 154)");
    mat_detruire(&r);
    verifier(mat_multiplier(&c, &a, &r) == MAT_OK
             && r.coef != NULL && r.nb_lignes == 3 && r.nb_colonnes == 3,
             "(3.f) (3 x 2) x (2 x 3) donne une matrice 3 x 3");
    mat_detruire(&r);
    verifier(contient(&a, 2, 3, va) && contient(&c, 3, 2, vc),
             "a et c n'ont pas ete modifiees");

    const int vg[] = { 100000, 100000 };
    Matrice l = creer(1, 2, vg), col = creer(2, 1, vg);
    verifier(mat_multiplier(&l, &col, &r) == MAT_ERR_DEPASSEMENT
             && est_vide(&r),
             "(3.g) 2 x 10^10 depasse INT_MAX : MAT_ERR_DEPASSEMENT");
    mat_detruire(&l);
    mat_detruire(&col);

    printf("=== Exercice 3 : cas particuliers ===\n");
    verifier(mat_additionner(&a, &b, &a) == MAT_ERR_ARGUMENT
             && contient(&a, 2, 3, va),
             "resultat = entree refuse, a reste intacte");
    int propre = 1;
    for (int k = 0; k <= 2; k++) {              /* 2 x 2 : 3 allocations */
        mat_test_allocs_autorisees = k;
        if (mat_multiplier(&a, &c, &r) != MAT_ERR_ALLOCATION || !est_vide(&r))
            propre = 0;
        mat_detruire(&r);
    }
    mat_test_allocs_autorisees = -1;
    verifier(propre, "(3.f) echec d'allocation : MAT_ERR_ALLOCATION, r vide");

    mat_detruire(&a);
    mat_detruire(&b);
    mat_detruire(&c);
    printf("\nBilan : %d / %d verifications reussies.\n", nb_ok, nb_total);
    if (nb_ok == nb_total)
        printf("Pensez a verifier l'absence de fuite : "
               "valgrind --leak-check=full ./test_ex3\n");
    return nb_ok == nb_total ? 0 : 1;
}
