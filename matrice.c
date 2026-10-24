/*
 * matrice.c -- Fonctions utilitaires communes à tous les modules.
 *
 * Exercice 1.
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

    /*  étape 1.a (FAIT) : les cas MAT_ERR_DIMENSIONS et
     *       MAT_ERR_DEPASSEMENT, sur le même modèle que ci-dessus. */
    case MAT_ERR_DIMENSIONS:  return "dimensions incompatibles";
    case MAT_ERR_DEPASSEMENT: return "dépassement de capacité";

    default:                  break;
    }
    return "erreur inconnue";
}

int mat_est_valide(const Matrice *m)
{
    /*  étapes 1.b (FAIT) : renvoyer 1 si les QUATRE conditions suivantes
     *       sont vraies, 0 sinon :
     *         - m n'est pas NULL ;
     *         - m->coef n'est pas NULL ;
     *         - 1 <= m->nb_lignes <= MAT_DIM_MAX ;
     *         - 1 <= m->nb_colonnes <= MAT_DIM_MAX.
     *       Une seule instruction suffit :
     *         return m != NULL && m->coef != NULL && ... ;            */
    return m != NULL && m->coef != NULL && m->nb_lignes >= 1 && m->nb_lignes <= MAT_DIM_MAX && m->nb_colonnes >= 1 && m->nb_colonnes <= MAT_DIM_MAX;

}
