
#include <stdio.h>
#include <stdlib.h> // Pour system()
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

void poserBarriere(int x, int y, char type) {
    if (barrierCount < TAILLE * TAILLE) { // Assurez-vous de ne pas dépasser le nombre maximal de barrières
        barriers[barrierCount].x = x;
        barriers[barrierCount].y = y;
        barriers[barrierCount].type = type;
        barrierCount++;

        if (type == 'H') {
            players[0].remainingBarriers--; // Décrémente le nombre de barrières restantes pour le joueur 1
        } else if (type == 'V') {
            players[1].remainingBarriers--; // Décrémente le nombre de barrières restantes pour le joueur 2
        }
    }
}

int estBarrierePosee(int x, int y, char type) {
    for (int i = 0; i < barrierCount; i++) {
        if (barriers[i].x == x && barriers[i].y == y && barriers[i].type == type) {
            return 1; // Barrière trouvée
        }
    }
    return 0; // Barrière non trouvée
}

void afficherPlateau() {
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

int main() {
    initialiserPlateau();
    players[0].playerID = 1;
    players[0].remainingBarriers = 10;
    players[1].playerID = 2;
    players[1].remainingBarriers = 10;

    int remainingTime = INITIAL_TIME;

    while (remainingTime > 0) {
        clearScreen(); // Effacer l'écran à chaque itération



        // Afficher le plateau et les informations des joueurs
        afficherPlateau();
        displayInfo(remainingTime, players);

        remainingTime--;
        sleep(1);
    }


    printf("Time's up!\n");
    return 0;
}
