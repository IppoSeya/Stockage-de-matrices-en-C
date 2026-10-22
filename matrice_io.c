/*
 * matrice_io.c -- Lecture, écriture et affichage des matrices.
 *
 * FICHIER À COMPLÉTER (exercice 2, étapes 2.a à 2.f).
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

    /* (2.a) À COMPLÉTER : pour chaque ligne i, afficher chaque
     *       coefficient avec printf(" %8d", m->coef[i][j]),
     *       puis passer à la ligne avec putchar('\n').               */
}

MatErreur mat_ecrire(FILE *f, const Matrice *m)
{
    if (f == NULL || !mat_est_valide(m))                 /* FOURNI */
        return MAT_ERR_ARGUMENT;

    /* FOURNI : première ligne du fichier = les dimensions. */
    if (fprintf(f, "%d %d\n", m->nb_lignes, m->nb_colonnes) < 0)
        return MAT_ERR_ECRITURE;

    /* (2.b) À COMPLÉTER : pour chaque ligne i de la matrice :
     *         - écrire les coefficients séparés par UN espace :
     *             le premier (j == 0) avec "%d", les autres avec " %d" ;
     *         - terminer la ligne avec fputc('\n', f) ;
     *         - si un fprintf renvoie un nombre < 0, ou si fputc
     *           renvoie EOF : return MAT_ERR_ECRITURE;               */


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

    /* (2.c) À COMPLÉTER : si nb_lignes ou nb_colonnes n'est pas compris
     *       entre 1 et MAT_DIM_MAX, renvoyer MAT_ERR_FORMAT
     *       (c'est le contenu du fichier qui est faux).               */


    /* (2.d) À COMPLÉTER : déclarer une matrice LOCALE et l'allouer :
     *         Matrice tmp;
     *         err = mat_allouer(&tmp, nb_lignes, nb_colonnes);
     *         if (err != MAT_OK) return err;                          */


    /* (2.e) À COMPLÉTER : deux boucles imbriquées (i, puis j) qui lisent
     *       chaque coefficient avec lire_entier(f, &tmp.coef[i][j]).
     *       Si une lecture échoue :
     *         mat_detruire(&tmp);  return err;                        */


    /* (2.f) À COMPLÉTER : tout a réussi, on transfère le résultat :
     *         *res = tmp;  return MAT_OK;                             */

    return MAT_ERR_LECTURE;  /* ligne provisoire : à remplacer en (2.f) */
}
