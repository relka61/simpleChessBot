#include <Raylib.h>
#include <vector>

struct Move {
    int startingSquare;
    int targetSquare;
};

bool onBoard(int square) { 
    return (square >= 0 && square < 64); 
}

int knightMoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
int rookMoves[4] = { 8, -8, 1, -1 };
int bishopMoves[4] = { -9, -7, 7, 9 };
int kingMoves[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };

bool noLoopAround(int square, int targetSquare) {
    return (abs(square % 8 - targetSquare % 8) <= 1);
}

// Helper for sliding pieces (rook, bishop, queen)
void addSlidingMoves(int board[64], int square, int color, const int* colors, int dirCount, std::vector<Move>& moves) {
    for (int i = 0; i < dirCount; i++) {
        int offset = colors[i];
        int targetSquare = square;
        for (int step = 1; step < 8; step++) {
            int fileFrom = targetSquare % 8;
            targetSquare += offset;
            if (!onBoard(targetSquare)) break;
            int fileTo = targetSquare % 8;

            // For horizontal and diagonal moves, prevent wrapping
            if ((offset == 1 || offset == -1) && abs(fileFrom - fileTo) != 1) break;
            if ((offset == 9 || offset == -9 || offset == 7 || offset == -7) && abs(fileFrom - fileTo) != 1) break;

            if (board[targetSquare] == 0) {
                moves.push_back({ square, targetSquare });
            } else {
                if (color * board[targetSquare] < 0) {
                    moves.push_back({ square, targetSquare });
                }
                break; // Blocked by any piece
            }
        }
    }
}

std::vector<Move> generateMoves(int board[64]) {
    std::vector<Move> moves;

    for (int square = 0; square < 64; square++) {
        if (board[square] != 0) {
            int piece = abs(board[square]);
            int color = board[square] > 0 ? 1 : -1;

            // Pawn
            if (piece == 6) {
                int startRank = color > 0 ? 1 : 6;

                // Standard Move
                int targetSquare = square + color * 8;
                if (onBoard(targetSquare) && board[targetSquare] == 0) {
                    moves.push_back({ square, targetSquare });
                }
                // Double Move on first move
                targetSquare = square + color * 16;
                if (onBoard(targetSquare) && square / 8 == startRank && board[targetSquare] == 0) {
                    moves.push_back({ square, targetSquare });
                }
                // Capture left
                targetSquare = square + color * 7;
                if (onBoard(targetSquare) && board[targetSquare] * color < 0) {
                    moves.push_back({ square, targetSquare });
                }
                // Capture right
                targetSquare = square + color * 9;
                if (onBoard(targetSquare) && board[targetSquare] * color < 0) {
                    moves.push_back({ square, targetSquare });
                }
            }

            // Rook
            if (piece == 5) {
                addSlidingMoves(board, square, color, rookMoves, 4, moves);
            }

            // Knight
            if (piece == 4) {
                for (int i = 0; i < 8; i++) {
                    int targetSquare = square + knightMoves[i];
                    if (!onBoard(targetSquare)) continue;

                    int fileFrom = square % 8;
                    int fileTo = targetSquare % 8;
                    int df = abs(fileFrom - fileTo);

                    if (df == 1 || df == 2) {
                        if (color * board[targetSquare] <= 0) {
                            moves.push_back({ square, targetSquare });
                        }
                    }
                }
            }

            // Bishop
            if (piece == 3) {
                addSlidingMoves(board, square, color, bishopMoves, 4, moves);
            }

            // Queen
            if (piece == 2) {
                addSlidingMoves(board, square, color, rookMoves, 4, moves);
                addSlidingMoves(board, square, color, bishopMoves, 4, moves);
            }

            // King
            if (piece == 1) {
                for (int i = 0; i < 8; i++) {
                    int targetSquare = square + kingMoves[i];
                    if (noLoopAround(square, targetSquare) && onBoard(targetSquare) && (board[targetSquare] * color <= 0)) {
                        moves.push_back({ square, targetSquare });
                    }
                }
            }
        }
    }

    return moves;
}