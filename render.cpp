#include "render.h"
#include "utilities.h"
#include "moveGen.h"

Color lightColor = { 210, 180, 150, 255 };
Color darkColor = { 140, 100, 80, 255 };
Color highlightColor = { 10, 100, 200, 255 };
Color possibleMoveColor = { 10, 100, 200, 127 };

Vector2 origin = { 0.0f, 0.0f };

void RenderBoard(gameState state, Texture2D spritesheet, bool isWhiteAtBottom, int selectedSquare) {
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();

    int startX = (windowWidth - windowHeight) / 2;
    int squareSize = windowHeight / 8;

    // Timers
    float timeLeftWhite = state.timeLeft[0];
    float timeLeftBlack = state.timeLeft[1];
    int whiteMinutes = (int)timeLeftWhite / 60;
    int whiteSeconds = (int)timeLeftWhite % 60;
    int blackMinutes = (int)timeLeftBlack / 60;
    int blackSeconds = (int)timeLeftBlack % 60;


    int xPos = windowWidth - (windowWidth - startX - windowHeight ) * 0.6;
    if (isWhiteAtBottom) {
        DrawText(TextFormat("%dm%02ds", whiteMinutes, whiteSeconds), xPos, windowHeight * 0.6, 30, WHITE);
        DrawText(TextFormat("%dm%02ds", blackMinutes, blackSeconds), xPos, windowHeight * 0.4, 30, WHITE);
    } else {
        DrawText(TextFormat("%dm%02ds", blackMinutes, blackSeconds), xPos, windowHeight * 0.6, 30, WHITE);
        DrawText(TextFormat("%dm%02ds", whiteMinutes, whiteSeconds), xPos, windowHeight * 0.4, 30, WHITE);
    }
    

    int* board = state.board;

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
            if (selectedSquare != squareIndex && board[squareIndex] != 0) {
                int xPos = 171 * (board[squareIndex] > 0 ? board[squareIndex] - 1 : -board[squareIndex] - 1);
                int yPos = board[squareIndex] > 0 ? 0 : 171;
                Rectangle pieceRect = { xPos, yPos, 171, 171 };
                DrawTexturePro(spritesheet, pieceRect, destRect, origin, 0, WHITE);
            }
        }
    }

    // If a square is selected, then:
    if (selectedSquare != -1) {
        // Highlight the selected square
        int selectedX = startX + (selectedSquare % 8) * squareSize;
        int selectedY = windowHeight - ((selectedSquare / 8) + 1) * squareSize;
        DrawRectangle(selectedX, selectedY, squareSize, squareSize, highlightColor);

        // Draw the possible moves
        std::vector<Move> validMoves = generateMoves(state);
            for (const Move& move : validMoves) {
                if (move.startingSquare == selectedSquare) {
                    int file = move.targetSquare % 8;
                    int rank = move.targetSquare / 8;
                    int displayFile = isWhiteAtBottom ? file : 7 - file;
                    int displayRank = isWhiteAtBottom ? rank : 7 - rank;
                    int x = startX + displayFile * squareSize;
                    int y = windowHeight - (displayRank + 1) * squareSize;

                    DrawRectangle(x, y, squareSize, squareSize, possibleMoveColor);
                }
            }

        // Draw the piece at the mouse position
        int xPos = 171 * (board[selectedSquare] > 0 ? board[selectedSquare] - 1 : -board[selectedSquare] - 1);
        int yPos = board[selectedSquare] > 0 ? 0 : 171;
        Rectangle pieceRect = { xPos, yPos, 171, 171 };
        Rectangle destRect = { GetMouseX() - squareSize / 2, GetMouseY() - squareSize / 2, (float)squareSize, (float)squareSize };
        DrawTexturePro(spritesheet, pieceRect, destRect, origin, 0, WHITE);
    }
}