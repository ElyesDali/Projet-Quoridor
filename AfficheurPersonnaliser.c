#include <windows.h>
#include "AfficheurPersonnaliser.h"
#include <stdio.h>

// Fonction pour positionner le curseur à une position spécifique dans la console
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour afficher l'aide
void afficherAide() {
    setCursorPosition(60, 0);  // Position du titre "AIDE"
    printf("  ---- AIDE ----");

    // Explication du but du jeu
    setCursorPosition(60, 1);
    printf("  But : Atteindre l'autre cote.");

    // Instructions pour le déplacement
    setCursorPosition(60, 2);
    printf("  Deplacement :");
    setCursorPosition(60, 3);
    printf("  - W : Haut");
    setCursorPosition(60, 4);
    printf("  - S : Bas");
    setCursorPosition(60, 5);
    printf("  - A : Gauche");
    setCursorPosition(60, 6);
    printf("  - D : Droite");

    // Instructions pour poser une barrière
    setCursorPosition(60, 7);
    printf("  Pose de barriere :");
    setCursorPosition(60, 8);
    printf("  - Ligne puis colonne (0-8)");
    setCursorPosition(60, 9);
    printf("  - H : Horizontal, V : Vertical");

    // Instructions pour sauter un tour
    setCursorPosition(60, 10);
    printf("  Sauter un tour :");
    setCursorPosition(60, 11);
    printf("  - Appuyez sur 1.");

    // Instructions pour refaire un coup à la fin du tour
    setCursorPosition(60, 12);
    printf("  Refaire un coup :");
    setCursorPosition(60, 13);
    printf("  - A la fin du tour.");

    // Instructions pour quitter le jeu
    setCursorPosition(60, 14);
    printf("  Quitter :");
    setCursorPosition(60, 15);
    printf("  - Appuyez sur 0.");

    setCursorPosition(60, 16);  // Position du séparateur
    printf("  ---------------------");
}
