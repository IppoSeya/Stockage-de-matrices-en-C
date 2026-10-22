/*
 * matrice_calcul.c -- Opérations arithmétiques sur les matrices.
 *
 * FICHIER À COMPLÉTER (exercice 3, étapes 3.a à 3.g).
 */
#include <limits.h>
#include <stddef.h>
#include "matrice_calcul.h"
#include "matrice_alloc.h"

/* ------------------------------------------------------------------
 * FOURNI -- Contrôles communs aux deux opérations.
 * Refuse res NULL ou égal à une entrée (sans rien modifier), met *res
 * à l'état vide, puis vérifie que a et b sont valides.
 * ------------------------------------------------------------------ */
static MatErreur verifier_parametres(const Matrice *a, const Matrice *b,
                                     Matrice *res)
{
    if (res == NULL || res == a || res == b)
        return MAT_ERR_ARGUMENT;
    *res = MATRICE_VIDE;
    if (!mat_est_valide(a) || !mat_est_valide(b))
        return MAT_ERR_ARGUMENT;
    return MAT_OK;
}

/* FOURNI -- Un résultat calculé en long long tient-il dans un int ? */
static int tient_dans_int(long long v)
{
    return v >= INT_MIN && v <= INT_MAX;
}

MatErreur mat_additionner(const Matrice *a, const Matrice *b,
                          Matrice *res)
{
    MatErreur err = verifier_parametres(a, b, res);      /* FOURNI */
    if (err != MAT_OK)
        return err;

    /* (3.a) À COMPLÉTER : si a et b n'ont pas le même nombre de lignes
     *       OU pas le même nombre de colonnes,
     *       renvoyer MAT_ERR_DIMENSIONS.                              */


    /* (3.b) À COMPLÉTER : allouer r avec les dimensions de a ;
     *         err = mat_allouer(&r, ..., ...);
     *         if (err != MAT_OK) return err;                          */
    Matrice r = MATRICE_VIDE;


    /* FOURNI : parcours de tous les coefficients de r. */
    for (int i = 0; i < r.nb_lignes; i++) {
        for (int j = 0; j < r.nb_colonnes; j++) {
            /* (3.c) À COMPLÉTER : calculer la somme des coefficients
             *       (i, j) de a et de b EN long long :
             *         long long s = (long long)a->coef[i][j] + ... ;  */
            long long s = 0;   /* ligne provisoire : à remplacer en (3.c) */

            if (!tient_dans_int(s)) {                    /* FOURNI */
                mat_detruire(&r);
                return MAT_ERR_DEPASSEMENT;
            }
            r.coef[i][j] = (int)s;
        }
    }

    /* (3.d) À COMPLÉTER : transférer le résultat :
     *         *res = r;  return MAT_OK;                               */
    mat_detruire(&r);            /* ligne provisoire : à supprimer en (3.d) */
    return MAT_ERR_LECTURE;      /* ligne provisoire : à remplacer en (3.d) */
}

MatErreur mat_multiplier(const Matrice *a, const Matrice *b,
                         Matrice *res)
{
    MatErreur err = verifier_parametres(a, b, res);      /* FOURNI */
    if (err != MAT_OK)
        return err;

    /* (3.e) À COMPLÉTER : le produit a x b n'existe que si le nombre de
     *       COLONNES de a est égal au nombre de LIGNES de b.
     *       Sinon, renvoyer MAT_ERR_DIMENSIONS.                       */


    /* (3.f) À COMPLÉTER : allouer r de dimensions
     *       (lignes de a) x (colonnes de b).                          */
    Matrice r = MATRICE_VIDE;


    for (int i = 0; i < r.nb_lignes; i++) {              /* FOURNI */
        for (int j = 0; j < r.nb_colonnes; j++) {
            long long s = 0;

            /* (3.g) À COMPLÉTER : boucle sur k, de 0 à a->nb_colonnes - 1,
             *       qui ajoute à s le produit a(i,k) x b(k,j) :
             *
             *   for (int k = 0; k < a->nb_colonnes; k++) {
             *       long long p = (long long)a->coef[i][k] * b->coef[k][j];
             *       if ((p > 0 && s > LLONG_MAX - p)
             *           || (p < 0 && s < LLONG_MIN - p)) {
             *           mat_detruire(&r);
             *           return MAT_ERR_DEPASSEMENT;
             *       }
             *       s += p;
             *   }                                                     */

            if (!tient_dans_int(s)) {                    /* FOURNI */
                mat_detruire(&r);
                return MAT_ERR_DEPASSEMENT;
            }
            r.coef[i][j] = (int)s;
        }
    }

    /* (3.h) À COMPLÉTER : *res = r;  return MAT_OK;                    */
    mat_detruire(&r);            /* ligne provisoire : à supprimer en (3.h) */
    return MAT_ERR_LECTURE;      /* ligne provisoire : à remplacer en (3.h) */
}
