#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOUEURS 4
#define MAX_NOM 50

typedef struct {
    char nom[MAX_NOM];
    int classement;
    int coups;
    int victoires;
    int parties_jouees;
} Joueur;

void initialiserClassement(Joueur *joueurs, int nbJoueurs) {
    // Initialisation basique du classement
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i].classement = i + 1;
        joueurs[i].coups = 0;
        joueurs[i].victoires = 0;
        joueurs[i].parties_jouees = 0;
        // On suppose que les noms sont définis ailleurs
    }
}

void miseAJourJoueur(Joueur *joueur, int coups, int gagnant) {
    joueur->coups += coups;
    joueur->parties_jouees++; // Incrémentation des parties jouées
    if (gagnant) {
        joueur->victoires++; // Incrémentation des victoires
    }
}

void trierClassement(Joueur *joueurs, int nbJoueurs) {
   
    for (int i = 0; i < nbJoueurs - 1; i++) {
        for (int j = 0; j < nbJoueurs - i - 1; j++) {
            if (joueurs[j].victoires < joueurs[j + 1].victoires) {
                Joueur temp = joueurs[j];
                joueurs[j] = joueurs[j + 1];
                joueurs[j + 1] = temp;
            }
        }
    }
    // Mise à jour des classements
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i].classement = i + 1;
    }
}

void afficherClassement(Joueur *joueurs, int nbJoueurs) {
    // Affiche le classement actuel
    printf("\n--- Classement ---\n");
    printf("Rang | Nom                 | Coups | Victoires | Parties jouées\n");
    printf("-----|---------------------|-------|-----------|----------------\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("%-4d | %-19s | %-5d | %-9d | %-14d\n",
               joueurs[i].classement,
               joueurs[i].nom,
               joueurs[i].coups,
               joueurs[i].victoires,
               joueurs[i].parties_jouees);
    }
    printf("\n");
}
