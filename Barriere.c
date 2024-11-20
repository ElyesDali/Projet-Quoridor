
#include <stdio.h>



int estBarrierePosee(int x, int y, char type) {
    for (int i = 0; i < barrierCount; i++) {
        if (barriers[i].x == x && barriers[i].y == y && barriers[i].type == type) {
            return 1; // Barrière trouvée
        }
    }
    return 0; // Barrière non trouvée
}
void poserBarriere(int x, int y, char type) {
    if (barrierCount < TAILLE * TAILLE) { // Assurez-vous de ne pas dépasser le nombre maximal de barrières
        barriers[barrierCount].x = x;
        barriers[barrierCount].y = y;
        barriers[barrierCount].type = type;
        barrierCount++;

        if (type == 'H') {
            players[0].remainingBarriers--; // Décrémente le nombre de barrières restantes pour le joueur 1            Erreur dans cette fonction.
        } else if (type == 'V') {
            players[1].remainingBarriers--; // Décrémente le nombre de barrières restantes pour le joueur 2
        }
    }
}
m
