#include "gameLoop.h"
#include <stdio.h>
#include "Plato.h"
#include "deplacement.h"
#include "AfficheurPersonnaliser.h"
#include "Barriere.h"
#include "Victoire.h"
#include <string.h> // Include for memcpy

extern int barrierCount;
extern Player players[2];
extern Barriere barriers[];
extern Case plateau[TAILLE][TAILLE];
extern Case savedPlateau[TAILLE][TAILLE];

void gameLoop() {
    int playerX = 0, playerY = 4; // Initial position of player 1
    int player2X = 8, player2Y = 4; // Initial position of player 2
    int currentPlayer = 1;
    bool redoUsed = false;
    int lastPlayerX, lastPlayerY, lastPlayer2X, lastPlayer2Y;
    int lastBarrierX, lastBarrierY;
    char lastBarrierType;

    while (1) {
        afficherPlateau();
        printf("\n(0 to quit, 1 to skip, 2 to move, 3 to place barrier): ");
        printf("\nPlayer %d's turn. Enter command: ", currentPlayer);
        afficherAide(); // Call the new function to display the help text
        setCursorPosition(32, TAILLE + 13); // Ensure the prompt is below the board

        int command;
        while (scanf("%d", &command) != 1 || (command < 0 || command > 3)) {
            printf("Invalid command! Please enter a valid command (0 to quit, 1 to skip, 2 to move, 3 to place barrier): ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        if (command == 0) {
            break;
        } else if (command == 1) {
            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Skip turn
            redoUsed = false; // Reset redo flag for the next player
        } else if (command == 2) {
            // Save current positions before moving
            lastPlayerX = playerX;
            lastPlayerY = playerY;
            lastPlayer2X = player2X;
            lastPlayer2Y = player2Y;

            if (currentPlayer == 1) {
                gererDeplacement(&playerX, &playerY, currentPlayer);
            } else {
                gererDeplacement(&player2X, &player2Y, currentPlayer);
            }

            // Update the board with the new position
            if (currentPlayer == 1) {
                plateau[playerX][playerY].joueur = 1;
            } else {
                plateau[player2X][player2Y].joueur = 2;
            }

            // Check for victory
            if ((currentPlayer == 1 && victoire(playerX, playerY, currentPlayer)) ||
                (currentPlayer == 2 && victoire(player2X, player2Y, currentPlayer))) {
                printf("Player %d wins!\n", currentPlayer);
                break;
            }

            // Handle redo
            if (!redoUsed) {
                handleRedo(&playerX, &playerY, &player2X, &player2Y, currentPlayer, &redoUsed, lastPlayerX, lastPlayerY, lastPlayer2X, lastPlayer2Y, -1, -1, '\0');
                if (redoUsed) continue;
            }
            currentPlayer = (currentPlayer == 1) ? 2 : 1; // End turn
            redoUsed = false; // Reset redo flag for the next player
        } else if (command == 3) {
            // Ask where to place the barrier
            int col, row;
            char orientation;
            demanderBarriere(&col, &row, &orientation);

            // Save the barrier position before placing
            lastBarrierX = col;
            lastBarrierY = row;
            lastBarrierType = orientation;

            // Handle redo
            if (!redoUsed) {
                handleRedo(&playerX, &playerY, &player2X, &player2Y, currentPlayer, &redoUsed, -1, -1, -1, -1, lastBarrierX, lastBarrierY, lastBarrierType);
                if (redoUsed) continue;
            }

            // Place barrier
            poserBarriere(col, row, orientation);
            players[currentPlayer - 1].remainingBarriers--; // Decrement the player's remaining barriers

            currentPlayer = (currentPlayer == 1) ? 2 : 1; // End turn
            redoUsed = false; // Reset redo flag for the next player
        }
    }
}

void handleRedo(int *playerX, int *playerY, int *player2X, int *player2Y, int currentPlayer, bool *redoUsed, int lastPlayerX, int lastPlayerY, int lastPlayer2X, int lastPlayer2Y, int lastBarrierX, int lastBarrierY, char lastBarrierType) {
    if (*redoUsed) {
        printf("Redo has already been used this turn.\n");
        return;
    }

    printf("\nPlayer %d, do you want to redo your move? (1 for yes, 0 for no): ", currentPlayer);
    int redo;
    while (scanf("%d", &redo) != 1 || (redo < 0 || redo > 1)) {
        printf("Invalid command! Please enter 1 for yes or 0 for no: ");
        while (getchar() != '\n'); // Clear the input buffer
    }
    if (redo == 1) {
        // Restore the previous state of the board
        memcpy(plateau, savedPlateau, sizeof(plateau));

        // Restore the previous position if it was a move
        if (lastPlayerX != -1 && lastPlayerY != -1) {
            if (currentPlayer == 1) {
                *playerX = lastPlayerX;
                *playerY = lastPlayerY;
            } else {
                *player2X = lastPlayer2X;
                *player2Y = lastPlayer2Y;
            }
        } else if (lastBarrierX != -1 && lastBarrierY != -1) {
            // Remove the placed barrier
            if (barrierCount > 0) {
                barrierCount--;
                players[currentPlayer - 1].remainingBarriers++; // Increment the player's remaining barriers
                barriers[barrierCount].x = -1; // Invalidate the last barrier
                barriers[barrierCount].y = -1;
                barriers[barrierCount].type = '\0';

                // Restore the board state by removing the barrier
                if (lastBarrierType == 'H') {
                    plateau[lastBarrierX][lastBarrierY].joueur = 0;
                    plateau[lastBarrierX][lastBarrierY + 1].joueur = 0;
                } else if (lastBarrierType == 'V') {
                    plateau[lastBarrierX][lastBarrierY].joueur = 0;
                    plateau[lastBarrierX + 1][lastBarrierY].joueur = 0;
                }
            }
        }

        // Ensure both players' positions are correctly updated on the board
        plateau[*playerX][*playerY].joueur = 1;
        plateau[*player2X][*player2Y].joueur = 2;

        afficherPlateau();
        *redoUsed = true;
    }
}