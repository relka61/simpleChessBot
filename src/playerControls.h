#ifndef PLAYERCONTRLS_H
#define PLAYERCONTRLS_H

#include "raylib.h"

void HandlePlayerControls(int board[64], int &selectedSquare, bool isWhiteAtTop, int startX, int squareSize, int windowHeight);

#endif // PLAYERCONTRLS_H