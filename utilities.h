#pragma once

struct gameState {
    int board[64];
    bool isWhiteTurn;
    float timeLeft[2];
    int movesWithoutCapture;
    bool canCastle[4]; // 0: white kingside, 1: white queenside, 2: black kingside, 3: black queenside
};

struct Move {
    int startingSquare;
    int targetSquare;
};

enum PieceType {
    EMPTY  = 0,
    KING   = 1,
    QUEEN  = 2,
    BISHOP = 3,
    KNIGHT = 4,
    ROOK   = 5,
    PAWN   = 6
};

Vector2 squareCenter(int square, int startX, int squareSize, int windowHeight, bool isWhiteAtBottom);
bool onBoard(int square);
bool noLoopAround(int square, int targetSquare, int distance = 1);