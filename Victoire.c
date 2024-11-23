//
// Created by joshu on 23/11/2024.
//

#include "Victoire.h"

int victoire(int PlayerX, int PlayerY, int currentPlayer) {
    if (currentPlayer == 1) {
        if (PlayerX == 8) {
            return 1;
        } else {
            return 0;
        }
    } else if (currentPlayer == 2) {
        if (PlayerX == 0) {
            return 1;
        } else {
            return 0;
        }
    } else if (currentPlayer == 3) {
        if (PlayerY == 8) {
            return 1;
        } else {
            return 0;
        }
    } else if (currentPlayer == 4) {
        if (PlayerY == 8) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}