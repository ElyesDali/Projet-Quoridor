#include "handleRedo.h"  // Inclusion de l'en-tête pour la gestion du redo (annuler/rehabiter un mouvement)
#include "Plato.h"        // Inclusion de l'en-tête pour la gestion du plateau de jeu
#include <stdio.h>        // Inclusion de la bibliothèque standard pour les entrées/sorties
#include <string.h>       // Inclusion de la bibliothèque pour manipuler les chaînes de caractères
#include <stdbool.h>      // Inclusion de la bibliothèque pour utiliser les types booléens

// Déclarations externes des variables définies ailleurs
extern Case plateau[TAILLE][TAILLE];       // Plateau de jeu actuel
extern Case savedPlateau[TAILLE][TAILLE]; // Sauvegarde de l'état précédent du plateau
extern int barrierCount;                  // Compteur des barrières restantes
extern Player players[];                  // Liste des joueurs

// Fonction pour gérer l'option "redo" (annuler le dernier mouvement et le refaire)
void handleRedo(int *playerX, int *playerY, int *player2X, int *player2Y, int currentPlayer, bool *redoUsed,
                int lastPlayerX, int lastPlayerY, int lastPlayer2X, int lastPlayer2Y,
                int lastBarrierX, int lastBarrierY, char lastBarrierType) {

    // Vérifie si l'option "redo" a déjà été utilisée lors de ce tour
    if (*redoUsed) {
        printf("Redo has already been used this turn.\n");  // Message si le redo a déjà été utilisé
        return; // Sortie de la fonction si "redo" a déjà été utilisé
    }

    // Demande au joueur s'il souhaite utiliser "redo"
    printf("\nPlayer %d, do you want to redo your move? (1 for yes, 0 for no): ", currentPlayer);
    int redo;  // Variable pour stocker la réponse du joueur
    while (scanf("%d", &redo) != 1 || (redo < 0 || redo > 1)) {  // Vérifie si l'entrée est valide (1 ou 0)
        printf("Invalid command! Please enter 1 for yes or 0 for no: ");  // Message d'erreur pour entrée invalide
        while (getchar() != '\n'); // Vide le tampon en cas d'entrée invalide
    }

    // Si le joueur choisit de refaire son mouvement
    if (redo == 1) {
        // Restauration de l'état précédent du plateau
        memcpy(plateau, savedPlateau, sizeof(plateau));  // Copie le plateau sauvegardé dans le plateau actuel

        // Restaure la position précédente du joueur si un mouvement a été effectué
        *playerX = lastPlayerX;
        *playerY = lastPlayerY;
        *player2X = lastPlayer2X;
        *player2Y = lastPlayer2Y;

        // Met à jour les positions des joueurs sur le plateau
        plateau[*playerX][*playerY].joueur = 1;  // Mise à jour de la position du joueur 1
        plateau[*player2X][*player2Y].joueur = 2; // Mise à jour de la position du joueur 2

        afficherPlateau();  // Affiche le plateau mis à jour
        *redoUsed = true;   // Marque que "redo" a été utilisé
    }
}
