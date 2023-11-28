#include "piece.h"

Piece::Piece(PieceType pt, QObject *parent)
    : QObject{parent},
    pieceType(pt)
{
    if (pt == BLACK_KNIGHT) {
        pieceImage = QImage(":/pieces/Images/blackKnight.png");
    }

    else if (pt == BLACK_BISHOP) {
        pieceImage = QImage(":/pieces/Images/blackBishop.png");
    }

    else if (pt == BLACK_ROOK) {
        pieceImage = QImage(":/pieces/Images/blackRook.png");
    }

    else if (pt == BLACK_PAWN) {
        pieceImage = QImage(":/pieces/Images/blackPawn.png");
    }

    else if (pt == BLACK_KING) {
        pieceImage = QImage(":/pieces/Images/blackKing.png");
    }

    else if (pt == BLACK_QUEEN) {
        pieceImage = QImage(":/pieces/Images/blackQueen.png");
    }

    else if (pt == WHITE_KNIGHT) {
        pieceImage = QImage(":/pieces/Images/whiteKnight.png");
    }

    else if (pt == WHITE_BISHOP) {
        pieceImage = QImage(":/pieces/Images/whiteBishop.png");
    }

    else if (pt == WHITE_ROOK) {
        pieceImage = QImage(":/pieces/Images/whiteRook.png");
    }

    else if (pt == WHITE_PAWN) {
        pieceImage = QImage(":/pieces/Images/whitePawn.png");
    }

    else if (pt == WHITE_KING) {
        pieceImage = QImage(":/pieces/Images/whiteKing.png");
    }

    else if (pt == WHITE_QUEEN) {
        pieceImage = QImage(":/pieces/Images/whiteQueen.png");
    }

}
