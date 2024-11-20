
#ifndef ESQD_H
#define ESQD_H


int estBarrierePosee(int x, int y, char type);
void poserBarriere(int x, int y, char type);
void deplacerJoueur(int *x, int *y, int dx, int dy);
void gererDeplacement(int *playerX, int *playerY);

#endif //ESQD_H
