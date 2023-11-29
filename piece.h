#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <cstdlib>

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

    explicit Piece(PieceType, bool newPawn = false, QObject *parent = nullptr);

    PieceType pieceType;

    QPixmap pieceImage;

    bool freshPawn;

    void setKnight(QPushButton* space);

private:
    QList<QPair<int, int>> getPossibleLocations(QPair<int, int>, QHash<QPair<int, int>, Piece*>);
    bool checkInbounds(int, int);
    bool whitePiece(Piece*);
    bool blackPiece(Piece*);
    bool checkPiece(int, int, bool, QHash<QPair<int, int>, Piece*>, QList<QPair<int, int>>);
    void rookMoves(bool, QPair<int,int>, QHash<QPair<int, int>, Piece*>, QList<QPair<int, int>>);
    void bishopMoves(bool, QPair<int,int>, QHash<QPair<int, int>, Piece*>, QList<QPair<int, int>>);

signals:

};

#endif // PIECE_H
