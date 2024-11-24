#include "deplacement.h"
#include "Plato.h"
#include <stdio.h>
#include "Barriere.h"

void gererDeplacement(int *playerX, int *playerY, int currentPlayer) {
    char direction;
    int validMove = 0;

    while (!validMove) {
        printf("Enter direction (w/a/s/d): ");
        scanf(" %c", &direction);

        int newX = *playerX;
        int newY = *playerY;

        switch (direction) {
            case 'w': newX--; break; // Move up
            case 'a': newY--; break; // Move left
            case 's': newX++; break; // Move down
            case 'd': newY++; break; // Move right
            default:
                printf("Invalid direction!\n");
                continue;
        }

        // Vérification des limites du plateau
        if (newX >= 0 && newX < TAILLE && newY >= 0 && newY < TAILLE) {
            // Vérifier s'il y a une barrière sur le chemin
            if ((direction == 'w' && estBarrierePosee(*playerX, *playerY, 'H')) ||
                (direction == 's' && estBarrierePosee(newX, newY, 'H')) ||
                (direction == 'a' && estBarrierePosee(*playerX, *playerY, 'V')) ||
                (direction == 'd' && estBarrierePosee(*playerX, newY, 'V'))) {
                printf("You cannot move in that direction! A barrier is blocking the way.\n");
                continue;
            }

            // Check if the player is face-to-face with the other player
            if (plateau[newX][newY].joueur != 0) {
                int opponentX = newX;
                int opponentY = newY;
                int jumpX = newX;
                int jumpY = newY;

                switch (direction) {
                    case 'w': jumpX--; break; // Jump up
                    case 'a': jumpY--; break; // Jump left
                    case 's': jumpX++; break; // Jump down
                    case 'd': jumpY++; break; // Jump right
                }

                // Check if the jump is within bounds and not blocked by a barrier
                if (jumpX >= 0 && jumpX < TAILLE && jumpY >= 0 && jumpY < TAILLE &&
                    !estBarrierePosee(opponentX, opponentY, direction == 'w' || direction == 's' ? 'H' : 'V')) {
                    newX = jumpX;
                    newY = jumpY;
                } else {
                    printf("You cannot jump over the opponent! A barrier is blocking the way.\n");
                    continue;
                }
            }

            // Mise à jour de la position sur le plateau
            plateau[*playerX][*playerY].joueur = 0; // Efface la position actuelle
            plateau[newX][newY].joueur = currentPlayer; // Positionne le joueur à la nouvelle position
            *playerX = newX;
            *playerY = newY;
            validMove = 1;
        } else {
            printf("Move out of bounds!\n");
        }
    }
}