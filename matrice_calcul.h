/*
 * matrice_calcul.h -- Opérations arithmétiques sur les matrices.
 *
 * Règles communes aux deux fonctions :
 *   - a et b ne sont jamais modifiées (paramètres const) ;
 *   - res est un paramètre de SORTIE : son contenu antérieur est ignoré
 *     et écrasé ; s'il possédait de la mémoire, l'appelant doit l'avoir
 *     libérée avant l'appel ;
 *   - res doit être distinct de a et de b (sinon MAT_ERR_ARGUMENT, et
 *     rien n'est modifié) ;
 *   - en cas de succès, *res possède sa propre mémoire (mat_detruire) ;
 *   - en cas d'échec, *res == MATRICE_VIDE (si res != NULL), aucune fuite.
 */
#ifndef MATRICE_CALCUL_H
#define MATRICE_CALCUL_H

#include "matrice.h"

/*
 * res = a + b.
 *   Condition : mêmes dimensions (a et b de taille n x p) ; res : n x p.
 *   Erreurs : MAT_ERR_ARGUMENT, MAT_ERR_DIMENSIONS, MAT_ERR_ALLOCATION,
 *             MAT_ERR_DEPASSEMENT.
 */
MatErreur mat_additionner(const Matrice *a, const Matrice *b,
                          Matrice *res);

/*
 * res = a x b (produit matriciel).
 *   Condition : a de taille n x p, b de taille p x q ; res : n x q.
 *   Erreurs : MAT_ERR_ARGUMENT, MAT_ERR_DIMENSIONS, MAT_ERR_ALLOCATION,
 *             MAT_ERR_DEPASSEMENT.
 */
MatErreur mat_multiplier(const Matrice *a, const Matrice *b,
                         Matrice *res);

#endif /* MATRICE_CALCUL_H */
