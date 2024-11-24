//
// Created by dariu on 11/23/2024.
//

int victoire(int PlayerX, int PlayerY, int currentPlayer) {
        if (currentPlayer == 1) {
            return (PlayerX == 8); // Le joueur 1 gagne s'il atteint la ligne 8 (indexé à partir de 0)
        } else if (currentPlayer == 2) {
            return (PlayerX == 0); // Le joueur 2 gagne s'il atteint la ligne 0
        } else if (currentPlayer == 3 || currentPlayer == 4) {
            return (PlayerY == 8);
        } else if(currentPlayer == 4);{
            return (PlayerY == 0);
        }
        return 0;
    }
