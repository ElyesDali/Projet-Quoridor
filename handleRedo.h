#ifndef HANDLEREDO_H
#define HANDLEREDO_H

#include <stdbool.h>

void handleRedo(int *playerX, int *playerY, int *player2X, int *player2Y, int currentPlayer, bool *redoUsed, int lastPlayerX, int lastPlayerY, int lastPlayer2X, int lastPlayer2Y, int lastBarrierX, int lastBarrierY, char lastBarrierType);

#endif // HANDLEREDO_H