#include "gameLoop.h"
#include <stdio.h>
#include "Plato.h"
#include "deplacement.h"
#include "AfficheurPersonnaliser.h"
#include "Barriere.h"
#include "Victoire.h"
#include <string.h>
#include "handleRedo.h"

// Variables externes utilisées dans le programme
extern int barrierCount; // Nombre total de barrières
extern Player players[2]; // Liste des joueurs
extern Barriere barriers[]; // Tableau des barrières
extern Case plateau[TAILLE][TAILLE]; // Plateau de jeu
extern Case savedPlateau[TAILLE][TAILLE]; // Sauvegarde du plateau

// Fonction principale pour gérer le tour de jeu
void gameLoop() {
    // Position initiale des joueurs
    int playerX = 0, playerY = 4; // Joueur 1
    int player2X = 8, player2Y = 4; // Joueur 2

    int currentPlayer = 1; // Détermine le joueur en cours (1 ou 2)
    bool redoUsed = false; // Indique si le joueur a utilisé l'option "Redo" (annuler/refaire)

    // Variables pour stocker la dernière position et la dernière barrière
    int lastPlayerX, lastPlayerY, lastPlayer2X, lastPlayer2Y;
    int lastBarrierX, lastBarrierY;
    char lastBarrierType;

    // Boucle infinie jusqu'à la fin du jeu
    while (1) {
        afficherPlateau(); // Affiche le plateau de jeu
        printf("\n(0 to quit, 1 to skip, 2 to move, 3 to place barrier): ");
        printf("\nPlayer %d's turn. Enter command: ", currentPlayer);

        afficherAide(); // Affiche les instructions pour aider le joueur
        setCursorPosition(32, TAILLE + 13); // Positionne le curseur après le plateau pour éviter de décaler l'affichage

        int command;

        // Lire la commande du joueur et vérifier qu'elle est valide
        while (scanf("%d", &command) != 1 || (command < 0 || command > 3)) {
            printf("Invalid command! Please enter a valid command (0 to quit, 1 to skip, 2 to move, 3 to place barrier): ");
            while (getchar() != '\n'); // Vide le buffer d'entrée
        }

        if (command == 0) {
            break; // Quitter la boucle si le joueur entre 0
        } else if (command == 1) {
            // Passer le tour au joueur suivant
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
            redoUsed = false; // Réinitialiser le statut "Redo"
        } else if (command == 2) {
            // Enregistrer les positions actuelles avant le déplacement
            lastPlayerX = playerX;
            lastPlayerY = playerY;
            lastPlayer2X = player2X;
            lastPlayer2Y = player2Y;

            // Gérer le déplacement en fonction du joueur actuel
            if (currentPlayer == 1) {
                gererDeplacement(&playerX, &playerY, currentPlayer);
            } else {
                gererDeplacement(&player2X, &player2Y, currentPlayer);
            }

            // Mettre à jour le plateau avec la nouvelle position
            if (currentPlayer == 1) {
                plateau[playerX][playerY].joueur = 1;
            } else {
                plateau[player2X][player2Y].joueur = 2;
            }

            // Vérifier si le joueur actuel a gagné
            if ((currentPlayer == 1 && victoire(playerX, playerY, currentPlayer)) ||
                (currentPlayer == 2 && victoire(player2X, player2Y, currentPlayer))) {
                printf("Player %d wins!\n", currentPlayer);
                break; // Quitter la boucle si un joueur a gagné
            }

            // Gérer l'option "Redo" si elle est disponible
            if (!redoUsed) {
                handleRedo(&playerX, &playerY, &player2X, &player2Y, currentPlayer,
                           &redoUsed, lastPlayerX, lastPlayerY, lastPlayer2X, lastPlayer2Y, -1, -1, '\0');
                if (redoUsed) continue; // Recommencer le tour si "Redo" est utilisé
            }

            // Passer au joueur suivant
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
            redoUsed = false; // Réinitialiser le statut "Redo"
        } else if (command == 3) {
            // Poser une barrière
            int col, row;
            char orientation;

            // Demander au joueur où placer la barrière
            demanderBarriere(&col, &row, &orientation);

            // Enregistrer la position avant de poser la barrière
            lastBarrierX = col;
            lastBarrierY = row;
            lastBarrierType = orientation;

            // Gérer l'option "Redo" si elle est disponible
            if (!redoUsed) {
                handleRedo(&playerX, &playerY, &player2X, &player2Y, currentPlayer,
                           &redoUsed, -1, -1, -1, -1, lastBarrierX, lastBarrierY, lastBarrierType);
                if (redoUsed) continue; // Recommencer le tour si "Redo" est utilisé
            }

            // Poser la barrière
            poserBarriere(col, row, orientation);
            players[currentPlayer - 1].remainingBarriers--; // Décrémenter le nombre de barrières restantes

            // Passer au joueur suivant
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
            redoUsed = false; // Réinitialiser le statut "Redo"
        }
    }
}
