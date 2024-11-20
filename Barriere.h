#ifndef BARRIERE_H
#define BARRIERE_H

typedef struct {
    int x;
    int y;
    char type; // 'H' pour horizontale, 'V' pour verticale
} Barriere;

int estBarrierePosee(int x, int y, char type);
void poserBarriere(int x, int y, char type);

#endif // BARRIERE_H
