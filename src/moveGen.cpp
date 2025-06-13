#include <Raylib.h>
#include "utilities.h"
#include <vector>

int knightMoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
int rookMoves[4] = { 8, -8, 1, -1 };
int bishopMoves[4] = { -9, -7, 7, 9 };
int kingMoves[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };

// Helper for sliding pieces (rook, bishop, queen)
void addSlidingMoves(int board[64], int square, int color, const int* moveOffsets, std::vector<Move>& moves) {
    for (int i = 0; i < 4; i++) {
        int offset = moveOffsets[i];
        int targetSquare = square;
        for (int step = 1; step < 8; step++) {
            int fileFrom = targetSquare % 8;
            if (!noLoopAround(targetSquare, targetSquare + offset)) break;
            targetSquare += offset;
            if (!onBoard(targetSquare)) break;

            if (board[targetSquare] == 0) {
                moves.push_back({ square, targetSquare });
            } else {
                if (color * board[targetSquare] < 0) {
                    moves.push_back({ square, targetSquare });
                }
                break;
            }
        }
    }
}

void pawnMove(std::vector<Move>& moves, int square, int targetSquare, int color) {
    // Check for promotion
    if (targetSquare / 8 == (color > 0 ? 7 : 0)) {
        for (int promotionPiece = QUEEN; promotionPiece <= ROOK; promotionPiece++) {
            moves.push_back({ square, targetSquare, promotionPiece });
        }
    } else {
        moves.push_back({ square, targetSquare });
    }
}

std::vector<Move> generateMoves(gameState state) {
    std::vector<Move> moves;
    int* board = state.board;
    int color = state.isWhiteTurn ? 1 : -1;


    for (int square = 0; square < 64; square++) {
        if (board[square] != 0) {
            int piece = color * board[square];

            if (piece == PAWN || piece == PAWN_ENPASSANT) {
                int startRank = color > 0 ? 1 :  6;

                // Standard Move
                int targetSquare = square + color * 8;
                if (onBoard(targetSquare) && board[targetSquare] == 0) {
                    pawnMove(moves, square, targetSquare, color);
                }
                // Double Move on first move
                targetSquare = square + color * 16;
                if (onBoard(targetSquare) && square / 8 == startRank && board[targetSquare] == 0) {
                    pawnMove(moves, square, targetSquare, color);
                }
                // Capture left
                targetSquare = square + color * 7;
                if (onBoard(targetSquare) && board[targetSquare] * color < 0 && noLoopAround(square, targetSquare)) {
                    pawnMove(moves, square, targetSquare, color);
                }
                // Capture right
                targetSquare = square + color * 9;
                if (onBoard(targetSquare) && board[targetSquare] * color < 0 && noLoopAround(square, targetSquare)) {
                    pawnMove(moves, square, targetSquare, color);
                }
                // En passant left
                targetSquare = square + color * 7;
                int enPassantSquare = targetSquare - 8 * color;
                if (onBoard(targetSquare) && onBoard(enPassantSquare) && abs(board[enPassantSquare]) == PAWN_ENPASSANT && noLoopAround(square, targetSquare)) {
                    moves.push_back({ square, targetSquare });
                }
                // En passant right
                targetSquare = square + color * 9;
                enPassantSquare = targetSquare - 8 * color;
                if (onBoard(targetSquare) && onBoard(enPassantSquare) && abs(board[enPassantSquare]) == PAWN_ENPASSANT && noLoopAround(square, targetSquare)) {
                    moves.push_back({ square, targetSquare });
                }
            } else

            if (piece == ROOK) {
                addSlidingMoves(board, square, color, rookMoves, moves);
            } else

            if (piece == KNIGHT) {
                for (int i = 0; i < 8; i++) {
                    int targetSquare = square + knightMoves[i];
                    if (noLoopAround(square, targetSquare, 2) && onBoard(targetSquare)) {
                        if (color * board[targetSquare] <= 0) {
                            moves.push_back({ square, targetSquare });
                        }
                    }
                }
            } else

            if (piece == BISHOP) {
                addSlidingMoves(board, square, color, bishopMoves, moves);
            } else 
            
            if (piece == QUEEN) {
                addSlidingMoves(board, square, color, rookMoves, moves);
                addSlidingMoves(board, square, color, bishopMoves, moves);
            } else 
            
            if (piece == KING) {
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


void makeMove(gameState& state, std::vector<Move>& validMoves, const Move& move) {
    int piece = state.board[move.startingSquare];
    int color = piece > 0 ? 1 : -1;
    piece = abs(piece);

    // En Passant Capture
    if (piece == PAWN) {
        if (abs(move.targetSquare - move.startingSquare) == 7 || abs(move.targetSquare - move.startingSquare) == 9) {
            int enPassantTarget = move.targetSquare - color * 8;
            if (onBoard(enPassantTarget) && abs(state.board[enPassantTarget]) == PAWN_ENPASSANT) {
                state.board[enPassantTarget] = 0;
            }
        }
    }

    for (int i = 0; i < 64; i++) {
        if (state.board[i] == PAWN_ENPASSANT) state.board[i] = PAWN;
        if (state.board[i] == -PAWN_ENPASSANT) state.board[i] = -PAWN;
    }

    if (piece == PAWN) {
        // Promotion
        int promotionRank = color > 0 ? 7 : 0;
        if (move.targetSquare / 8 == promotionRank) {
            piece = move.promotionPiece;
        }
        
        // Change into an en passant-able pawn if the move is a double step
        if (abs(move.targetSquare - move.startingSquare) == 16) {
            piece = PAWN_ENPASSANT;
        }
    }

    // Castling

    // General Move
    state.board[move.targetSquare] = color * piece;
    state.board[move.startingSquare] = 0;
    state.isWhiteTurn = !state.isWhiteTurn;
    validMoves = generateMoves(state);
}