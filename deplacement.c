#define PLATO_H

void deplacerJoueur(int *x, int *y, int dx, int dy) {
    int newX = *x + dx;
    int newY = *y + dy;

    // Vérifiez si le nouveau mouvement est dans les limites du plateau
    if (newX >= 0 && newX < TAILLE && newY >= 0 && newY < TAILLE) {     //c'est une règle, on le remplacera par la fonction plus tard,
                                                                        //pas sortir des limitation, vu que les bord du plato sont considéré comme des barrière alors 
                                                                        //elle sera la même que celle pour pas sauter au dessus d'une
        // Vérifiez si la case est vide
        if (plateau[newX][newY].joueur == 0) {                          //c'est une règle, on le remplacera par la fonction plus tard, pas aller sur la case où le joueur est )
            plateau[*x][*y].joueur = 0;                                 // Libérer la case actuelle
            plateau[newX][newY].joueur = (plateau[*x][*y].joueur == 1) ? 1 : 2; // Déplacer le joueur
            *x = newX; // Mettre à jour la position x du joueur
            *y = newY; // Mettre à jour la position y du joueur
        }
    }
}

void gererDeplacement(int *playerX, int *playerY) {
    if (kbhit()) {                                  //si on appuie sur une touche
        int key = getch(); // Lire la touche pressée
        if (key == 0 || key == 224) { // Touche spéciale API windows qui dit que bref 224 = touche flèche, alt, ctrl.. ET 0 touche indéfini ou inconnu (belec y'a un bug)
            switch (getch()) {
                case 72: // Flèche haut
                    deplacerJoueur(playerX, playerY, -1, 0);
                break;
                case 80: // Flèche bas
                    deplacerJoueur(playerX, playerY, 1, 0);
                break;
                case 75: // Flèche gauche
                    deplacerJoueur(playerX, playerY, 0, -1);
                break;
                case 77: // Flèche droite
                    deplacerJoueur(playerX, playerY, 0, 1);
                break;
            }
        }
    }
}
