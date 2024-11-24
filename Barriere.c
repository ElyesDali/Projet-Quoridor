#include <stdio.h>
#include <stdbool.h>
#include "Barriere.h"
#include "Plato.h"

#define TAILLE 9

extern Barriere barriers[TAILLE * TAILLE];
extern int barrierCount;

extern Player players[2];

bool floodFill(int x, int y, int goalX, int goalY, bool visited[TAILLE][TAILLE]) {
    if (x < 0 || x >= TAILLE || y < 0 || y >= TAILLE || visited[x][y] || plateau[x][y].joueur == -1) {
        return false;
    }
    if (x == goalX && y == goalY) {
        return true;
    }
    visited[x][y] = true;

    // Check all four directions
    if (!estBarrierePosee(x, y, 'H') && floodFill(x - 1, y, goalX, goalY, visited)) return true; // Up
    if (!estBarrierePosee(x + 1, y, 'H') && floodFill(x + 1, y, goalX, goalY, visited)) return true; // Down
    if (!estBarrierePosee(x, y, 'V') && floodFill(x, y - 1, goalX, goalY, visited)) return true; // Left
    if (!estBarrierePosee(x, y + 1, 'V') && floodFill(x, y + 1, goalX, goalY, visited)) return true; // Right

    return false;
}

bool validerBarriere(int x, int y, char orientation) {
    // Simulate the placement of the barrier
    barriers[barrierCount].x = x;
    barriers[barrierCount].y = y;
    barriers[barrierCount].type = orientation;
    barrierCount++;

    // Check paths for each player
    bool visited[TAILLE][TAILLE] = {false};
    bool cheminJoueur1 = floodFill(0, 4, 8, 4, visited); // Player 1 must reach row 8

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            visited[i][j] = false;
        }
    }

    bool cheminJoueur2 = floodFill(8, 4, 0, 4, visited); // Player 2 must reach row 0

    // Revert the placement if a player is blocked
    if (!cheminJoueur1 || !cheminJoueur2) {
        barrierCount--;
        return false;
    }

    return true;
}

void poserBarriere(int x, int y, char type) {
    if (barrierCount < TAILLE * TAILLE) {
        if (validerBarriere(x, y, type)) {
            barriers[barrierCount].x = x;
            barriers[barrierCount].y = y;
            barriers[barrierCount].type = type;
            barrierCount++;
        } else {
            printf("Placement de la barrière invalide : cela bloque le passage d'un joueur.\n");
        }
    }
}

int estBarrierePosee(int x, int y, char type) {
    for (int i = 0; i < barrierCount; i++) {
        if (barriers[i].x == x && barriers[i].y == y && barriers[i].type == type) {
            return 1;
        }
    }
    return 0;
}

void demanderBarriere(int *col, int *row, char *orientation) {
    int validInput = 0;

    while (!validInput) {
        printf("Enter barrier lignes: ");
        if (scanf("%d", col) != 1) {
            printf("Invalid column! Please enter a valid ligne.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        printf("Enter barrier colonnes: ");
        if (scanf("%d", row) != 1) {
            printf("Invalid row! Please enter a valid colonnes.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        printf("Enter barrier orientation (H for horizontal, V for vertical): ");
        if (scanf(" %c", orientation) != 1 || (*orientation != 'H' && *orientation != 'V')) {
            printf("Invalid orientation! Please enter H for horizontal or V for vertical.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        validInput = 1;
    }
}