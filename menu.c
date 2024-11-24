#include <stdio.h>
#include "Plato.h"
#include "gameLoop.h"


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

                if (choix == 1 || choix == 2) {
                    int mode = choix;
                    printf("\n1 : 4 Joueurs\n");
                    printf("2 : 2 Joueurs\n");
                    printf("3 : Retour\n");
                    printf("\nChoix : ");
                    scanf("%d", &choix);

                    switch (choix) {
                        case 1:
                            printf("Mode 4 Joueurs sélectionné.\n");
                            //initialiserPlateau4Joueurs(); // Initialize the board for 4 players
                            if (mode == 1) {
                               // gameLoop4Joueurs(); // Start the game loop for 4 players in Normal mode
                            } else {
                              //  gameLoop4JoueursBlitz(); // Start the game loop for 4 players in Blitz mode
                            }
                            break;
                        case 2:
                            printf("Mode 2 Joueurs sélectionné.\n");
                            initialiserPlateau();
                            if (mode == 1) {
                                gameLoop(); // Start the game loop for 2 players in Normal mode
                            } else {
                               // gameLoopBlitz(); // Start the game loop for 2 players in Blitz mode
                            }
                            break;
                        case 3:
                            break;
                        default:
                            printf("Choix invalide.\n");
                            break;
                    }
                } else if (choix == 3) {
                    break;
                } else {
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