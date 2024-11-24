#include <stdio.h>
#include "Plato.h"
#include "gameLoop.h"

void afficherRegles() {
    printf("\nPRESENTATION\n");
    printf("- un plateau de jeu;\n");
    printf("- 2 zones de stockage;\n");
    printf("- 20 barrières et 4 pions.\n");
    printf("BUT DU JEU\n");
    printf("Atteindre le premier la ligne opposée à sa ligne de départ.\n");
    printf("REGLE POUR 2 JOUEURS\n");
    printf("En début de partie, les barrières sont remisées dans leur zone de stockage (10 par joueur).\n");
    printf("Chaque joueur pose son pion au centre de sa ligne de départ.\n");
    printf("Un tirage au sort détermine qui commence.\n");
    printf("Déroulement d’une partie\n");
    printf("A tour de rôle, chaque joueur choisit de déplacer son pion ou de poser une de ses barrières.\n");
    printf("Lorsqu’il n’a plus de barrières, un joueur est obligé de déplacer son pion.\n");
    printf("Déplacement des pions:\n");
    printf("les pions se déplacent d’une case, horizontalement ou verticalement, en avant ou en arrière ; les barrières doivent être contournées.\n");
    printf("Pose des barrières:\n");
    printf("une barrière doit être posée exactement entre 2 cases .\n");
    printf("La pose des barrières a pour but de se créer son propre chemin ou de ralentir l’adversaire, mais il est interdit de lui fermer totalement l’accès à sa ligne de but: il faut toujours lui laisser une solution.\n");
    printf("Face à face:\n");
    printf("quand les 2 pions se retrouvent en vis-à-vis sur 2 cases voisines non séparées par une barrière, le joueur dont c’est le tour peut sauter son adversaire et se placer derrière lui .\n");
    printf("Si une barrière est située derrière le pion sauté, le joueur peut choisir de bifurquer à droite ou à gauche du pion sauté.\n");
    printf("FIN DE LA PARTIE\n");
    printf("Le premier joueur qui atteint une des 9 cases de la ligne opposée à sa ligne de départ gagne la partie.\n");
    printf("DUREE D’UNE PARTIE\n");
    printf("De 10 à 20 minutes.\n");
    printf("REGLE POUR 4 JOUEURS\n");
    printf("En début de partie, les 4 pions sont disposés au centre de chacun des 4 cotés du plateau et chaque joueur dispose de 5 barrières.\n");
    printf("Les règles sont strictement identiques, mais on ne peut sauter plus d’un pion à la fois .\n");
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
                afficherRegles();
                printf("\n2 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        afficherRegles();
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