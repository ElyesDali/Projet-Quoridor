#include <stdio.h>
#include "Plato.h"
#include "deplacement.h"
#include "AfficheurPersonnaliser.h"
#include "Barriere.h"
#include "Victoire.h"

extern int barrierCount; // Add this line to declare barrierCount
extern Player players[2]; // Add this line to declare players

void gameLoop() {
    int playerX = 0, playerY = 4; // Initial position of player 1
    int player2X = 8, player2Y = 4; // Initial position of player 2
    int currentPlayer = 1;
    int lastPlayerX, lastPlayerY, lastPlayer2X, lastPlayer2Y;
    int lastPlayer = 1;

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
        } else if (command == 2) {
            // Save current positions before moving
            lastPlayerX = playerX;
            lastPlayerY = playerY;
            lastPlayer2X = player2X;
            lastPlayer2Y = player2Y;
            lastPlayer = currentPlayer;

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

            // Ask if the player wants to redo their move after moving
            printf("\nPlayer %d, do you want to redo your move? (1 for yes, 0 for no): ", currentPlayer);
            int redo;
            while (scanf("%d", &redo) != 1 || (redo < 0 || redo > 1)) {
                printf("Invalid command! Please enter 1 for yes or 0 for no: ");
                while (getchar() != '\n'); // Clear the input buffer
            }
            if (redo == 1) {
                // Restore the previous position
                if (currentPlayer == 1) {
                    plateau[playerX][playerY].joueur = 0;
                    playerX = lastPlayerX;
                    playerY = lastPlayerY;
                } else {
                    plateau[player2X][player2Y].joueur = 0;
                    player2X = lastPlayer2X;
                    player2Y = lastPlayer2Y;
                }
                // Redo the move
                if (currentPlayer == 1) {
                    gererDeplacement(&playerX, &playerY, currentPlayer);
                } else {
                    gererDeplacement(&player2X, &player2Y, currentPlayer);
                }

                // Update the board with the new position again
                if (currentPlayer == 1) {
                    plateau[playerX][playerY].joueur = 1;
                } else {
                    plateau[player2X][player2Y].joueur = 2;
                }

                // Check for victory again after redo
                if ((currentPlayer == 1 && victoire(playerX, playerY, currentPlayer)) ||
                    (currentPlayer == 2 && victoire(player2X, player2Y, currentPlayer))) {
                    printf("Player %d wins!\n", currentPlayer);
                    break;
                }
            }
            currentPlayer = (currentPlayer == 1) ? 2 : 1; // End turn
        } else if (command == 3) {
            // Place barrier
            int col, row;
            char orientation;
            demanderBarriere(&col, &row, &orientation);
            poserBarriere(col, row, orientation);
            players[currentPlayer - 1].remainingBarriers--; // Decrement the player's remaining barriers

            // Ask if the player wants to redo their move after placing a barrier
            printf("\nPlayer %d, do you want to redo your move? (1 for yes, 0 for no): ", currentPlayer);
            int redo;
            while (scanf("%d", &redo) != 1 || (redo < 0 || redo > 1)) {
                printf("Invalid command! Please enter 1 for yes or 0 for no: ");
                while (getchar() != '\n'); // Clear the input buffer
            }
            if (redo == 1) {
                // Remove the placed barrier
                barrierCount--;
                players[currentPlayer - 1].remainingBarriers++; // Increment the player's remaining barriers
                // Redo the barrier placement
                demanderBarriere(&col, &row, &orientation);
                poserBarriere(col, row, orientation);
                players[currentPlayer - 1].remainingBarriers--; // Decrement the player's remaining barriers
            }
            currentPlayer = (currentPlayer == 1) ? 2 : 1; // End turn
        }
    }
}
int menu() {
    int choix = 0;

    while (1) {
        printf("\nQUORIDOR\n");
        printf("\n");
        printf("1 : Jouer\n");
        printf("2 : Reprendre une partie\n");
        printf("3 : Aide\n");
        printf("4 : Tableau des scores\n");
        printf("5 : Quitter\n");
        printf("\nChoix : ");

        scanf("%d", &choix);

        switch (choix) {
            case 1: // Jouer
                printf("\nCHOISIR LE MODE DE JEU\n");
                printf("\n1 : Normal\n");
                printf("2 : Blitz\n");
                printf("3 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);

                switch (choix) {
                    case 1:
                    case 2:
                        printf("Mode sélectionné.\n");
                        initialiserPlateau();
                        gameLoop();
                        break;
                    case 3:
                        break;
                    default:
                        printf("Choix invalide.\n");
                    break;
                }
                break;

            case 2: // Reprendre une partie
                printf("1 : Reprendre une partie\n");
                printf("2 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        printf("Reprendre une partie.\n");
                        initialiserPlateau();
                        gameLoop();
                        break;
                    case 2:
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 3: // Aide
                printf("1 : Règles à mettre après\n");
                printf("2 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        printf("Règles à mettre après.\n");
                        break;
                    case 2:
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 4: // Tableau des scores
                printf("1 : Tableau des scores\n");
                printf("2 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        printf("Tableau des scores.\n");
                        break;
                    case 2:
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 5: // Quitter
                printf("Quitter le jeu.\n");
                return 0;

            default: // Choix invalide
                printf("Choix invalide.\n");
        }
    }
    return 0;
}