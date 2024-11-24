#include "Plato.h"
#include <stdio.h>
#include <stdlib.h>
#include "Barriere.h"

// Déclaration des variables globales
Case plateau[TAILLE][TAILLE];          // Représente le plateau de jeu avec des cases
Case savedPlateau[TAILLE][TAILLE];    // Sauvegarde l'état précédent du plateau pour pouvoir revenir en arrière
Barriere barriers[TAILLE * TAILLE];    // Tableau pour les barrières placées sur le plateau
int barrierCount = 0;                  // Compte le nombre de barrières placées
Player players[2];                     // Tableau des joueurs (ici seulement 2 joueurs pour l'instant)

// Fonction d'initialisation du plateau selon le mode de jeu
void initialiserPlateau(int mode) {
    // Réinitialisation du plateau en mettant les joueurs à la position 0 (aucun joueur)
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j].joueur = 0;  // 0 signifie qu'il n'y a pas de joueur dans cette case
        }
    }

    // Si le mode de jeu est à 2 joueurs
    if (mode == 2) {
        plateau[0][4].joueur = 1;  // Le joueur 1 commence à la position (0, 4)
        plateau[8][4].joueur = 2;  // Le joueur 2 commence à la position (8, 4)
    }
    // Si le mode de jeu est à 4 joueurs
    else if (mode == 4) {
        plateau[0][4].joueur = 1;  // Le joueur 1 commence à la position (0, 4)
        plateau[8][4].joueur = 2;  // Le joueur 2 commence à la position (8, 4)
        plateau[4][0].joueur = 3;  // Le joueur 3 commence à la position (4, 0)
        plateau[4][8].joueur = 4;  // Le joueur 4 commence à la position (4, 8)
    }
}

// Fonction pour nettoyer l'écran en fonction du système d'exploitation
void clearScreen() {
#ifdef _WIN32
    system("cls");  // Si l'OS est Windows, utiliser la commande "cls"
#else
    system("clear");  // Sinon, utiliser "clear" (généralement sur Linux ou macOS)
#endif
}

// Affichage des informations du jeu : barre de temps et état des barrières des joueurs
void displayInfo(int remainingTime, Player players[]) {
    printf("  ---- PLAYER INFO ----\n");
    printf("  Player 1: Barriers: %d\n", players[0].remainingBarriers);  // Affiche le nombre de barrières restantes du joueur 1
    printf("  Player 2: Barriers: %d\n", players[1].remainingBarriers);  // Affiche le nombre de barrières restantes du joueur 2
    printf("  Time Remaining: %02d:%02d\n", remainingTime / 60, remainingTime % 60);  // Affiche le temps restant
    printf("  ---------------------\n");
}

// Fonction pour afficher l'état actuel du plateau de jeu avec les joueurs et les barrières
void afficherPlateau() {
    clearScreen();  // Nettoie l'écran avant d'afficher le plateau
    printf("   ");
    // Affiche les indices des colonnes
    for (int i = 0; i < TAILLE; i++) {
        printf("  %d ", i);
    }
    printf("\n");

    // Affiche le plateau ligne par ligne
    for (int i = 0; i < TAILLE; i++) {
        printf("   ");
        // Affiche les bordures horizontales du plateau
        for (int j = 0; j < TAILLE; j++) {
            if (estBarrierePosee(i, j, 'H') || (i == 0)) {
                printf("+###");  // Barrière horizontale
            } else {
                printf("+---");  // Case vide sans barrière
            }
        }
        printf("+\n");
        printf(" %d ", i);
        for (int j = 0; j < TAILLE; j++) {
            if (estBarrierePosee(i, j, 'V') || (j == 0)) {
                printf("#");  // Barrière verticale
            } else {
                printf("|");  // Séparateur entre les cases
            }

            // Affiche les joueurs dans leurs cases respectives
            if (plateau[i][j].joueur == 1) {
                printf(" 1 ");  // Le joueur 1
            } else if (plateau[i][j].joueur == 2) {
                printf(" 2 ");  // Le joueur 2
            } else if (plateau[i][j].joueur == 3) {
                printf(" 3 ");  // Le joueur 3
            } else if (plateau[i][j].joueur == 4) {
                printf(" 4 ");  // Le joueur 4
            } else {
                printf("   ");  // Case vide sans joueur
            }
        }
        printf("#\n");
    }
    printf("   ");
    // Affiche les bordures du bas du plateau
    for (int j = 0; j < TAILLE; j++) {
        printf("+###");
    }
    printf("+\n");
}
