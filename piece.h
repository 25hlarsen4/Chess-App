#ifndef PIECE_H
#define PIECE_H

#include "qimage.h"
#include <QObject>

class Piece : public QObject
{
    Q_OBJECT
public:

    enum PieceType
    {
        WHITE_KING,
        WHITE_QUEEN,
        WHITE_ROOK,
        WHITE_BISHOP,
        WHITE_KNIGHT,
        WHITE_PAWN,
        BLACK_KING,
        BLACK_QUEEN,
        BLACK_ROOK,
        BLACK_BISHOP,
        BLACK_KNIGHT,
        BLACK_PAWN
    };

    explicit Piece(PieceType, QObject *parent = nullptr);

    PieceType pieceType;

    QImage pieceImage;

private:


signals:

};

#endif // PIECE_H
