/*
 * matrice_alloc.h -- Création et destruction des matrices.
 */
#ifndef MATRICE_ALLOC_H
#define MATRICE_ALLOC_H

#include "matrice.h"

/*
 * Alloue une matrice nb_lignes x nb_colonnes dont tous les coefficients
 * valent 0.
 *   Préconditions : res != NULL ; 1 <= nb_lignes, nb_colonnes <= MAT_DIM_MAX.
 *   Succès (MAT_OK) : *res possède sa propre mémoire ; l'appelant devra
 *                     appeler mat_detruire(res).
 *   Échec           : *res == MATRICE_VIDE (si res != NULL), aucune fuite.
 *   Erreurs         : MAT_ERR_ARGUMENT, MAT_ERR_ALLOCATION.
 */
MatErreur mat_allouer(Matrice *res, int nb_lignes, int nb_colonnes);

/*
 * Libère toute la mémoire possédée par *m puis remet *m à MATRICE_VIDE.
 * Sans effet si m == NULL ou si *m est déjà vide : un second appel est
 * donc sans danger (pas de double libération).
 */
void mat_detruire(Matrice *m);

#ifdef MAT_TEST_ALLOC
/* Instrumentation réservée aux tests (compiler avec -DMAT_TEST_ALLOC) :
 * nombre d'allocations qui réussiront encore avant un échec simulé ;
 * -1 (valeur par défaut) désactive la simulation. */
extern int mat_test_allocs_autorisees;
#endif

#endif /* MATRICE_ALLOC_H */
