#include "piece.h"

Piece::Piece(PieceType pt, QObject *parent)
    : QObject{parent},
    pieceType(pt)
{
    if (pt == BLACK_KNIGHT) {
        pieceImage = QPixmap(":/pieces/Images/blackKnight.png");
    }

    else if (pt == BLACK_BISHOP) {
        pieceImage = QPixmap(":/pieces/Images/blackBishop.png");
    }

    else if (pt == BLACK_ROOK) {
        pieceImage = QPixmap(":/pieces/Images/blackRook.png");
    }

    else if (pt == BLACK_PAWN) {
        pieceImage = QPixmap(":/pieces/Images/blackPawn.png");
    }

    else if (pt == BLACK_KING) {
        pieceImage = QPixmap(":/pieces/Images/blackKing.png");
    }

    else if (pt == BLACK_QUEEN) {
        pieceImage = QPixmap(":/pieces/Images/blackQueen.png");
    }

    else if (pt == WHITE_KNIGHT) {
        pieceImage = QPixmap(":/pieces/Images/whiteKnight.png");
    }

    else if (pt == WHITE_BISHOP) {
        pieceImage = QPixmap(":/pieces/Images/whiteBishop.png");
    }

    else if (pt == WHITE_ROOK) {
        pieceImage = QPixmap(":/pieces/Images/whiteRook.png");
    }

    else if (pt == WHITE_PAWN) {
        pieceImage = QPixmap(":/pieces/Images/whitePawn.png");
    }

    else if (pt == WHITE_KING) {
        pieceImage = QPixmap(":/pieces/Images/whiteKing.png");
    }

    else if (pt == WHITE_QUEEN) {
        pieceImage = QPixmap(":/pieces/Images/whiteQueen.png");
    }

}
void Piece::setKnight(QPushButton *space){
    QLabel *pieceLabel = new QLabel(space);
    pieceLabel->setPixmap(pieceImage);
    pieceLabel->setScaledContents(true);
    pieceLabel->setGeometry(0, 0, space->width(), space->height());
    pieceLabel->show();
}
