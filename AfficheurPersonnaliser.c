#include <windows.h>
#include "AfficheurPersonnaliser.h"

// In AfficheurPersonnaliser.c
#include <windows.h>
#include "AfficheurPersonnaliser.h"
#include <stdio.h>

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void afficherAide() {
    setCursorPosition(60, 0);
    printf("  ---- AIDE ----");
    setCursorPosition(60, 1);
    printf("  Placeholder for AIDE text.");
    setCursorPosition(60, 2);
    printf("  ---------------------");
}
