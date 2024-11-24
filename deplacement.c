#include "deplacement.h"
#include "Plato.h"
#include <stdio.h>
#include "Barriere.h"

// Fonction pour gérer le déplacement d'un joueur
void gererDeplacement(int *playerX, int *playerY, int currentPlayer) {
    char direction;    // Stocke la direction du déplacement (w/a/s/d)
    int validMove = 0; // Indique si le déplacement est valide

    while (!validMove) {
        // Demande au joueur d'entrer une direction
        printf("Enter direction (w/a/s/d): ");
        scanf(" %c", &direction);

        // Initialise les nouvelles coordonnées du joueur
        int newX = *playerX;
        int newY = *playerY;

        // Met à jour les coordonnées en fonction de la direction
        switch (direction) {
            case 'w': newX--; break; // Déplacement vers le haut
            case 'a': newY--; break; // Déplacement vers la gauche
            case 's': newX++; break; // Déplacement vers le bas
            case 'd': newY++; break; // Déplacement vers la droite
            default:
                // Si la direction est invalide, afficher un message et recommencer
                printf("Invalid direction!\n");
                continue;
        }

        // Vérifie si le mouvement reste dans les limites du plateau
        if (newX >= 0 && newX < TAILLE && newY >= 0 && newY < TAILLE) {
            // Vérifie s'il y a une barrière bloquant le chemin dans la direction donnée
            if ((direction == 'w' && estBarrierePosee(*playerX, *playerY, 'H')) ||
                (direction == 's' && estBarrierePosee(newX, newY, 'H')) ||
                (direction == 'a' && estBarrierePosee(*playerX, *playerY, 'V')) ||
                (direction == 'd' && estBarrierePosee(*playerX, newY, 'V'))) {
                printf("You cannot move in that direction! A barrier is blocking the way.\n");
                continue;
            }

            // Gérer le cas où le joueur rencontre un adversaire face à lui
            if (plateau[newX][newY].joueur != 0) {
                // L'adversaire est directement devant
                int opponentX = newX;
                int opponentY = newY;
                int jumpX = newX;
                int jumpY = newY;

                // Calcule les coordonnées pour sauter par-dessus l'adversaire
                switch (direction) {
                    case 'w': jumpX--; break; // Saut vers le haut
                    case 'a': jumpY--; break; // Saut vers la gauche
                    case 's': jumpX++; break; // Saut vers le bas
                    case 'd': jumpY++; break; // Saut vers la droite
                }

                // Vérifie si le saut est possible (dans les limites et sans barrière)
                if (jumpX >= 0 && jumpX < TAILLE && jumpY >= 0 && jumpY < TAILLE &&
                    !estBarrierePosee(opponentX, opponentY, direction == 'w' || direction == 's' ? 'H' : 'V')) {
                    // Effectue le saut
                    newX = jumpX;
                    newY = jumpY;
                } else {
                    // Si le saut est bloqué, afficher un message et recommencer
                    printf("You cannot jump over the opponent! A barrier is blocking the way.\n");
                    continue;
                }
            }

            // Met à jour le plateau après un mouvement valide
            plateau[*playerX][*playerY].joueur = 0; // Efface l'ancienne position du joueur
            plateau[newX][newY].joueur = currentPlayer; // Met à jour la nouvelle position
            *playerX = newX; // Met à jour la coordonnée X du joueur
            *playerY = newY; // Met à jour la coordonnée Y du joueur
            validMove = 1; // Indique que le mouvement est valide
        } else {
            // Si le mouvement dépasse les limites du plateau
            printf("Move out of bounds!\n");
        }
    }
}
