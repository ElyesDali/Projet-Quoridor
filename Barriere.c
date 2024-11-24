#include <stdio.h>
#include <stdbool.h>
#include "Barriere.h"
#include "Plato.h"

#define TAILLE 9  // Taille du plateau de jeu, 9x9 cases

extern Barriere barrieres[TAILLE * TAILLE];  // Tableau pour stocker les barrières posées
extern int compteurBarriere;  // Compteur de barrières posées
extern Player joueurs[2];  // Tableau pour stocker les informations des joueurs

// Fonction de recherche de chemin à travers le plateau, utilisée pour vérifier si un joueur peut atteindre sa destination
// x, y : Position actuelle
// goalX, goalY : Position de destination du joueur
// visited : Tableau pour garder trace des cases déjà visitées pour éviter les boucles infinies
bool remplissage(int x, int y, int goalX, int goalY, bool visite[TAILLE][TAILLE]) {
    // Implémentation de l'algorithme de remplissage
    if (x == goalX && y == goalY) {
        return true;
    }
    // Ajouter la logique de remplissage ici
    return false;
}

// Fonction qui valide le placement d'une barrière
// x, y : Position de la barrière
// orientation : 'H' pour horizontal, 'V' pour vertical
bool validerBarriere(int x, int y, char orientation) {
    bool visite[TAILLE][TAILLE] = {false};
    bool cheminJoueur1 = remplissage(0, 4, 8, 4, visite);  // Vérifie si le joueur 1 peut atteindre la ligne 8
    bool cheminJoueur2 = remplissage(8, 4, 0, 4, visite);  // Vérifie si le joueur 2 peut atteindre la ligne 0

    if (!cheminJoueur1 || !cheminJoueur2) {
        return false;
    }

    return true;  // La barrière est valide si les deux joueurs peuvent encore atteindre leur destination
}

// Fonction pour poser une barrière sur le plateau
// x, y : Position de la barrière
// type : 'H' pour horizontal, 'V' pour vertical
void poserBarriere(int x, int y, char type) {
    // Implémentation pour poser une barrière
}

// Fonction qui vérifie si une barrière est déjà posée à une position donnée
// x, y : Position de la barrière
// type : 'H' pour horizontal, 'V' pour vertical
int estBarrierePosee(int x, int y, char type) {
    // Implémentation pour vérifier si une barrière est posée
    return 0;
}

// Fonction qui demande à l'utilisateur les coordonnées et l'orientation d'une barrière
// col, row : Pointeurs sur les coordonnées de la barrière
// orientation : Pointeur sur l'orientation de la barrière ('H' ou 'V')
void demanderBarriere(int *col, int *row, char *orientation) {
    int entreeValide = 0;  // Indicateur d'entrée valide

    // Boucle pour demander des entrées valides
    while (!entreeValide) {
        // Demande et vérifie la colonne
        printf("Entrez la ligne de la barrière : ");
        if (scanf("%d", col) != 1) {
            printf("Ligne invalide! Veuillez entrer une ligne valide.\n");
            while (getchar() != '\n');
        }

        // Demande et vérifie la ligne
        printf("Entrez la colonne de la barrière : ");
        if (scanf("%d", row) != 1) {
            printf("Colonne invalide! Veuillez entrer une colonne valide.\n");
            while (getchar() != '\n');  // Efface le tampon d'entrée
            continue;
        }

        // Demande et vérifie l'orientation de la barrière
        printf("Entrez l'orientation de la barrière (H pour horizontal, V pour vertical) : ");
        if (scanf(" %c", orientation) != 1 || (*orientation != 'H' && *orientation != 'V')) {
            printf("Orientation invalide! Veuillez entrer H pour horizontal ou V pour vertical.\n");
            while (getchar() != '\n');  // Efface le tampon d'entrée
            continue;
        }

        entreeValide = 1;  // Entrée valide, on sort de la boucle
    }
}