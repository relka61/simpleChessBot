#include <Raylib.h>

void generateValidMoves(int selectedSquare, int board[64], int moves[64]) {
    // Clear the moves array
    for (int i = 0; i < 64; i++) moves[i] = 0;

    
    // White Pawn
    if (board[selectedSquare] == 6) {
        // Standard Move
        if (selectedSquare / 8 == 1 && board[selectedSquare + 16] == 0) {
            moves[selectedSquare + 16] = 1;
        }
        // Double Move on first move
        if (selectedSquare + 8 < 64 && board[selectedSquare + 8] == 0) {
            moves[selectedSquare + 8] = 1;
        }
        // Capture left
        if (selectedSquare % 8 > 0 && selectedSquare + 7 < 64 && board[selectedSquare + 7] < 0) {
            moves[selectedSquare + 7] = 1;
        }
        // Capture right
        if (selectedSquare % 8 < 7 && selectedSquare + 9 < 64 && board[selectedSquare + 9] < 0) {
            moves[selectedSquare + 9] = 1;
        }
    }

    // Black Pawn
    if (board[selectedSquare] == -6) {
        // Standard Move
        if (selectedSquare / 8 == 6 && board[selectedSquare - 16] == 0) {
            moves[selectedSquare - 16] = 1;
        }
        // Double Move on first move
        if (selectedSquare - 8 >= 0 && board[selectedSquare - 8] == 0) {
            moves[selectedSquare - 8] = 1;
        }
        // Capture left
        if (selectedSquare % 8 > 0 && selectedSquare - 9 >= 0 && board[selectedSquare - 9] > 0) {
            moves[selectedSquare - 9] = 1;
        }
        // Capture right
        if (selectedSquare % 8 < 7 && selectedSquare - 7 >= 0 && board[selectedSquare - 7] > 0) {
            moves[selectedSquare - 7] = 1;
        }
    }

    // White Knight
    if (board[selectedSquare] == 4) {
        int knightMoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
        for (int i = 0; i < 8; i++) {
            int moveIndex = selectedSquare + knightMoves[i];
            if (moveIndex >= 0 && moveIndex < 64 && (board[moveIndex] <= 0 || board[moveIndex] == -6)) {
                moves[moveIndex] = 1;
            }
        }
    }

    // Black Knight
    if (board[selectedSquare] == -4) {
        int knightMoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
        for (int i = 0; i < 8; i++) {
            int moveIndex = selectedSquare + knightMoves[i];
            if (moveIndex >= 0 && moveIndex < 64 && (board[moveIndex] >= 0 || board[moveIndex] == 6)) {
                moves[moveIndex] = 1;
            }
        }
    }

    // White King
    if (board[selectedSquare] == 2) {
        int kingMoves[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
        for (int i = 0; i < 8; i++) {
            int moveIndex = selectedSquare + kingMoves[i];
            if (moveIndex >= 0 && moveIndex < 64 && (board[moveIndex] <= 0 || board[moveIndex] == -6)) {
                moves[moveIndex] = 1;
            }
        }
    }

    // Black King
    if (board[selectedSquare] == -2) {
        int kingMoves[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
        for (int i = 0; i < 8; i++) {
            int moveIndex = selectedSquare + kingMoves[i];
            if (moveIndex >= 0 && moveIndex < 64 && (board[moveIndex] >= 0 || board[moveIndex] == 6)) {
                moves[moveIndex] = 1;
            }
        }
    }
}