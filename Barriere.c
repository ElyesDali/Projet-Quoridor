#include <stdio.h>
#include "Barriere.h"

#define TAILLE 10  // Define TAILLE

typedef struct {
    int remainingBarriers;
} Player;  // Define Player

extern Barriere barriers[TAILLE * TAILLE];
extern int barrierCount;

extern Player players[2];

void poserBarriere(int x, int y, char type) {
    if (barrierCount < TAILLE * TAILLE) {
        barriers[barrierCount].x = x;
        barriers[barrierCount].y = y;
        barriers[barrierCount].type = type;
        barrierCount++;
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