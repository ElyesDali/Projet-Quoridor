#include "gameLoop.h"
#include <stdio.h>
#include "Plato.h"
#include "deplacement.h"
#include "AfficheurPersonnaliser.h"
#include "Barriere.h"
#include "Victoire.h"
#include <string.h>
#include "handleRedo.h"
#include <stdlib.h>
#include <time.h>

// Variables externes utilisées dans le programme
extern int barrierCount; // Nombre total de barrières
extern Player players[2]; // Liste des joueurs
extern Barriere barriers[]; // Tableau des barrières
extern Case plateau[TAILLE][TAILLE]; // Plateau de jeu
extern Case savedPlateau[TAILLE][TAILLE]; // Sauvegarde du plateau

// Fonction principale pour gérer le tour de jeu
void boucleDeJeu() {
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Initialiser les positions des joueurs
    int joueurX = 0, joueurY = 4;
    int joueur2X = 8, joueur2Y = 4;

    // Sélectionner aléatoirement le joueur qui commence
    int joueurActuel = (rand() % 2) + 1;
    bool redoUtilise = false;

    // Variables pour stocker la dernière position et la dernière barrière
    int dernierJoueurX, dernierJoueurY, dernierJoueur2X, dernierJoueur2Y;
    int derniereBarriereX, derniereBarriereY;
    char derniereBarriereType;

    // Boucle de jeu
    while (1) {
        afficherPlateau(); // Afficher l'état actuel du plateau
        printf("\n(0 pour quitter, 1 pour passer, 2 pour déplacer, 3 pour poser une barrière) : ");
        printf("\nTour du joueur %d. Entrez la commande : ", joueurActuel);

        afficherAide(); // Afficher les règles et commandes du jeu
        setCursorPosition(32, TAILLE + 13); // Positionner le curseur sous le plateau pour les entrées utilisateur

        int commande;

        // Valider l'entrée utilisateur pour la commande
        while (scanf("%d", &commande) != 1 || (commande < 0 || commande > 3)) {
            printf("Commande invalide ! Veuillez entrer une commande valide (0 pour quitter, 1 pour passer, 2 pour déplacer, 3 pour poser une barrière) : ");
            while (getchar() != '\n'); // Vider le tampon en cas d'entrée invalide
        }

        // Commande : quitter la partie
        if (commande == 0) {
            break;
        }
        // Commande : passer son tour
        else if (commande == 1) {
            joueurActuel = (joueurActuel == 1) ? 2 : 1; // Passer au joueur suivant
            redoUtilise = false; // Réinitialiser le flag "redo"
        }
        // Commande : déplacer son pion
        else if (commande == 2) {
            // Sauvegarder les positions actuelles avant de déplacer
            dernierJoueurX = joueurX;
            dernierJoueurY = joueurY;
            dernierJoueur2X = joueur2X;
            dernierJoueur2Y = joueur2Y;

            // Gérer le déplacement en fonction du joueur actuel
            if (joueurActuel == 1) {
                gererDeplacement(&joueurX, &joueurY, joueurActuel);
            } else {
                gererDeplacement(&joueur2X, &joueur2Y, joueurActuel);
            }

            // Mettre à jour le plateau avec la nouvelle position
            if (joueurActuel == 1) {
                plateau[joueurX][joueurY].joueur = 1;
            } else {
                plateau[joueur2X][joueur2Y].joueur = 2;
            }

            // Vérifier si le joueur actuel a gagné
            if ((joueurActuel == 1 && victoire(joueurX, joueurY, joueurActuel)) ||
                (joueurActuel == 2 && victoire(joueur2X, joueur2Y, joueurActuel))) {
                printf("Le joueur %d gagne !\n", joueurActuel);
                break; // Sortir de la boucle si un joueur a gagné
            }

            // Gérer l'option "redo" si disponible
            if (!redoUtilise) {
                handleRedo(&joueurX, &joueurY, &joueur2X, &joueur2Y, joueurActuel,
                           &redoUtilise, dernierJoueurX, dernierJoueurY, dernierJoueur2X, dernierJoueur2Y, -1, -1, '\0');
                if (redoUtilise) continue; // Recommencer le tour si "redo" est utilisé
            }

            // Passer au joueur suivant
            joueurActuel = (joueurActuel == 1) ? 2 : 1;
            redoUtilise = false; // Réinitialiser le flag "redo"
        }
        // Commande : placer une barrière
        else if (commande == 3) {
            int col, row;
            char orientation;

            // Demander au joueur où placer la barrière
            demanderBarriere(&col, &row, &orientation);

            // Sauvegarder la position avant de placer la barrière
            derniereBarriereX = col;
            derniereBarriereY = row;
            derniereBarriereType = orientation;

            // Gérer l'option "redo" si disponible
            if (!redoUtilise) {
                handleRedo(&joueurX, &joueurY, &joueur2X, &joueur2Y, joueurActuel,
                           &redoUtilise, -1, -1, -1, -1, derniereBarriereX, derniereBarriereY, derniereBarriereType);
                if (redoUtilise) continue; // Recommencer le tour si "redo" est utilisé
            }

            // Placer la barrière
            poserBarriere(col, row, orientation);
            players[joueurActuel - 1].remainingBarriers--; // Diminuer le nombre de barrières restantes

            // Passer au joueur suivant
            joueurActuel = (joueurActuel == 1) ? 2 : 1;
            redoUtilise = false; // Réinitialiser le flag "redo"
        }
    }
}