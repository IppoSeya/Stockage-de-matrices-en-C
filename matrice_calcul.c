/*
 * matrice_calcul.c -- Opérations arithmétiques sur les matrices.
 *
 * Exercice 3, étapes 3.a à 3.g.
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

    /* étape 3.a (FAIT) : si a et b n'ont pas le même nombre de lignes
     *       OU pas le même nombre de colonnes,
     *       renvoyer MAT_ERR_DIMENSIONS.                              */
    if ((a->nb_lignes != b->nb_lignes) || (a->nb_colonnes != b->nb_colonnes))
        return MAT_ERR_DIMENSIONS;

    /* étape 3.b (FAIT) : allouer r avec les dimensions de a ;
     *         err = mat_allouer(&r, ..., ...);
     *         if (err != MAT_OK) return err;                          */

    Matrice r = MATRICE_VIDE;

    err = mat_allouer(&r, a->nb_lignes, a->nb_colonnes);
    if (err != MAT_OK)
        return err;



    /* FOURNI : parcours de tous les coefficients de r. */
    for (int i = 0; i < r.nb_lignes; i++) {
        for (int j = 0; j < r.nb_colonnes; j++) {
            /* étape 3.c (FAIT) : calculer la somme des coefficients
             *       (i, j) de a et de b EN long long :
             *         long long s = (long long)a->coef[i][j] + ... ;  */
            long long  s = (long long)a->coef[i][j] + b->coef[i][j];

            if (!tient_dans_int(s)) {                    /* FOURNI */
                mat_detruire(&r);
                return MAT_ERR_DEPASSEMENT;
            }
            r.coef[i][j] = (int)s;
        }
    }

    /* étape 3.d (FAIT) : transférer le résultat :
     *         *res = r;  return MAT_OK;                               */
    *res = r;
    return MAT_OK;
}

MatErreur mat_multiplier(const Matrice *a, const Matrice *b,
                         Matrice *res)
{
    MatErreur err = verifier_parametres(a, b, res);      /* FOURNI */
    if (err != MAT_OK)
        return err;

    /* étape 3.e (FAIT) : le produit a x b n'existe que si le nombre de
     *       COLONNES de a est égal au nombre de LIGNES de b.
     *       Sinon, renvoyer MAT_ERR_DIMENSIONS.                       */
    if (a->nb_colonnes != b->nb_lignes)
	return MAT_ERR_DIMENSIONS;

    /* étape 3.f (FAIT) : allouer r de dimensions
     *       (lignes de a) x (colonnes de b).                          */

    Matrice r = MATRICE_VIDE;

    err = mat_allouer(&r, a->nb_lignes, b->nb_colonnes);
    if (err != MAT_OK)
	return err;


    for (int i = 0; i < r.nb_lignes; i++) {              /* FOURNI */
        for (int j = 0; j < r.nb_colonnes; j++) {
            long long s = 0;

            /* étape 3.g (FAIT) : boucle sur k, de 0 à a->nb_colonnes - 1,
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
	    for (int k = 0; k < a->nb_colonnes; k++) {
		long long p = (long long)a->coef[i][k] * b->coef[k][j];
		if ((p > 0 && s > LLONG_MAX - p) || (p < 0 && s < LLONG_MIN - p)) {
		    mat_detruire(&r);
		    return MAT_ERR_DEPASSEMENT;
                }
		s += p;
	    }

            if (!tient_dans_int(s)) {                    /* FOURNI */
                mat_detruire(&r);
                return MAT_ERR_DEPASSEMENT;
            }
            r.coef[i][j] = (int)s;
        }
    }

    /* étape 3.h (FAIT) : *res = r;  return MAT_OK;                    */
    *res = r;
    return MAT_OK;
}

