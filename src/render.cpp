#include "render.h"

extern int board[64];
extern Color lightColor;
extern Color darkColor;
extern Color highlightColor;

Vector2 origin = { 0.0f, 0.0f };


void RenderBoard(Texture2D spritesheet, int startX, int squareSize, int windowHeight, bool isWhiteAtBottom, int selectedSquare) {
    // Loop through each square
    for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {
            int squareIndex = rank * 8 + file;

            // Calculate variables for displaying board
            int displayFile = isWhiteAtBottom ? file : 7 - file;
            int displayRank = isWhiteAtBottom ? rank : 7 - rank;
            int x = startX + displayFile * squareSize;
            int y = windowHeight - (displayRank + 1) * squareSize;
            Rectangle destRect = { (float)x, (float)y, (float)squareSize, (float)squareSize };

            // Draw the squares
            DrawRectangle(x, y, squareSize, squareSize, (displayFile + displayRank) % 2 == 0 ? darkColor : lightColor);

            // Draw the pieces
            if (selectedSquare != squareIndex) {
                if (board[squareIndex] < 0) {
                    Rectangle pieceRect = { 171 * (-board[squareIndex] - 1) , 171, 171, 171 };
                    DrawTexturePro(spritesheet, pieceRect, destRect, origin, 0, WHITE);
                } else if (board[squareIndex] > 0) {
                    Rectangle pieceRect = { 171 * (board[squareIndex] - 1), 0, 171, 171 };
                    DrawTexturePro(spritesheet, pieceRect, destRect, origin, 0, WHITE);
                }
            }
        }
    }

    // If a square is selected, then:
    if (selectedSquare != -1) {
        // Highlight the selected square
        int selectedX = startX + (selectedSquare % 8) * squareSize;
        int selectedY = windowHeight - ((selectedSquare / 8) + 1) * squareSize;
        DrawRectangle(selectedX, selectedY, squareSize, squareSize, Fade(highlightColor, 0.5f));

        // Draw the piece at the mouse position
        int xPos = 171 * (board[selectedSquare] > 0 ? board[selectedSquare] - 1 : -board[selectedSquare] - 1);
        int yPos = board[selectedSquare] > 0 ? 0 : 171;
        Rectangle pieceRect = { xPos, yPos, 171, 171 };
        Rectangle destRect = { GetMouseX() - squareSize / 2, GetMouseY() - squareSize / 2, (float)squareSize, (float)squareSize };
        DrawTexturePro(spritesheet, pieceRect, destRect, origin, 0, WHITE);
    }
}