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

QList<QPair<int, int>> Piece::getPossibleLocations(QPair<int,int> currLocation, QHash<QPair<int, int>, Piece*> gameBoard){
    QList<QPair<int, int>> validLocations;
    if (pieceType == BLACK_KNIGHT) {
        checkPiece(currLocation.first + 2, currLocation.second + 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first + 2, currLocation.second - 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first - 2, currLocation.second + 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first - 2, currLocation.second - 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first + 1, currLocation.second + 2, true, gameBoard, validLocations);
        checkPiece(currLocation.first + 1, currLocation.second - 2, true, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second + 2, true, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second - 2, true, gameBoard, validLocations);
    }

    else if (pieceType == WHITE_KNIGHT) {
        checkPiece(currLocation.first + 2, currLocation.second + 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first + 2, currLocation.second - 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first - 2, currLocation.second + 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first - 2, currLocation.second - 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first + 1, currLocation.second + 2, false, gameBoard, validLocations);
        checkPiece(currLocation.first + 1, currLocation.second - 2, false, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second + 2, false, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second - 2, false, gameBoard, validLocations);
    }

    else if (pieceType == BLACK_BISHOP) {
        bishopMoves(true, currLocation, gameBoard, validLocations);
    }

    else if (pieceType == WHITE_BISHOP) {
        bishopMoves(false, currLocation, gameBoard, validLocations);
    }

    else if (pieceType == BLACK_ROOK) {
        rookMoves(true, currLocation, gameBoard, validLocations);
    }

    else if (pieceType == WHITE_ROOK) {
        rookMoves(false, currLocation, gameBoard, validLocations);
    }

    else if (pieceType == BLACK_PAWN) {
        // Pawn gets custom logic (yay)
        if(freshPawn){
            // Check two moves
            if(checkInbounds(currLocation.first - 2, currLocation.second)){
                QPair<int, int> nextLocation(currLocation.first - 1, currLocation.second);
                if(!gameBoard.contains(nextLocation)){
                    validLocations.append(nextLocation);
                }
            }
        }
        // Check One Move
        if(checkInbounds(currLocation.first - 1, currLocation.second)){
            QPair<int, int> nextLocation(currLocation.first - 1, currLocation.second);
            if(!gameBoard.contains(nextLocation)){
                validLocations.append(nextLocation);
            }
        }
        // Check diagonal capture
        if(checkInbounds(currLocation.first - 1, currLocation.second - 1)){
            QPair<int, int> nextLocation(currLocation.first - 1, currLocation.second - 1);
            if(gameBoard.contains(nextLocation)){
                if(whitePiece(gameBoard[nextLocation])){
                    validLocations.append(nextLocation);
                }
            }
        }
        if(checkInbounds(currLocation.first - 1, currLocation.second + 1)){
            QPair<int, int> nextLocation(currLocation.first - 1, currLocation.second + 1);
            if(gameBoard.contains(nextLocation)){
                if(whitePiece(gameBoard[nextLocation])){
                    validLocations.append(nextLocation);
                }
            }
        }
    }

    else if (pieceType == WHITE_PAWN) {
        // Pawn gets custom logic (yay)
        if(freshPawn){
            // Check two moves
            if(checkInbounds(currLocation.first - 2, currLocation.second)){
                QPair<int, int> nextLocation(currLocation.first - 1, currLocation.second);
                if(!gameBoard.contains(nextLocation)){
                    validLocations.append(nextLocation);
                }
            }
        }
        // Check One Move
        if(checkInbounds(currLocation.first - 1, currLocation.second)){
            QPair<int, int> nextLocation(currLocation.first - 1, currLocation.second);
            if(!gameBoard.contains(nextLocation)){
                validLocations.append(nextLocation);
            }
        }
        // Check diagonal capture
        if(checkInbounds(currLocation.first - 1, currLocation.second - 1)){
            QPair<int, int> nextLocation(currLocation.first - 1, currLocation.second - 1);
            if(gameBoard.contains(nextLocation)){
                if(blackPiece(gameBoard[nextLocation])){
                    validLocations.append(nextLocation);
                }
            }
        }
        if(checkInbounds(currLocation.first - 1, currLocation.second + 1)){
            QPair<int, int> nextLocation(currLocation.first - 1, currLocation.second + 1);
            if(gameBoard.contains(nextLocation)){
                if(blackPiece(gameBoard[nextLocation])){
                    validLocations.append(nextLocation);
                }
            }
        }
    }

    else if (pieceType == BLACK_KING) {
        checkPiece(currLocation.first + 1, currLocation.second, true, gameBoard, validLocations);
        checkPiece(currLocation.first + 1, currLocation.second + 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first + 1, currLocation.second - 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second, true, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second + 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second - 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first, currLocation.second + 1, true, gameBoard, validLocations);
        checkPiece(currLocation.first, currLocation.second - 1, true, gameBoard, validLocations);
    }

    else if (pieceType == WHITE_KING) {
        checkPiece(currLocation.first + 1, currLocation.second, false, gameBoard, validLocations);
        checkPiece(currLocation.first + 1, currLocation.second + 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first + 1, currLocation.second - 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second, false, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second + 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first - 1, currLocation.second - 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first, currLocation.second + 1, false, gameBoard, validLocations);
        checkPiece(currLocation.first, currLocation.second - 1, false, gameBoard, validLocations);
    }

    else if (pieceType == BLACK_QUEEN) {
        rookMoves(true, currLocation, gameBoard, validLocations);
        bishopMoves(true, currLocation, gameBoard, validLocations);
    }

    else if (pieceType == WHITE_QUEEN) {
        rookMoves(false, currLocation, gameBoard, validLocations);
        bishopMoves(false, currLocation, gameBoard, validLocations);
    }
    return validLocations;
}

