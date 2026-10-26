/*
 * matrice_io.c -- Lecture, écriture et affichage des matrices.
 *
 * FICHIER COMPLÉTÉ (exercice 2, étapes 2.a à 2.f).
 */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrice_io.h"
#include "matrice_alloc.h"

/* ------------------------------------------------------------------
 * FOURNI -- Ne pas modifier.
 * Lit le prochain entier du flux f et le range dans *val.
 * Renvoie MAT_OK, MAT_ERR_FORMAT (pas un entier, entier trop grand,
 * fin de fichier) ou MAT_ERR_LECTURE (erreur du flux).
 * ------------------------------------------------------------------ */
static MatErreur lire_entier(FILE *f, int *val)
{
    char mot[32];
    char *fin;

    if (fscanf(f, "%31s", mot) != 1)
        return ferror(f) ? MAT_ERR_LECTURE : MAT_ERR_FORMAT;

    errno = 0;
    long v = strtol(mot, &fin, 10);
    if (fin == mot || *fin != '\0' || errno == ERANGE
        || v < INT_MIN || v > INT_MAX)
        return MAT_ERR_FORMAT;

    *val = (int)v;
    return MAT_OK;
}

void mat_afficher(const char *nom, const Matrice *m)
{
    if (nom == NULL)                                     /* FOURNI */
        nom = "matrice";
    if (!mat_est_valide(m)) {
        printf("%s : matrice vide ou invalide\n", nom);
        return;
    }
    printf("%s (%d x %d) :\n", nom, m->nb_lignes, m->nb_colonnes);

    /* (2.a) FAIT : pour chaque ligne i, afficher chaque
     *       coefficient avec printf(" %8d", m->coef[i][j]),
     *       puis passer à la ligne avec putchar('\n').
     *
     *Affichage des coefficients: une ligne de la matrice par
     * ligne d'ecran, chaque coefficient sur 8 caracteres pour que les
     * colonnes de la matrices soit alignees.                     */

    for (int i = 0; i < m->nb_lignes; i++){
        for (int j = 0; j < m->nb_colonnes; j++)
            printf(" %8d", m->coef[i][j]);
        putchar('\n');
    }
}

MatErreur mat_ecrire(FILE *f, const Matrice *m)
{
    if (f == NULL || !mat_est_valide(m))                 /* FOURNI */
        return MAT_ERR_ARGUMENT;

    /* FOURNI : première ligne du fichier = les dimensions. */
    if (fprintf(f, "%d %d\n", m->nb_lignes, m->nb_colonnes) < 0)
        return MAT_ERR_ECRITURE;

     /* (2.b) FAIT : pour chaque ligne i de la matrice :
     *         - écrire les coefficients séparés par UN espace :
     *             le premier (j == 0) avec "%d", les autres avec " %d" ;
     *         - terminer la ligne avec fputc('\n', f) ;
     *         - si un fprintf renvoie un nombre < 0, ou si fputc
     *           renvoie EOF : return MAT_ERR_ECRITURE;
     *
     *       Écriture des coefficients au format canonique : un seul
     *       espace entre deux coefficients, aucun espace en fin de
     *       ligne, un saut de ligne après chaque ligne.
     *       Chaque écriture est vérifiée : fprintf renvoie une valeur
     *       négative en cas d'erreur, fputc renvoie EOF. */
    for (int i = 0; i < m->nb_lignes; i++) {
        for (int j = 0; j < m->nb_colonnes; j++) {
            /* j == 0 : pas d'espace devant le premier coefficient */
            if (fprintf(f, j == 0 ? "%d" : " %d", m->coef[i][j]) < 0)
                return MAT_ERR_ECRITURE;
        }
        if (fputc('\n', f) == EOF)     /* fin de la ligne i */
            return MAT_ERR_ECRITURE;
    }


    /* FOURNI : forcer l'écriture du tampon et détecter une erreur. */
    if (fflush(f) == EOF)
        return MAT_ERR_ECRITURE;
    return MAT_OK;
}

MatErreur mat_lire(FILE *f, Matrice *res)
{
    /* FOURNI : contrôle des paramètres, *res mis à l'état vide. */
    if (res == NULL)
        return MAT_ERR_ARGUMENT;
    *res = MATRICE_VIDE;
    if (f == NULL)
        return MAT_ERR_ARGUMENT;

    /* FOURNI : lecture des deux dimensions. */
    int nb_lignes = 0, nb_colonnes = 0;
    MatErreur err = lire_entier(f, &nb_lignes);
    if (err == MAT_OK)
        err = lire_entier(f, &nb_colonnes);
    if (err != MAT_OK)
        return err;

    /* (2.c) FAIT : si nb_lignes ou nb_colonnes n'est pas compris
     *       entre 1 et MAT_DIM_MAX, renvoyer MAT_ERR_FORMAT
     *       (c'est le contenu du fichier qui est faux).
     *       Contrôle des dimensions lues. Ce n'est pas un problème
     *       d'argument (f et res sont corrects) : c'est le contenu du
     *       fichier qui est faux, donc MAT_ERR_FORMAT. */
    if (nb_lignes < 1 || nb_lignes > MAT_DIM_MAX || nb_colonnes < 1 || nb_colonnes > MAT_DIM_MAX)
        return MAT_ERR_FORMAT;


    /* (2.d) FAIT : déclarer une matrice LOCALE et l'allouer :
     *         Matrice tmp;
     *         err = mat_allouer(&tmp, nb_lignes, nb_colonnes);
     *         if (err != MAT_OK) return err;
     *
     *       Matrice LOCALE : on remplit tmp et non *res, pour que
     *       l'appelant ne reçoive jamais une matrice à moitié remplie
     *       si une erreur survient au milieu du fichier (règle R3).
     *       Si mat_allouer échoue, elle a déjà tout libéré (tmp vide). */ 
    Matrice tmp;
    err = mat_allouer(&tmp, nb_lignes, nb_colonnes);
    if (err != MAT_OK)
        return err;


    /* (2.e) FAIT : deux boucles imbriquées (i, puis j) qui lisent
     *       chaque coefficient avec lire_entier(f, &tmp.coef[i][j]).
     *       Si une lecture échoue :
     *         mat_detruire(&tmp);  return err;
     *
     * Lecture des nb_lignes x nb_colonnes coefficients.
     *       À la moindre erreur (non numérique, trop grand, fichier
     *       tronqué...), on rend d'abord la mémoire de tmp, puis on
     *       renvoie l'erreur  */

    for (int i = 0; i < nb_lignes; i++) {
        for (int j = 0; j < nb_colonnes; j++) {
            err = lire_entier(f, &tmp.coef[i][j]);
            if (err != MAT_OK) {
                mat_detruire(&tmp);
                return err;
            }
        }
    }


    /* (2.f) FAIT : tout a réussi, on transfère le résultat :
     *         *res = tmp;  return MAT_OK;
     *       Tout a reussi : on transfere le résultat a l'appelant.
     *       C'est lui qui devra appeler mat_detruire (règle R2). */

    *res = tmp;
    return MAT_OK;

}
