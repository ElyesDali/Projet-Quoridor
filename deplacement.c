#include "deplacement.h"
#include "Plato.h"
#include "Barriere.h"
#include <conio.h>  // Include for kbhit() and getch() on Windows

void deplacerJoueur(int *x, int *y, int dx, int dy) {
    int newX = *x + dx;
    int newY = *y + dy;

    if (newX >= 0 && newX < TAILLE && newY >= 0 && newY < TAILLE) {
        if (plateau[newX][newY].joueur == 0) {
            if ((dx == -1 && estBarrierePosee(*x, *y, 'H')) ||
                (dx == 1 && estBarrierePosee(*x + 1, *y, 'H')) ||
                (dy == -1 && estBarrierePosee(*x, *y, 'V')) ||
                (dy == 1 && estBarrierePosee(*x, *y + 1, 'V'))) {
                return;
                }

            plateau[newX][newY].joueur = plateau[*x][*y].joueur;
            plateau[*x][*y].joueur = 0;
            *x = newX;
            *y = newY;
        }
    }
}

void gererDeplacement(int *playerX, int *playerY) {
    if (kbhit()) {
        int key = getch();
        if (key == 0 || key == 224) {
            switch (getch()) {
                case 72: // Up arrow
                    deplacerJoueur(playerX, playerY, -1, 0);
                break;
                case 80: // Down arrow
                    deplacerJoueur(playerX, playerY, 1, 0);
                break;
                case 75: // Left arrow
                    deplacerJoueur(playerX, playerY, 0, -1);
                break;
                case 77: // Right arrow
                    deplacerJoueur(playerX, playerY, 0, 1);
                break;
            }
        }
    }
}