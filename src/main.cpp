#include "raylib.h"
#include <raymath.h>
#include "render.h"
#include "playerControls.h"
#include "moveGen.h"

int board[64] = {
     5, 4, 3, 2, 1, 3, 4, 5,
     6, 6, 6, 6, 6, 6, 6, 6,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
    -6,-6,-6,-6,-6,-6,-6,-6,
    -5,-4,-3,-1,-2,-3,-4,-5
};

struct gameState {
    int board[64];
    bool isWhiteTurn;
    float timeLeft[2];
    int movesWithoutCapture;
    bool canCastle[4]; // 0: white kingside, 1: white queenside, 2: black kingside, 3: black queenside
};

Color lightColor = { 210, 180, 150, 255 };
Color darkColor = { 140, 100, 80, 255 };
Color highlightColor = { 40, 140, 255, 255 };

bool isPieceAt(int board[64], int index) {
    return board[index] != 0;
}

Vector2 squareCenter(int square, int startX, int squareSize, int windowHeight, bool isWhiteAtBottom) {
    int file = square % 8;
    int rank = square / 8;
    int displayFile = isWhiteAtBottom ? file : 7 - file;
    int displayRank = isWhiteAtBottom ? rank : 7 - rank;
    float x = startX + displayFile * squareSize + squareSize / 2.0f;
    float y = windowHeight - (displayRank + 1) * squareSize + squareSize / 2.0f;
    return { x, y };
}


int main(void) {
    InitWindow(1280, 720, "i luv chess");
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    SetTargetFPS(60);

    bool isWhiteAtBottom = true;
    int selectedSquare = -1;

    int startX = (windowWidth - windowHeight) / 2;
    int squareSize = windowHeight / 8;

    Texture2D spritesheet = LoadTexture("resources/spritesheet.png");

    std::vector<Move> moves = generateMoves(board);

    // Main game loop
    while (!WindowShouldClose()) {
        // Toggle board orientation
        if (IsKeyPressed(KEY_S)) {
            isWhiteAtBottom = !isWhiteAtBottom;
        }

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            RenderBoard(spritesheet, startX, squareSize, windowHeight, isWhiteAtBottom, selectedSquare);
            HandlePlayerControls(board, selectedSquare, isWhiteAtBottom, startX, squareSize, windowHeight);
        EndDrawing();
    }

    UnloadTexture(spritesheet);
    CloseWindow();
    return 0;
}