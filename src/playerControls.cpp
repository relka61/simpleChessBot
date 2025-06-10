#include "raylib.h"
#include <raymath.h>
#include "playerControls.h"
#include "moveGen.h"
#include <algorithm>

extern bool isPieceAt(int board[64], int index);
extern Vector2 squareCenter(int square, int startX, int squareSize, int windowHeight, bool isWhiteAtBottom);

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
            }
        }
    } else {
        if (selectedSquare != -1) {
            std::vector<Move> validMoves = generateMoves(board);
            auto it = std::find_if(validMoves.begin(), validMoves.end(),
                [selectedSquare, squareIndex](const Move& m) {
                    return m.startingSquare == selectedSquare && m.targetSquare == squareIndex;
                });
            if (it != validMoves.end()) {
                board[squareIndex] = board[selectedSquare];
                board[selectedSquare] = 0;
            }

            selectedSquare = -1;
        }
    }

    std::vector<Move> validMoves = generateMoves(board);
    for (const Move& move : validMoves) {
                Vector2 start = squareCenter(move.startingSquare, startX, squareSize, windowHeight, isWhiteAtBottom);
                Vector2 end = squareCenter(move.targetSquare, startX, squareSize, windowHeight, isWhiteAtBottom);

                // Draw the shaft
                DrawLineEx(start, end, 4, RED);

                // Draw the arrowhead
                Vector2 dir = Vector2Normalize(Vector2Subtract(end, start));
                DrawCircleV(end, 7, RED);
            }
}