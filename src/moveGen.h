#ifndef MOVEGEN_H
#define MOVEGEN_H
#include <vector>

struct Move {
    int startingSquare;
    int targetSquare;
};

std::vector<Move> generateMoves(int board[64]);

#endif // MOVEGEN_H