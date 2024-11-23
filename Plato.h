#ifndef QUORIDOR_PLATO_H
#define QUORIDOR_PLATO_H

#include "Player.h"

#define TAILLE 9

typedef struct {
    int joueur;
} Case;

extern Case plateau[TAILLE][TAILLE];

void afficherPlateau();
void initialiserPlateau();
void clearScreen();
void displayInfo(int remainingTime, Player players[]);
void afficherAide(); // Add this line

#endif // QUORIDOR_PLATO_H