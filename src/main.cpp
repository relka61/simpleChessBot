#include "raylib.h"
#include "render.h"
#include "playerControls.h"
#include "moveGen.h"
#include "utilities.h"

int main(void) {
    // Initialization
    InitWindow(1280, 720, "i luv chess");
    SetTargetFPS(60);

    // Rendering variables
    bool isWhiteAtBottom = true;
    Texture2D spritesheet = LoadTexture("resources/spritesheet.png");

    // Player control variables
    int selectedSquare = -1;

    // Game state initialization
    gameState state = {
        {
            5, 4, 3, 2, 1, 3, 4, 5,
            6, 6, 6, 6, 6, 6, 6, 6,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
           -6,-6,-6,-6,-6,-6,-6,-6,
           -5,-4,-3,-2,-1,-3,-4,-5
        },
        true,           // isWhiteTurn
        {300.0f, 240.0f}, // timeLeft
        0,              // movesWithoutCapture
        {true, true, true, true} // canCastle
    };

    // Create variable to store moves
    std::vector<Move> validMoves = generateMoves(state);

    // Main game loop
    while (!WindowShouldClose()) {
        // Toggle board orientation
        if (IsKeyPressed(KEY_S)) {
            isWhiteAtBottom = !isWhiteAtBottom;
        }        

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            RenderBoard(state, spritesheet, isWhiteAtBottom, selectedSquare);
            handlePlayerControls(state, validMoves, selectedSquare, isWhiteAtBottom);
        EndDrawing();
    }

    // Cleanup and close
    UnloadTexture(spritesheet);
    CloseWindow();
    return 0;
}