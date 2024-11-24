#include "deplacement.h"
#include "Plato.h"
#include <stdio.h>
#include "Barriere.h"

// Fonction pour gérer le déplacement d'un joueur
void gererDeplacement(int *joueurX, int *joueurY, int joueurActuel) {
    char direction;    // Stocke la direction du déplacement (w/a/s/d)
    int deplacementValide = 0; // Indique si le déplacement est valide

    while (!deplacementValide) {
        // Demande au joueur d'entrer une direction
        printf("Entrez la direction (w/a/s/d) : ");
        scanf(" %c", &direction);

        // Initialise les nouvelles coordonnées du joueur
        int nouvelleX = *joueurX;
        int nouvelleY = *joueurY;

        // Met à jour les coordonnées en fonction de la direction
        switch (direction) {
            case 'w': nouvelleX--; break; // Déplacement vers le haut
            case 'a': nouvelleY--; break; // Déplacement vers la gauche
            case 's': nouvelleX++; break; // Déplacement vers le bas
            case 'd': nouvelleY++; break; // Déplacement vers la droite
            default:
                // Si la direction est invalide, afficher un message et recommencer
                printf("Direction invalide !\n");
                continue;
        }

        // Vérifie si le mouvement reste dans les limites du plateau
        if (nouvelleX >= 0 && nouvelleX < TAILLE && nouvelleY >= 0 && nouvelleY < TAILLE) {
            // Vérifie s'il y a une barrière bloquant le chemin dans la direction donnée
            if ((direction == 'w' && estBarrierePosee(*joueurX, *joueurY, 'H')) ||
                (direction == 's' && estBarrierePosee(nouvelleX, nouvelleY, 'H')) ||
                (direction == 'a' && estBarrierePosee(*joueurX, *joueurY, 'V')) ||
                (direction == 'd' && estBarrierePosee(*joueurX, nouvelleY, 'V'))) {
                printf("Vous ne pouvez pas vous déplacer dans cette direction ! Une barrière bloque le chemin.\n");
                continue;
            }

            // Gérer le cas où le joueur rencontre un adversaire face à lui
            if (plateau[nouvelleX][nouvelleY].joueur != 0) {
                // L'adversaire est directement devant
                int adversaireX = nouvelleX;
                int adversaireY = nouvelleY;
                int sautX = nouvelleX;
                int sautY = nouvelleY;

                // Calcule les coordonnées pour sauter par-dessus l'adversaire
                switch (direction) {
                    case 'w': sautX--; break; // Saut vers le haut
                    case 'a': sautY--; break; // Saut vers la gauche
                    case 's': sautX++; break; // Saut vers le bas
                    case 'd': sautY++; break; // Saut vers la droite
                }

                // Vérifie si le saut est possible (dans les limites et sans barrière)
                if (sautX >= 0 && sautX < TAILLE && sautY >= 0 && sautY < TAILLE &&
                    !estBarrierePosee(adversaireX, adversaireY, direction == 'w' || direction == 's' ? 'H' : 'V')) {
                    // Effectue le saut
                    nouvelleX = sautX;
                    nouvelleY = sautY;
                } else {
                    // Si le saut est bloqué, afficher un message et recommencer
                    printf("Vous ne pouvez pas sauter par-dessus l'adversaire ! Une barrière bloque le chemin.\n");
                    continue;
                }
            }

            // Met à jour le plateau après un mouvement valide
            plateau[*joueurX][*joueurY].joueur = 0; // Efface l'ancienne position du joueur
            plateau[nouvelleX][nouvelleY].joueur = joueurActuel; // Met à jour la nouvelle position
            *joueurX = nouvelleX; // Met à jour la coordonnée X du joueur
            *joueurY = nouvelleY; // Met à jour la coordonnée Y du joueur
            deplacementValide = 1; // Indique que le mouvement est valide
        } else {
            // Si le mouvement dépasse les limites du plateau
            printf("Déplacement hors limites !\n");
        }
    }
}