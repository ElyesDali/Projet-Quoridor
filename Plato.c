#include "Plato.h"
#include <stdio.h>
#include <stdlib.h>
#include "Barriere.h"
#include <time.h>
#include <unistd.h>

Case plateau[TAILLE][TAILLE];
Barriere barriers[TAILLE * TAILLE];
int barrierCount = 0;
Player players[2];

void initialiserPlateau() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j].joueur = 0;
        }
    }
    plateau[0][4].joueur = 1;
    plateau[8][4].joueur = 2;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayInfo(int remainingTime, Player players[]) {
    printf("  ---- PLAYER INFO ----\n");
    printf("  Player 1: Barriers: %d\n", players[0].remainingBarriers);
    printf("  Player 2: Barriers: %d\n", players[1].remainingBarriers);
    printf("  Time Remaining: %02d:%02d\n", remainingTime / 60, remainingTime % 60);
    printf("  ---------------------\n");
}

void afficherPlateau() {
    clearScreen();
    printf("   ");
    for (int i = 0; i < TAILLE; i++) {
        printf("  %d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAILLE; i++) {
        printf("   ");
        for (int j = 0; j < TAILLE; j++) {
            if (estBarrierePosee(i, j, 'H') || (i == 0)) {
                printf("+###");
            } else {
                printf("+---");
            }
        }
        printf("+\n");
        printf(" %d ", i);
        for (int j = 0; j < TAILLE; j++) {
            if (estBarrierePosee(i, j, 'V') || (j == 0)) {
                printf("#");
            } else {
                printf("|");
            }

            if (plateau[i][j].joueur == 1) {
                printf(" 1 ");
            } else if (plateau[i][j].joueur == 2) {
                printf(" 2 ");
            } else {
                printf("   ");
            }
        }
        printf("#\n");
    }
    printf("   ");
    for (int j = 0; j < TAILLE; j++) {
        printf("+###");
    }
    printf("+\n");
}
