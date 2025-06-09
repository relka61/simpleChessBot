#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"

// Declare rendering function
void RenderBoard(Texture2D spritesheet, int startX, int squareSize, int windowHeight, bool isWhiteAtBottom, int selectedSquare);

#endif // RENDER_HTexture2D