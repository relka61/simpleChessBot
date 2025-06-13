#include "raylib.h"
#include <raymath.h>
#include "playerControls.h"
#include "moveGen.h"
#include "utilities.h"
#include <algorithm>

enum PromotionUIState { NONE, SHOWING };
PromotionUIState promotionUIState = NONE;
Move pendingPromotionMove;
std::vector<Move> pendingPromotionMoves;

Color promotionBackgroundColor = { 200, 200, 200, 255 };

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

    if (promotionUIState == SHOWING) {
        // Draw four options: Queen, Rook, Bishop, Knight
        for (int i = 0; i < 4; ++i) {
            int x = startX + i * squareSize;
            DrawRectangle(x, 0, squareSize, squareSize, promotionBackgroundColor);
            // Optionally draw piece icons here
            int pieceType = QUEEN + i; // 0: Queen, 1: Rook, 2: Bishop, 3: Knight
            // Draw piece icon (assuming you have a function to draw pieces)
            DrawText(TextFormat("%s", pieceType == QUEEN ? "Q" : pieceType == ROOK ? "R" : pieceType == BISHOP ? "B" : "N"), 
                     x + squareSize / 4, squareSize / 4, 20, BLACK);

            // Detect click
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int mouseX = GetMouseX();
                int mouseY = GetMouseY();
                if (mouseX >= x && mouseX < x + squareSize && mouseY >= 0 && mouseY < squareSize) {
                    // Find the corresponding move
                    int promotionPiece = QUEEN + i;
                    auto it = std::find_if(
                        pendingPromotionMoves.begin(), pendingPromotionMoves.end(),
                        [promotionPiece](const Move& m) { return m.promotionPiece == promotionPiece; }
                    );
                    if (it != pendingPromotionMoves.end()) {
                        makeMove(state, validMoves, *it);
                    }
                    promotionUIState = NONE;
                    selectedSquare = -1;
                    pendingPromotionMoves.clear();
                    return;
                }
            }
        }
        return; // Block normal controls while promotion UI is up
    }

    // Normal controls:
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (selectedSquare == -1) {
            if (board[squareIndex] != 0) {
                selectedSquare = squareIndex;
            }
        }
    } else {
        if (selectedSquare != -1) {
            // Find all moves from selectedSquare to squareIndex
            std::vector<Move> candidateMoves;
            for (const Move& m : validMoves) {
                if (m.startingSquare == selectedSquare && m.targetSquare == squareIndex)
                    candidateMoves.push_back(m);
            }
            if (!candidateMoves.empty()) {
                // Check if this is a promotion
                if (candidateMoves[0].promotionPiece != 0) {
                    // Show promotion UI
                    promotionUIState = SHOWING;
                    pendingPromotionMoves = candidateMoves;
                    pendingPromotionMove = candidateMoves[0];
                    // Don't reset selectedSquare yet
                } else {
                    makeMove(state, validMoves, candidateMoves[0]);
                    selectedSquare = -1;
                }
            } else {
                selectedSquare = -1;
            }
        }
    }
}