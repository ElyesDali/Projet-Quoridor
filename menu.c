#include <stdio.h>
#include "Plato.h"
#include "gameLoop.h"
#include "gameLoop4Joueurs.h"

// Fonction pour afficher les règles du jeu
void afficherRegles() {
    // Présentation du matériel et des objectifs du jeu
    printf("\nPRESENTATION\n");
    printf("- un plateau de jeu;\n");
    printf("- 2 zones de stockage;\n");
    printf("- 20 barrières et 4 pions.\n");

    // Objectif principal
    printf("BUT DU JEU\n");
    printf("Atteindre le premier la ligne opposée à sa ligne de départ.\n");

    // Règles pour le mode 2 joueurs
    printf("REGLE POUR 2 JOUEURS\n");
    printf("En début de partie, les barrières sont remisées dans leur zone de stockage (10 par joueur).\n");
    printf("Chaque joueur pose son pion au centre de sa ligne de départ.\n");
    printf("Un tirage au sort détermine qui commence.\n");

    // Explications détaillées du déroulement d'une partie
    printf("Déroulement d’une partie\n");
    printf("A tour de rôle, chaque joueur choisit de déplacer son pion ou de poser une de ses barrières.\n");
    printf("Lorsqu’il n’a plus de barrières, un joueur est obligé de déplacer son pion.\n");

    // Déplacements possibles des pions
    printf("Déplacement des pions:\n");
    printf("les pions se déplacent d’une case, horizontalement ou verticalement, en avant ou en arrière ; les barrières doivent être contournées.\n");

    // Règles pour poser des barrières
    printf("Pose des barrières:\n");
    printf("une barrière doit être posée exactement entre 2 cases .\n");
    printf("La pose des barrières a pour but de se créer son propre chemin ou de ralentir l’adversaire, mais il est interdit de lui fermer totalement l’accès à sa ligne de but: il faut toujours lui laisser une solution.\n");

    // Gestion des cas où deux pions se font face
    printf("Face à face:\n");
    printf("quand les 2 pions se retrouvent en vis-à-vis sur 2 cases voisines non séparées par une barrière, le joueur dont c’est le tour peut sauter son adversaire et se placer derrière lui .\n");
    printf("Si une barrière est située derrière le pion sauté, le joueur peut choisir de bifurquer à droite ou à gauche du pion sauté.\n");

    // Fin de partie et conditions de victoire
    printf("FIN DE LA PARTIE\n");
    printf("Le premier joueur qui atteint une des 9 cases de la ligne opposée à sa ligne de départ gagne la partie.\n");

    // Informations sur la durée moyenne d'une partie
    printf("DUREE D’UNE PARTIE\n");
    printf("De 10 à 20 minutes.\n");

    // Règles spécifiques pour le mode 4 joueurs
    printf("REGLE POUR 4 JOUEURS\n");
    printf("En début de partie, les 4 pions sont disposés au centre de chacun des 4 cotés du plateau et chaque joueur dispose de 5 barrières.\n");
    printf("Les règles sont strictement identiques, mais on ne peut sauter plus d’un pion à la fois .\n");
}

// Fonction principale pour le menu du jeu
int menu() {
    int choix = 0; // Variable pour stocker le choix de l'utilisateur

    while (1) { // Boucle infinie pour maintenir le menu actif
        // Affichage des options principales du menu
        printf("\nQUORIDOR\n");
        printf("\n");
        printf("1 : Jouer\n");
        printf("2 : Reprendre une partie\n");
        printf("3 : Aide\n");
        printf("4 : Tableau des scores\n");
        printf("5 : Quitter\n");
        printf("\nChoix : ");

        scanf("%d", &choix); // Lecture du choix de l'utilisateur

        // Gestion des différents choix possibles
        switch (choix) {
            case 1: // Option "Jouer"
                printf("\nCHOISIR LE MODE DE JEU\n");
                printf("\n1 : Normal\n");
                printf("2 : Blitz\n");
                printf("3 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);

                if (choix == 1 || choix == 2) { // Modes "Normal" ou "Blitz"
                    int mode = choix; // Stocke le mode choisi
                    printf("\n1 : 4 Joueurs\n");
                    printf("2 : 2 Joueurs\n");
                    printf("3 : Retour\n");
                    printf("\nChoix : ");
                    scanf("%d", &choix);

                    switch (choix) {
                        case 1: // Mode 4 joueurs
                            printf("Mode 4 Joueurs sélectionné.\n");
                            initialiserPlateau(4); // Initialisation pour 4 joueurs
                            if (mode == 1) {
                                gameLoop4Joueurs(); // Boucle de jeu pour 4 joueurs en mode normal
                            } else {
                                // gameLoop4JoueursBlitz(); // Boucle de jeu pour 4 joueurs en mode blitz (non implémentée)
                            }
                            break;
                        case 2: // Mode 2 joueurs
                            printf("Mode 2 Joueurs sélectionné.\n");
                            initialiserPlateau(2); // Initialisation pour 2 joueurs
                            if (mode == 1) {
                                gameLoop(); // Boucle de jeu pour 2 joueurs en mode normal
                            } else {
                                // gameLoopBlitz(); // Boucle de jeu pour 2 joueurs en mode blitz (non implémentée)
                            }
                            break;
                        case 3: // Retour au menu précédent
                            break;
                        default:
                            printf("Choix invalide.\n");
                            break;
                    }
                } else if (choix == 3) { // Retour au menu principal
                    break;
                } else {
                    printf("Choix invalide.\n");
                }
                break;

            case 2: // Option "Reprendre une partie"
                printf("1 : Reprendre une partie\n");
                printf("2 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1: // Charger une partie sauvegardée
                        printf("Reprendre une partie.\n");
                        initialiserPlateau(2); // Initialise le plateau
                        gameLoop(); // Lance la boucle de jeu
                        break;
                    case 2: // Retour au menu principal
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 3: // Option "Aide"
                afficherRegles(); // Affiche les règles du jeu
                printf("\n2 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1: // Réaffiche les règles (redondant ici)
                        afficherRegles();
                        break;
                    case 2: // Retour au menu principal
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 4: // Option "Tableau des scores"
                printf("1 : Tableau des scores\n");
                printf("2 : Retour\n");
                printf("\nChoix : ");
                scanf("%d", &choix);
                switch (choix) {
                    case 1: // Afficher le tableau des scores (fonctionnalité à implémenter)
                        printf("Tableau des scores.\n");
                        break;
                    case 2: // Retour au menu principal
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;

            case 5: // Option "Quitter"
                printf("Quitter le jeu.\n");
                return 0; // Quitte le programme

            default: // Gestion des choix invalides
                printf("Choix invalide.\n");
        }
    }
    return 0; // Retourne 0 par défaut (inaccessible ici à cause de la boucle infinie)
}
}