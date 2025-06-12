#include "raylib.h"
#include "utilities.h"
#include <stdlib.h>
#include <vector>

Vector2 squareCenter(int square, int startX, int squareSize, int windowHeight, bool isWhiteAtBottom) {
    int file = square % 8;
    int rank = square / 8;
    int displayFile = isWhiteAtBottom ? file : 7 - file;
    int displayRank = isWhiteAtBottom ? rank : 7 - rank;
    float x = startX + displayFile * squareSize + squareSize / 2.0f;
    float y = windowHeight - (displayRank + 1) * squareSize + squareSize / 2.0f;
    return { x, y };
}

bool onBoard(int square) { 
    return (square >= 0 && square < 64); 
}

bool noLoopAround(int square, int targetSquare, int distance) {
    return (abs(square % 8 - targetSquare % 8) <= distance);
}