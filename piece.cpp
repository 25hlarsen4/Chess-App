#include "piece.h"

Piece::Piece(QObject *parent)
    : QObject{parent}
{
    // all pieces are just knights for now
    pieceImage = QImage(":/backgrounds/Images/knight.png");
}
