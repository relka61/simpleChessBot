#include "raylib.h"
#include <raymath.h>
#include "playerControls.h"
#include "moveGen.h"

extern bool isPieceAt(int board[64], int index);

int validMoves[64];

void HandlePlayerControls(int board[64], int &selectedSquare, bool isWhiteAtBottom, int startX, int squareSize, int windowHeight) {
    int squareFile = Clamp((GetMouseX() - startX) / squareSize, 0, 7);
    int squareRank = Clamp((windowHeight - GetMouseY()) / squareSize, 0, 7);
    int squareIndex = squareRank * 8 + squareFile;
    squareIndex = isWhiteAtBottom ? squareIndex : 63 - squareIndex;

    DrawText(TextFormat("SelectedSquare: %d", selectedSquare), 10, 10, 20, WHITE);
    DrawText(TextFormat("Piece: %d", board[selectedSquare]), 10, 30, 20, WHITE);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (selectedSquare == -1) {
            if (isPieceAt(board, squareIndex)) {
                selectedSquare = squareIndex;
                generateValidMoves(selectedSquare, board, validMoves);
            }
        }
    } else {
        if (selectedSquare != -1) {
            if (validMoves[squareIndex] == 1) { // If the move is valid
                board[squareIndex] = board[selectedSquare];
                board[selectedSquare] = 0;
            }

            selectedSquare = -1;
        }
    }

    // Draw the valid moves
    for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {
            int squareIndex = rank * 8 + file;

            // Calculate variables for displaying board
            int displayFile = isWhiteAtBottom ? file : 7 - file;
            int displayRank = isWhiteAtBottom ? rank : 7 - rank;
            int x = startX + displayFile * squareSize;
            int y = windowHeight - (displayRank + 1) * squareSize;

            // Draw the squares
            if (validMoves[squareIndex] != 0) {
                DrawRectangle(x, y, squareSize, squareSize, Fade(GREEN, 0.5f));
            }
            
        }
    }
}