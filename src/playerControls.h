#pragma once

#include "raylib.h"
#include "utilities.h"
#include <vector>

void handlePlayerControls(gameState& state, std::vector<Move>& validMoves, int &selectedSquare, bool isWhiteAtTop);