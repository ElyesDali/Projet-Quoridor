#include "deplacement.h"
#include "Plato.h"
#include <stdio.h>

#include "Barriere.h"

void gererDeplacement(int *playerX, int *playerY, int currentPlayer) {
    char direction;
    int validMove = 0; // Variable pour savoir si le mouvement est valide

    while (!validMove) {
        printf("Enter direction (w/a/s/d): ");
        scanf(" %c", &direction);

        int newX = *playerX;
        int newY = *playerY;

        // Vérifie si une barrière bloque le mouvement
        if ((direction == 'w' || direction =='W') && estBarrierePosee(*playerX - 1, *playerY, 'H')) {
            printf("Move blocked by horizontal barrier!\n");
        } else if ((direction == 'a' || direction =='A') && estBarrierePosee(*playerX, *playerY - 1, 'V')) {
            printf("Move blocked by vertical barrier!\n");
        } else if ((direction == 'D' || direction =='d') && estBarrierePosee(*playerX, *playerY + 1, 'V')) {
            printf("Move blocked by vertical barrier!\n");
        } else if ((direction == 'S' || direction =='s') && estBarrierePosee(*playerX + 1, *playerY, 'H')) {
            printf("Move blocked by horizontal barrier!\n");
        } else {
            // Si le mouvement est valide, effectue le déplacement
            switch (direction) {
                case 'w': newX--; break;
                case 'W': newX--; break;
                case 'a': newY--; break;
                case 'A': newY--; break;
                case 's': newX++; break;
                case 'S': newX++; break;
                case 'd': newY++; break;
                case 'D': newY++; break;
                default:
                    printf("Invalid direction!\n");
                    continue;  // Si la direction est invalide, demande à nouveau
            }

            // Vérifie si le nouveau mouvement est dans les limites du plateau
            if (newX >= 0 && newX < TAILLE && newY >= 0 && newY < TAILLE) {
                // Supprime la position actuelle
                plateau[*playerX][*playerY].joueur = 0;
                // Met à jour la position sur le plateau
                plateau[newX][newY].joueur = currentPlayer;
                *playerX = newX;
                *playerY = newY;
                validMove = 1; // Le mouvement est valide, sort de la boucle
            } else {
                printf("Move out of bounds!\n");
            }
        }
    }
}