bool Piece::checkInbounds(int nextY, int nextX){
    if((nextY < 1) ||
       (nextY > 8) ||
       (nextX < 1) ||
       (nextX > 8)){
        return false;
    }
    return true;
}

bool Piece::whitePiece(Piece* piece){
    if(piece->pieceType == WHITE_KING||
        piece->pieceType == WHITE_QUEEN||
        piece->pieceType == WHITE_ROOK||
        piece->pieceType == WHITE_BISHOP||
        piece->pieceType == WHITE_KNIGHT||
        piece->pieceType == WHITE_PAWN){
        return true;
    }
    return false;
}

bool Piece::blackPiece(Piece* piece){
    if(piece->pieceType == BLACK_KING||
        piece->pieceType == BLACK_QUEEN||
        piece->pieceType == BLACK_ROOK||
        piece->pieceType == BLACK_BISHOP||
        piece->pieceType == BLACK_KNIGHT||
        piece->pieceType == BLACK_PAWN){
        return true;
    }
    return false;
}

bool Piece::checkPiece(int nextX, int nextY, bool black, QHash<QPair<int, int>, Piece*> gameBoard, QList<QPair<int, int>> validLocations){
    if(checkInbounds(nextY, nextX)){
        QPair<int, int> nextLocation(nextY, nextX);
        if(gameBoard.contains(nextLocation)){
            if(black){
                if(whitePiece(gameBoard[nextLocation])){
                    validLocations.append(nextLocation);
                    return true;
                }
            }else{
                if(blackPiece(gameBoard[nextLocation])){
                    validLocations.append(nextLocation);
                    return true;
                }
            }
        }else{
            validLocations.append(nextLocation);
            return true;
        }
    }
    return false;
}

void Piece::rookMoves(bool black, QPair<int,int> currLocation, QHash<QPair<int, int>, Piece*> gameBoard, QList<QPair<int, int>> validLocations){
    // Search Right
    int offsetX = 1;
    int offsetY = 0;
    bool clear = true;
    while(clear){
        clear = checkPiece(currLocation.first + offsetY, currLocation.second + offsetX, black, gameBoard, validLocations);
        offsetX++;
    }
    // Search Down
    offsetX = 0;
    offsetY = -1;
    clear = true;
    while(clear){
        clear = checkPiece(currLocation.first + offsetY, currLocation.second + offsetX, black, gameBoard, validLocations);
        offsetY--;
    }
    // Left
    offsetX = -1;
    clear = true;
    while(clear){
        clear = checkPiece(currLocation.first + offsetY, currLocation.second + offsetX, black, gameBoard, validLocations);
        offsetX--;
    }
    // Search Up
    offsetY = 1;
    clear = true;
    while(clear){
        clear = checkPiece(currLocation.first + offsetY, currLocation.second + offsetX, black, gameBoard, validLocations);
        offsetY++;
    }
}

void Piece::bishopMoves(bool black, QPair<int,int> currLocation, QHash<QPair<int, int>, Piece*> gameBoard, QList<QPair<int, int>> validLocations){
    // Search Up and Right
    int offsetX = 1;
    int offsetY = 1;
    bool clear = true;
    while(clear){
        clear = checkPiece(currLocation.first + offsetY, currLocation.second + offsetX, black, gameBoard, validLocations);
        offsetX++;
        offsetY++;
    }
    // Search Down and Right
    offsetX = 1;
    offsetY = -1;
    clear = true;
    while(clear){
        clear = checkPiece(currLocation.first + offsetY, currLocation.second + offsetX, black, gameBoard, validLocations);
        offsetX++;
        offsetY--;
    }
    // Search Up and Left
    offsetX = -1;
    offsetY = 1;
    clear = true;
    while(clear){
        clear = checkPiece(currLocation.first + offsetY, currLocation.second + offsetX, black, gameBoard, validLocations);
        offsetX--;
        offsetY++;
    }
    // Search Down and Left
    offsetX = -1;
    offsetY = -1;
    clear = true;
    while(clear){
        clear = checkPiece(currLocation.first + offsetY, currLocation.second + offsetX, black, gameBoard, validLocations);
        offsetX--;
        offsetY--;
    }
}

