#include <windows.h>
#include "AfficheurPersonnaliser.h"

// Fonction pour déplacer le curseur à une position spécifiée dans la console
// x : La position horizontale (colonne) du curseur
// y : La position verticale (ligne) du curseur
void setCursorPosition(int x, int y) {
    COORD coord;  // Déclaration d'une structure COORD pour stocker la position du curseur
    coord.X = x;  // Assigner la position x (colonne)
    coord.Y = y;  // Assigner la position y (ligne)

    // Utilisation de la fonction SetConsoleCursorPosition pour déplacer le curseur à la position spécifiée
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour afficher l'aide dans la fenêtre de la console
void afficherAide() {
    // Déplacer le curseur à la position (60, 0) pour afficher le titre de l'aide
    setCursorPosition(60, 0);
    printf("  ---- AIDE ----");

    // Déplacer le curseur à la position (60, 1) pour afficher un texte de remplacement pour l'aide
    setCursorPosition(60, 1);
    printf("  Placeholder for AIDE text.");

    // Déplacer le curseur à la position (60, 2) pour afficher une ligne de séparation sous l'aide
    setCursorPosition(60, 2);
    printf("  ---------------------");
}
