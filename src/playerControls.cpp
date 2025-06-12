#include "raylib.h"
#include <raymath.h>
#include "playerControls.h"
#include "moveGen.h"
#include "utilities.h"
#include <algorithm>

void handlePlayerControls(gameState& state, std::vector<Move>& validMoves, int &selectedSquare, bool isWhiteAtBottom) {
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();

    int startX = (windowWidth - windowHeight) / 2;
    int squareSize = windowHeight / 8;

    int* board = state.board;

    int squareFile = Clamp((GetMouseX() - startX) / squareSize, 0, 7);
    int squareRank = Clamp((windowHeight - GetMouseY()) / squareSize, 0, 7);
    int squareIndex = squareRank * 8 + squareFile;
    squareIndex = isWhiteAtBottom ? squareIndex : 63 - squareIndex;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (selectedSquare == -1) {
            if (board[squareIndex] != 0) {
                selectedSquare = squareIndex;
            }
        }
    } else {
        if (selectedSquare != -1) {
            auto it = std::find_if(validMoves.begin(), validMoves.end(),
                [selectedSquare, squareIndex](const Move& m) {
                    return m.startingSquare == selectedSquare && m.targetSquare == squareIndex;
                });
            if (it != validMoves.end()) {
                makeMove(state, validMoves, *it);
            }
            selectedSquare = -1;
        }
    }

    
}