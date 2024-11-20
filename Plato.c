#include <stdio.h>
#include <stdlib.h> // Pour system()
#define BARRIERE_H
#include <time.h>
#include <unistd.h>


#define TAILLE 9
#define INITIAL_TIME (5 * 60)

typedef struct {
    int joueur;      // 0 = vide, 1 = joueur 1, 2 = joueur 2
} Case;

typedef struct {
    int x;          // Coordonnée x de la barrière
    int y;          // Coordonnée y de la barrière
    char type;      // 'H' pour horizontale, 'V' pour verticale
} Barriere;

typedef struct {
    int playerID;
    int remainingBarriers;
} Player;

Case plateau[TAILLE][TAILLE];
Barriere barriers[TAILLE * TAILLE]; // Un tableau pour stocker les barrières
int barrierCount = 0; // Compteur de barrières posées
Player players[2];

void initialiserPlateau() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j].joueur = 0; // Toutes les cases sont vides au départ
        }
    }
    plateau[0][4].joueur = 1; // Joueur 1
    plateau[8][4].joueur = 2; // Joueur 2
}



void afficherPlateau() {
    clearScreen();
    printf("   ");
    for (int i = 0; i < TAILLE; i++) {
        printf("  %d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAILLE; i++) {
        printf("   ");
        for (int j = 0; j < TAILLE; j++) {
            // Affiche les barres horizontales
            if (estBarrierePosee(i, j, 'H')||(i == 0)) {
                printf("+###");
            } else {
                printf("+---");
            }
        }
        printf("+\n");
        printf(" %d ", i);
        for (int j = 0; j < TAILLE; j++) {
            // Affiche les cases et les barrières verticales
            if (estBarrierePosee(i, j, 'V')|| (j==0) ) {
                printf("#");
            } else {
                printf("|");
            }

            if (plateau[i][j].joueur == 1) {
                printf(" 1 ");
            } else if (plateau[i][j].joueur == 2) {
                printf(" 2 ");
            } else {
                printf("   ");
            }
        }
        // Ferme la ligne avec la barrière
        printf("#\n");
    }
    printf("   ");
    for (int j = 0; j < TAILLE; j++) {
        printf("+###");
    }
    printf("+\n");
}

// Fonction pour effacer l'écran
void clearScreen() {
#ifdef _WIN32
    system("cls"); // Pour Windows
#else
    system("clear"); // Pour Linux/Mac
#endif
}

void displayInfo(int remainingTime, Player players[]) {
    printf("  ---- PLAYER INFO ----\n");
    printf("  Player 1: Barriers: %d\n", players[0].remainingBarriers);
    printf("  Player 2: Barriers: %d\n", players[1].remainingBarriers);
    printf("  Time Remaining: %02d:%02d\n", remainingTime / 60, remainingTime % 60);
    printf("  ---------------------\n");
}
