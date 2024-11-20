#include "deplacement.h"
#include "Plato.h"
#include <stdio.h>

void gererDeplacement(int *playerX, int *playerY, int currentPlayer) {
    char direction;
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
        return;
    }

    // Check if the new position is within the board limits
    if (newX >= 0 && newX < TAILLE && newY >= 0 && newY < TAILLE) {
        // Clear the current position
        plateau[*playerX][*playerY].joueur = 0;
        // Update the board with the new position
        plateau[newX][newY].joueur = currentPlayer;
        *playerX = newX;
        *playerY = newY;
    } else {
        printf("Move out of bounds!\n");
    }
}
