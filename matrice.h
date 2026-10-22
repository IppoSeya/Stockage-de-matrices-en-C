/*
 * matrice.h -- Type commun à tous les modules de la bibliothèque.
 *
 * Ce fichier définit :
 *   - le type Matrice (représentation "tableau de pointeurs de lignes") ;
 *   - la constante MATRICE_VIDE (état sûr d'une matrice sans mémoire) ;
 *   - les codes d'erreur MatErreur partagés par toutes les fonctions ;
 *   - deux fonctions utilitaires communes (implémentées dans matrice.c).
 */
#ifndef MATRICE_H
#define MATRICE_H

/* Dimension maximale acceptée (lignes ou colonnes). Cette borne protège
 * contre les fichiers aberrants et les demandes d'allocation démesurées. */
#define MAT_DIM_MAX 10000

typedef struct matrice {
    int **coef;       /* coef[i][j] : coefficient ligne i, colonne j      */
                      /* (indices à partir de 0) ; NULL si matrice vide   */
    int nb_lignes;    /* nombre de lignes   (0 si vide, sinon >= 1)       */
    int nb_colonnes;  /* nombre de colonnes (0 si vide, sinon >= 1)       */
} Matrice;

/* Matrice vide : aucune mémoire possédée. C'est l'état initial
 * recommandé de toute variable Matrice, et l'état après destruction. */
#define MATRICE_VIDE ((Matrice){ NULL, 0, 0 })

/* Codes de retour communs à toutes les fonctions qui peuvent échouer. */
typedef enum {
    MAT_OK = 0,           /* succès                                       */
    MAT_ERR_ARGUMENT,     /* paramètre invalide (pointeur NULL, ...)      */
    MAT_ERR_ALLOCATION,   /* échec de malloc/calloc                       */
    MAT_ERR_LECTURE,      /* erreur du flux pendant la lecture            */
    MAT_ERR_FORMAT,       /* contenu du fichier mal formé ou tronqué      */
    MAT_ERR_ECRITURE,     /* erreur du flux pendant l'écriture            */
    MAT_ERR_DIMENSIONS,   /* dimensions incompatibles pour l'opération    */
    MAT_ERR_DEPASSEMENT   /* résultat hors de l'intervalle des int        */
} MatErreur;

/* Renvoie un message lisible (chaîne statique) décrivant le code. */
const char *mat_message_erreur(MatErreur code);

/* Renvoie 1 si m désigne une matrice utilisable (non vide, dimensions
 * dans [1, MAT_DIM_MAX], tableau de lignes alloué), 0 sinon. */
int mat_est_valide(const Matrice *m);

#endif /* MATRICE_H */
