#include "piece.h"

Piece::Piece(PieceType pt, QObject *parent)
    : QObject{parent},
    pieceType(pt)
{
    // all pieces are just knights for now
    if (pt == KNIGHT) {
        pieceImage = QImage(":/backgrounds/Images/knight.png");
    }
}
