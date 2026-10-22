/*
 * matrice.c -- Fonctions utilitaires communes à tous les modules.
 *
 * FICHIER À COMPLÉTER (exercice 1, étapes 1.a et 1.b).
 */
#include <stddef.h>
#include "matrice.h"

const char *mat_message_erreur(MatErreur code)
{
    switch (code) {
    case MAT_OK:              return "succès";
    case MAT_ERR_ARGUMENT:    return "argument invalide";
    case MAT_ERR_ALLOCATION:  return "mémoire insuffisante";
    case MAT_ERR_LECTURE:     return "erreur de lecture du fichier";
    case MAT_ERR_FORMAT:      return "fichier mal formé";
    case MAT_ERR_ECRITURE:    return "erreur d'écriture du fichier";

    /* (1.a) À COMPLÉTER : les cas MAT_ERR_DIMENSIONS et
     *       MAT_ERR_DEPASSEMENT, sur le même modèle que ci-dessus. */

    default:                  break;
    }
    return "erreur inconnue";
}

int mat_est_valide(const Matrice *m)
{
    /* (1.b) À COMPLÉTER : renvoyer 1 si les QUATRE conditions suivantes
     *       sont vraies, 0 sinon :
     *         - m n'est pas NULL ;
     *         - m->coef n'est pas NULL ;
     *         - 1 <= m->nb_lignes <= MAT_DIM_MAX ;
     *         - 1 <= m->nb_colonnes <= MAT_DIM_MAX.
     *       Une seule instruction suffit :
     *         return m != NULL && m->coef != NULL && ... ;            */

    (void)m;      /* ligne provisoire : à supprimer en (1.b) */
    return 0;     /* ligne provisoire : à remplacer en (1.b) */
}
