#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <stdbool.h>

void gameLoop();
void handleRedo(int *playerX, int *playerY, int *player2X, int *player2Y, int currentPlayer, bool *redoUsed, int lastPlayerX, int lastPlayerY, int lastPlayer2X, int lastPlayer2Y, int lastBarrierX, int lastBarrierY, char lastBarrierType);

#endif // GAMELOOP_H