#include "piece.h"

Piece::Piece(PieceType pt, bool newPawn, QObject *parent)
    : QObject{parent},
    pieceType(pt),
    freshPawn(newPawn)
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

bool Piece::checkValidMove(QPair<int, int> currLocation, QPair<int, int> nextLocation){
    // Check in bounds
    if(nextLocation.first < 1 ||
        nextLocation.first > 8 ||
        nextLocation.second < 1 ||
        nextLocation.second > 8){
        return false;
    }
    // Check if move valid for piece
    if (pieceType == BLACK_KNIGHT) {
    }

    else if (pieceType == BLACK_BISHOP) {
    }

    else if (pieceType == BLACK_ROOK) {
    }

    else if (pieceType == BLACK_PAWN) {
    }

    else if (pieceType == BLACK_KING) {
    }

    else if (pieceType == BLACK_QUEEN) {
    }

    else if (pieceType == WHITE_KNIGHT) {
        return ((nextLocation.first == currLocation.first + 2 &&
                 nextLocation.second == currLocation.first + 1) ||
                (nextLocation.first == currLocation.first + 2 &&
                 nextLocation.second == currLocation.first - 1) ||
                (nextLocation.first == currLocation.first + 1 &&
                 nextLocation.second == currLocation.first + 2) ||
                (nextLocation.first == currLocation.first + 1 &&
                 nextLocation.second == currLocation.first - 2) ||
                (nextLocation.first == currLocation.first - 2 &&
                 nextLocation.second == currLocation.first + 1) ||
                (nextLocation.first == currLocation.first - 2 &&
                 nextLocation.second == currLocation.first - 1) ||
                (nextLocation.first == currLocation.first - 1 &&
                 nextLocation.second == currLocation.first + 2) ||
                (nextLocation.first == currLocation.first - 1 &&
                nextLocation.second == currLocation.first - 2));
    }

    else if (pieceType == WHITE_BISHOP) {
        return abs(nextLocation.first - currLocation.first) == abs(nextLocation.second - currLocation.second);
    }

    else if (pieceType == WHITE_ROOK) {
        return (nextLocation.first == currLocation.first && nextLocation.second != currLocation.second) ||
               (nextLocation.second == currLocation.second && nextLocation.first != currLocation.first);
    }

    else if (pieceType == WHITE_PAWN) {
        if(nextLocation.second == currLocation.second){
            if(freshPawn){
                return (nextLocation.first == currLocation.first + 1) || (nextLocation.first == currLocation.first + 2);
            }else{
                return nextLocation.first == currLocation.first + 1;
            }
        }
    }

    else if (pieceType == WHITE_KING) {
        return ((nextLocation.first == currLocation.first ||
                 nextLocation.first == currLocation.first - 1 ||
                 nextLocation.first == currLocation.first + 1) &&
                (nextLocation.second == currLocation.second ||
                 nextLocation.second == currLocation.second - 1 ||
                 nextLocation.second == currLocation.second + 1));
    }

    else if (pieceType == WHITE_QUEEN) {
        return (abs(nextLocation.first - currLocation.first) == abs(nextLocation.second - currLocation.second)) ||
               (nextLocation.first == currLocation.first && nextLocation.second != currLocation.second) ||
               (nextLocation.second == currLocation.second && nextLocation.first != currLocation.first);
    }
    return false;
}

