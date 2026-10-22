/*
 * main.c -- Programme de démonstration de la bibliothèque de matrices.
 *
 * FICHIER À COMPLÉTER (exercice 4, étapes 4.a à 4.d).
 *
 * Usage : ./demo_matrices <add|mul> <fichier_A> <fichier_B> <fichier_R>
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrice.h"
#include "matrice_alloc.h"
#include "matrice_io.h"
#include "matrice_calcul.h"

/* ------------------------------------------------------------------
 * FOURNI -- Ouvre le fichier, lit une matrice, ferme le fichier.
 * Affiche un message précis sur stderr en cas d'erreur.
 * ------------------------------------------------------------------ */
static MatErreur charger(const char *chemin, Matrice *m)
{
    FILE *f = fopen(chemin, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir \"%s\" : %s\n",
                chemin, strerror(errno));
        *m = MATRICE_VIDE;
        return MAT_ERR_LECTURE;
    }
    MatErreur err = mat_lire(f, m);
    fclose(f);
    if (err != MAT_OK)
        fprintf(stderr, "Erreur : lecture de \"%s\" : %s\n",
                chemin, mat_message_erreur(err));
    return err;
}

/* ------------------------------------------------------------------
 * FOURNI -- Ouvre le fichier en écriture, écrit la matrice, ferme le
 * fichier (en testant aussi le résultat de fclose).
 * ------------------------------------------------------------------ */
static MatErreur sauvegarder(const char *chemin, const Matrice *m)
{
    FILE *f = fopen(chemin, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur : impossible de créer \"%s\" : %s\n",
                chemin, strerror(errno));
        return MAT_ERR_ECRITURE;
    }
    MatErreur err = mat_ecrire(f, m);
    if (fclose(f) == EOF && err == MAT_OK)
        err = MAT_ERR_ECRITURE;
    if (err != MAT_OK)
        fprintf(stderr, "Erreur : écriture de \"%s\" : %s\n",
                chemin, mat_message_erreur(err));
    return err;
}

int main(int argc, char *argv[])
{
    /* FOURNI : vérification des arguments. */
    if (argc != 5
        || (strcmp(argv[1], "add") != 0 && strcmp(argv[1], "mul") != 0)) {
        fprintf(stderr, "Usage : %s <add|mul> <fichier_A> <fichier_B> "
                        "<fichier_R>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int addition = (strcmp(argv[1], "add") == 0);

    /* FOURNI : toutes les matrices démarrent vides (règle R1) et le
     * programme est en échec tant qu'il n'a pas tout réussi. */
    Matrice a = MATRICE_VIDE, b = MATRICE_VIDE, r = MATRICE_VIDE;
    int statut = EXIT_FAILURE;

    /* FOURNI : chargement des deux matrices. */
    if (charger(argv[2], &a) != MAT_OK || charger(argv[3], &b) != MAT_OK)
        goto nettoyage;

    /* (4.a) À COMPLÉTER : afficher A et B avec mat_afficher.          */


    /* (4.b) À COMPLÉTER : calculer r.
     *         MatErreur err = addition ? mat_additionner(&a, &b, &r)
     *                                  : mat_multiplier(&a, &b, &r);
     *       Si err != MAT_OK : afficher sur stderr un message utilisant
     *       mat_message_erreur(err) et les dimensions de A et de B,
     *       puis : goto nettoyage;                                    */

    (void)addition;   /* ligne provisoire : à supprimer en (4.b) */

    /* (4.c) À COMPLÉTER : afficher r (nom "R = A + B" ou "R = A x B").  */


    /* FOURNI : enregistrement de r dans le fichier argv[4]. */
    if (sauvegarder(argv[4], &r) != MAT_OK)
        goto nettoyage;

    /* (4.d) À COMPLÉTER : tout a réussi :
     *         - afficher "Résultat enregistré dans \"...\"." ;
     *         - statut = EXIT_SUCCESS;                                 */


nettoyage:
    /* FOURNI : point de sortie unique. Chaque matrice est détruite
     * exactement une fois, quel que soit le chemin suivi. */
    mat_detruire(&r);
    mat_detruire(&b);
    mat_detruire(&a);
    return statut;
}
