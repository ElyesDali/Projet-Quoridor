#include "Victoire.h"

// Fonction pour vérifier si un joueur a gagné
// PlayerX : La position en X du joueur sur le plateau
// PlayerY : La position en Y du joueur sur le plateau
// currentPlayer : Le numéro du joueur actuel (1 à 4)
// Retourne 1 si le joueur a gagné, sinon 0
int victoire(int PlayerX, int PlayerY, int currentPlayer) {
    // Vérifie si le joueur 1 a atteint la ligne 8 (objectif en bas du plateau)
    if (currentPlayer == 1) {
        if (PlayerX == 8) {  // Si le joueur 1 est sur la ligne 8 en X
            return 1;  // Joueur 1 a gagné
        }
    }
    // Vérifie si le joueur 2 a atteint la ligne 0 (objectif en haut du plateau)
    else if (currentPlayer == 2) {
        if (PlayerX == 0) {  // Si le joueur 2 est sur la ligne 0 en X
            return 1;  // Joueur 2 a gagné
        }
    }
    // Vérifie si le joueur 3 a atteint la colonne 8 (objectif à droite du plateau)
    else if (currentPlayer == 3) {
        if (PlayerY == 8) {  // Si le joueur 3 est sur la colonne 8 en Y
            return 1;  // Joueur 3 a gagné
        }
    }
    // Vérifie si le joueur 4 a atteint la colonne 0 (objectif à gauche du plateau)
    else if (currentPlayer == 4) {
        if (PlayerY == 0) {  // Si le joueur 4 est sur la colonne 0 en Y
            return 1;  // Joueur 4 a gagné
        }
    }
    // Si aucune des conditions n'est remplie, le jeu continue
    return 0;  // Aucun gagnant
}
