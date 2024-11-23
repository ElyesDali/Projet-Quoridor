#ifndef BARRIERE_H
#define BARRIERE_H

typedef struct {
    int x;
    int y;
    char type; // 'H' for horizontal, 'V' for vertical
} Barriere;

int estBarrierePosee(int x, int y, char type);
void poserBarriere(int x, int y, char type);
void demanderBarriere(int *col, int *row, char *orientation); // Add this line

#endif // BARRIERE_H