#pragma once

#include <vector>
#include "utilities.h"
#include <vector>

std::vector<Move> generateMoves(gameState state);
void makeMove(gameState& state, std::vector<Move>& validMoves, const Move& move);