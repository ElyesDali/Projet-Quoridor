#include <stdio.h>
#include "Plato.h"
#include "deplacement.h"

#include <stdio.h>
#include "Plato.h"
#include "deplacement.h"

void gameLoop() {
    int playerX = 0, playerY = 4; // Initial position of player 1
    int player2X = 9, player2Y = 4; // Initial position of player 2
    int currentPlayer = 1;

    while (1) {
        afficherPlateau();
        printf("\nPlayer %d's turn. Enter command (0 to quit): ", currentPlayer);
        int command;
        scanf("%d", &command);
        if (command == 0) {
            break;
        }

        if (currentPlayer == 1) {
            gererDeplacement(&playerX, &playerY, currentPlayer);
            currentPlayer = 2;
        } else {
            gererDeplacement(&player2X, &player2Y, currentPlayer);
            currentPlayer = 1;
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
