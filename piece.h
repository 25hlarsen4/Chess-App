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
        KING,
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN
    };

    explicit Piece(PieceType, QObject *parent = nullptr);

    PieceType pieceType;

    QImage pieceImage;

private:


signals:

};

#endif // PIECE_H
