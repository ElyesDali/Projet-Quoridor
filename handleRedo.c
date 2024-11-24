#include "handleRedo.h"
#include "Plato.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Variables externes déclarées dans d'autres fichiers
extern Case plateau[TAILLE][TAILLE];       // Plateau de jeu actuel
extern Case savedPlateau[TAILLE][TAILLE]; // Sauvegarde de l'état précédent du plateau
extern int barrierCount;                  // Compteur des barrières restantes
extern Player players[];                  // Liste des joueurs

// Fonction pour gérer l'option "redo" (annulation du dernier mouvement ou placement)
void handleRedo(int *playerX, int *playerY, int *player2X, int *player2Y, int currentPlayer,
                bool *redoUsed, int lastPlayerX, int lastPlayerY,
                int lastPlayer2X, int lastPlayer2Y,
                int lastBarrierX, int lastBarrierY, char lastBarrierType) {
    // Vérifie si le "redo" a déjà été utilisé lors de ce tour
    if (*redoUsed) {
        printf("Redo has already been used this turn.\n");
        return;
    }

    // Demande au joueur s'il souhaite utiliser "redo"
    printf("\nPlayer %d, do you want to redo your move? (1 for yes, 0 for no): ", currentPlayer);
    int redo;
    while (scanf("%d", &redo) != 1 || (redo < 0 || redo > 1)) {
        printf("Invalid command! Please enter 1 for yes or 0 for no: ");
        while (getchar() != '\n'); // Vide le tampon en cas d'entrée invalide
    }

    // Si le joueur choisit "redo"
    if (redo == 1) {
        // Restauration de l'état précédent du plateau
        memcpy(plateau, savedPlateau, sizeof(plateau));

        // Si un mouvement a été effectué, restaure les positions des joueurs
        if (lastPlayerX != -1 && lastPlayerY != -1) {
            *playerX = lastPlayerX;
            *playerY = lastPlayerY;
            plateau[*playerX][*playerY].joueur = currentPlayer; // Met à jour la position sur le plateau
        }

        if (player2X && player2Y && lastPlayer2X != -1 && lastPlayer2Y != -1) {
            *player2X = lastPlayer2X;
            *player2Y = lastPlayer2Y;
            plateau[*player2X][*player2Y].joueur = (currentPlayer % 4) + 1; // Met à jour la position du second joueur
        }

        // Si une barrière a été posée, restaure son état
        if (lastBarrierX != -1 && lastBarrierY != -1) {
            retirerBarriere(lastBarrierX, lastBarrierY, lastBarrierType); // Fonction à définir pour retirer une barrière
            players[currentPlayer - 1].remainingBarriers++; // Restaure une barrière au joueur
        }

        // Affiche le plateau mis à jour
        afficherPlateau();

        // Marque le "redo" comme utilisé pour ce tour
        *redoUsed = true;
    }
}
