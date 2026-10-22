/*
 * matrice_alloc.c -- Création et destruction des matrices.
 *
 * FICHIER À COMPLÉTER (exercice 1, étapes 1.c à 1.f).
 *
 * Représentation : coef est un tableau de nb_lignes pointeurs ; chaque
 * coef[i] pointe vers un tableau de nb_colonnes int alloué séparément.
 */
#include <stdlib.h>
#include "matrice_alloc.h"

/* ------------------------------------------------------------------
 * FOURNI -- Ne pas modifier.
 * mat_calloc s'utilise exactement comme calloc. Compilé avec l'option
 * -DMAT_TEST_ALLOC, il permet aux programmes de test de simuler un
 * manque de mémoire.
 * ------------------------------------------------------------------ */
#ifdef MAT_TEST_ALLOC
int mat_test_allocs_autorisees = -1;

static void *mat_calloc(size_t nb, size_t taille)
{
    if (mat_test_allocs_autorisees == 0)
        return NULL;                       /* échec simulé */
    if (mat_test_allocs_autorisees > 0)
        mat_test_allocs_autorisees--;
    return calloc(nb, taille);
}
#else
#define mat_calloc calloc
#endif

MatErreur mat_allouer(Matrice *res, int nb_lignes, int nb_colonnes)
{
    /* FOURNI : on vérifie res, puis on le met à l'état vide (règle R3). */
    if (res == NULL)
        return MAT_ERR_ARGUMENT;
    *res = MATRICE_VIDE;

    /* (1.c) À COMPLÉTER : si nb_lignes ou nb_colonnes n'est pas compris
     *       entre 1 et MAT_DIM_MAX, renvoyer MAT_ERR_ARGUMENT.          */


    /* FOURNI : tableau des nb_lignes pointeurs de lignes (tous à NULL). */
    int **coef = mat_calloc((size_t)nb_lignes, sizeof *coef);
    if (coef == NULL)
        return MAT_ERR_ALLOCATION;

    /* (1.d) À COMPLÉTER : allouer chaque ligne.
     *   for (int i = 0; i < nb_lignes; i++) {
     *       coef[i] = mat_calloc(..., ...);    // nb_colonnes entiers
     *       if (coef[i] == NULL) {
     *           for (int k = i - 1; k >= 0; k--)  // lignes déjà
     *               free(coef[k]);                // obtenues
     *           free(coef);                       // puis le tableau
     *           return MAT_ERR_ALLOCATION;
     *       }
     *   }                                                             */

    (void)nb_colonnes;   /* ligne provisoire : à supprimer en (1.d) */

    /* (1.e) À COMPLÉTER : maintenant que tout a réussi, remplir *res
     *       (trois affectations : coef, nb_lignes, nb_colonnes)
     *       et renvoyer MAT_OK.                                        */

    free(coef);                  /* ligne provisoire : à supprimer en (1.e) */
    return MAT_ERR_LECTURE;      /* ligne provisoire : à remplacer en (1.e) */
}

void mat_detruire(Matrice *m)
{
    if (m == NULL)                 /* FOURNI */
        return;

    /* (1.f) À COMPLÉTER : si m->coef n'est pas NULL :
     *         - libérer chaque ligne m->coef[i], i de 0 à nb_lignes - 1 ;
     *         - PUIS libérer le tableau m->coef lui-même.              */


    *m = MATRICE_VIDE;   /* FOURNI : état sûr après destruction (R6) */
}
