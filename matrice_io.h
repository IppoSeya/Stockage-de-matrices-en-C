/*
 * matrice_io.h -- Lecture, écriture et affichage des matrices.
 *
 * Format texte d'une matrice :
 *   ligne 1          : <nb_lignes> <nb_colonnes>
 *   lignes suivantes : les nb_colonnes coefficients d'une ligne,
 *                      séparés par des espaces.
 *
 * Ces fonctions n'ouvrent ni ne ferment jamais de fichier : c'est le
 * code qui a appelé fopen qui doit appeler fclose.
 */
#ifndef MATRICE_IO_H
#define MATRICE_IO_H

#include <stdio.h>
#include "matrice.h"

/*
 * Lit une matrice depuis le flux f (ouvert en lecture).
 *   Préconditions : f != NULL, res != NULL.
 *   Succès : *res possède sa mémoire (à libérer avec mat_detruire) ;
 *            le flux est positionné juste après le dernier coefficient.
 *   Échec  : *res == MATRICE_VIDE (si res != NULL), aucune fuite.
 *   Erreurs : MAT_ERR_ARGUMENT, MAT_ERR_FORMAT, MAT_ERR_LECTURE,
 *             MAT_ERR_ALLOCATION.
 */
MatErreur mat_lire(FILE *f, Matrice *res);

/*
 * Écrit la matrice *m dans le flux f (ouvert en écriture) au format
 * ci-dessus. *m n'est pas modifiée.
 *   Erreurs : MAT_ERR_ARGUMENT (f NULL ou m invalide), MAT_ERR_ECRITURE.
 */
MatErreur mat_ecrire(FILE *f, const Matrice *m);

/*
 * Affiche *m sur la sortie standard, colonnes alignées, précédée de son
 * nom et de ses dimensions. Outil de mise au point : n'échoue jamais
 * (une matrice vide ou invalide est signalée comme telle).
 */
void mat_afficher(const char *nom, const Matrice *m);

#endif /* MATRICE_IO_H */
