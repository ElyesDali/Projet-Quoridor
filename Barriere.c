#include <stdio.h>
#include <stdbool.h>
#include "Barriere.h"
#include "Plato.h"

#define TAILLE 9  // Taille du plateau de jeu, 9x9 cases

extern Barriere barriers[TAILLE * TAILLE];  // Tableau pour stocker les barrières posées
extern int barrierCount;  // Compteur de barrières posées

extern Player players[2];  // Tableau pour stocker les informations des joueurs

// Fonction de recherche de chemin à travers le plateau, utilisée pour vérifier si un joueur peut atteindre sa destination
// x, y : Position actuelle
// goalX, goalY : Position de destination du joueur
// visited : Tableau pour garder trace des cases déjà visitées pour éviter les boucles infinies
bool floodFill(int x, int y, int goalX, int goalY, bool visited[TAILLE][TAILLE]) {
    // Vérifie si la case est hors limites, déjà visitée ou bloquée par une barrière
    if (x < 0 || x >= TAILLE || y < 0 || y >= TAILLE || visited[x][y] || plateau[x][y].joueur == -1) {
        return false;
    }
    // Si le joueur atteint la destination, retourne vrai
    if (x == goalX && y == goalY) {
        return true;
    }
    visited[x][y] = true;  // Marque la case comme visitée

    // Vérifie dans les quatre directions (haut, bas, gauche, droite)
    if (!estBarrierePosee(x, y, 'H') && floodFill(x - 1, y, goalX, goalY, visited)) return true; // Haut
    if (!estBarrierePosee(x + 1, y, 'H') && floodFill(x + 1, y, goalX, goalY, visited)) return true; // Bas
    if (!estBarrierePosee(x, y, 'V') && floodFill(x, y - 1, goalX, goalY, visited)) return true; // Gauche
    if (!estBarrierePosee(x, y + 1, 'V') && floodFill(x, y + 1, goalX, goalY, visited)) return true; // Droite

    return false;  // Retourne faux si aucune direction ne mène à la destination
}

// Fonction qui valide le placement d'une barrière
// x, y : Position de la barrière
// orientation : 'H' pour horizontal, 'V' pour vertical
bool validerBarriere(int x, int y, char orientation) {
    // Simule la pose de la barrière
    barriers[barrierCount].x = x;
    barriers[barrierCount].y = y;
    barriers[barrierCount].type = orientation;
    barrierCount++;

    // Vérifie si les deux joueurs peuvent toujours atteindre leur objectif
    bool visited[TAILLE][TAILLE] = {false};  // Tableau de cases visitées pour éviter les boucles infinies
    bool cheminJoueur1 = floodFill(0, 4, 8, 4, visited);  // Vérifie si le joueur 1 peut atteindre la ligne 8

    // Réinitialisation du tableau de visites pour le joueur 2
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            visited[i][j] = false;
        }
    }

    // Vérifie si le joueur 2 peut atteindre la ligne 0
    bool cheminJoueur2 = floodFill(8, 4, 0, 4, visited);

    // Si l'une des vérifications échoue, on annule la pose de la barrière
    if (!cheminJoueur1 || !cheminJoueur2) {
        barrierCount--;
        return false;
    }

    return true;  // La barrière est valide si les deux joueurs peuvent encore atteindre leur destination
}

// Fonction pour poser une barrière sur le plateau
// x, y : Position de la barrière
// type : 'H' pour horizontal, 'V' pour vertical
void poserBarriere(int x, int y, char type) {
    if (barrierCount < TAILLE * TAILLE) {  // Vérifie s'il y a de la place pour poser une nouvelle barrière
        if (validerBarriere(x, y, type)) {  // Valide le placement de la barrière
            barriers[barrierCount].x = x;
            barriers[barrierCount].y = y;
            barriers[barrierCount].type = type;
            barrierCount++;
        } else {
            printf("Placement de la barrière invalide : cela bloque le passage d'un joueur.\n");  // Affiche un message d'erreur si le placement est invalide
        }
    }
}

// Fonction qui vérifie si une barrière est déjà posée à une position donnée
// x, y : Position de la barrière
// type : 'H' pour horizontal, 'V' pour vertical
int estBarrierePosee(int x, int y, char type) {
    for (int i = 0; i < barrierCount; i++) {
        // Compare chaque barrière déjà posée avec celle recherchée
        if (barriers[i].x == x && barriers[i].y == y && barriers[i].type == type) {
            return 1;  // Retourne 1 si la barrière est déjà posée
        }
    }
    return 0;  // Retourne 0 si la barrière n'est pas posée
}

// Fonction qui demande à l'utilisateur les coordonnées et l'orientation d'une barrière
// col, row : Pointeurs sur les coordonnées de la barrière
// orientation : Pointeur sur l'orientation de la barrière ('H' ou 'V')
void demanderBarriere(int *col, int *row, char *orientation) {
    int validInput = 0;

    // Boucle pour demander des entrées valides
    while (!validInput) {
        // Demande et vérifie la colonne
        printf("Enter barrier lignes: ");
        if (scanf("%d", col) != 1) {
            printf("Invalid column! Please enter a valid ligne.\n");
            while (getchar() != '\n');  // Efface le tampon d'entrée
            continue;
        }

        // Demande et vérifie la ligne
        printf("Enter barrier colonnes: ");
        if (scanf("%d", row) != 1) {
            printf("Invalid row! Please enter a valid colonnes.\n");
            while (getchar() != '\n');  // Efface le tampon d'entrée
            continue;
        }

        // Demande et vérifie l'orientation de la barrière
        printf("Enter barrier orientation (H for horizontal, V for vertical): ");
        if (scanf(" %c", orientation) != 1 || (*orientation != 'H' && *orientation != 'V')) {
            printf("Invalid orientation! Please enter H for horizontal or V for vertical.\n");
            while (getchar() != '\n');  // Efface le tampon d'entrée
            continue;
        }

        validInput = 1;  // Entrée valide, on sort de la boucle
    }
}
