#include "gameLoop4Joueurs.h"
#include <stdio.h>
#include <stdlib.h>
#include "Plato.h"
#include "deplacement.h"
#include "AfficheurPersonnaliser.h"
#include "Barriere.h"
#include "Victoire.h"
#include <string.h>
#include "handleRedo.h"

// Variables externes déclarées dans d'autres fichiers
extern int barrierCount;
extern Player players[4];
extern Barriere barriers[];
extern Case plateau[TAILLE][TAILLE];
extern Case savedPlateau[TAILLE][TAILLE];

// Boucle principale pour un jeu avec 4 joueurs
void gameLoop4Joueurs() {
    // Positions initiales des joueurs sur le plateau
    int playerX[4] = {0, 8, 4, 4}; // Coordonnées X des joueurs 1 à 4
    int playerY[4] = {4, 4, 0, 8}; // Coordonnées Y des joueurs 1 à 4

    // Sélection aléatoire du joueur qui commence
    srand(time(NULL));
    int currentPlayer = (rand() % 4) + 1;

    bool redoUsed = false;         // Indique si une commande "redo" a été utilisée
    int lastPlayerX[4], lastPlayerY[4]; // Sauvegarde des dernières positions des joueurs
    int lastBarrierX, lastBarrierY;     // Sauvegarde des coordonnées de la dernière barrière placée
    char lastBarrierType;               // Sauvegarde du type (orientation) de la dernière barrière

    // Début de la boucle de jeu
    while (1) {
        afficherPlateau(); // Affiche l'état actuel du plateau

        // Options disponibles pour le joueur actif
        printf("\n(0 pour quitter, 1 pour passer, 2 pour déplacer, 3 pour poser une barrière) : ");
        printf("\nTour du joueur %d. Entrez la commande : ", currentPlayer);

        afficherAide(); // Affiche les règles et commandes du jeu
        setCursorPosition(32, TAILLE + 13); // Place le curseur sous le plateau pour les entrées utilisateur

        int command;

        // Validation de l'entrée utilisateur pour la commande
        while (scanf("%d", &command) != 1 || (command < 0 || command > 3)) {
            printf("Commande invalide ! Veuillez entrer une commande valide (0 pour quitter, 1 pour passer, 2 pour déplacer, 3 pour poser une barrière) : ");
            while (getchar() != '\n'); // Vide le tampon en cas d'entrée invalide
        }

        // Commande : quitter la partie
        if (command == 0) {
            break;
        }
        // Commande : passer son tour
        else if (command == 1) {
            currentPlayer = (currentPlayer % 4) + 1; // Passe au joueur suivant
            redoUsed = false; // Réinitialise le flag "redo"
        }
        // Commande : déplacer son pion
        else if (command == 2) {
            // Sauvegarde les positions actuelles des joueurs avant déplacement
            for (int i = 0; i < 4; i++) {
                lastPlayerX[i] = playerX[i];
                lastPlayerY[i] = playerY[i];
            }

            // Gère le déplacement du joueur actif
            gererDeplacement(&playerX[currentPlayer - 1], &playerY[currentPlayer - 1], currentPlayer);

            // Met à jour la position du joueur actif sur le plateau
            plateau[playerX[currentPlayer - 1]][playerY[currentPlayer - 1]].joueur = currentPlayer;

            // Vérifie si le joueur a gagné
            if (victoire(playerX[currentPlayer - 1], playerY[currentPlayer - 1], currentPlayer)) {
                printf("Le joueur %d gagne !\n", currentPlayer);
                break;
            }

            // Gestion de l'option "redo" (annulation du dernier mouvement)
            if (!redoUsed) {
                handleRedo(playerX, playerY, NULL, NULL, currentPlayer, &redoUsed,
                           lastPlayerX[currentPlayer - 1], lastPlayerY[currentPlayer - 1], -1, -1, -1, -1, '\0');
                if (redoUsed) continue; // Si "redo" est utilisé, passe au tour suivant
            }

            currentPlayer = (currentPlayer % 4) + 1; // Passe au joueur suivant
            redoUsed = false; // Réinitialise le flag "redo"
        }
        // Commande : placer une barrière
        else if (command == 3) {
            int col, row;
            char orientation;

            // Demande au joueur où placer la barrière
            demanderBarriere(&col, &row, &orientation);

            // Sauvegarde les informations de la barrière avant placement
            lastBarrierX = col;
            lastBarrierY = row;
            lastBarrierType = orientation;

            // Gestion de l'option "redo" pour le placement de barrière
            if (!redoUsed) {
                handleRedo(playerX, playerY, NULL, NULL, currentPlayer, &redoUsed,
                           -1, -1, -1, -1, lastBarrierX, lastBarrierY, lastBarrierType);
                if (redoUsed) continue; // Si "redo" est utilisé, passe au tour suivant
            }

            // Place la barrière sur le plateau
            poserBarriere(col, row, orientation);

            // Diminue le nombre de barrières restantes pour le joueur actif
            players[currentPlayer - 1].remainingBarriers--;

            currentPlayer = (currentPlayer % 4) + 1; // Passe au joueur suivant
            redoUsed = false; // Réinitialise le flag "redo"
        }
    }
}