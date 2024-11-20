#include <stdio.h>
#include "Barriere.h"

#define TAILLE 10  // Définir TAILLE

typedef struct {
    int remainingBarriers;
} Player;  // Définir Player

extern Barriere barriers[TAILLE * TAILLE];
extern int barrierCount;

extern Player players[2];

int estBarrierePosee(int x, int y, char type) {
    for (int i = 0; i < barrierCount; i++) {
        if (barriers[i].x == x && barriers[i].y == y && barriers[i].type == type) {
            return 1;
        }
    }
    return 0;
}

void poserBarriere(int x, int y, char type) {
    if (barrierCount < TAILLE * TAILLE) {
        barriers[barrierCount].x = x;
        barriers[barrierCount].y = y;
        barriers[barrierCount].type = type;
        barrierCount++;

        if (type == 'H') {
            players[0].remainingBarriers--;
        } else if (type == 'V') {
            players[1].remainingBarriers--;
        }
    }
}
