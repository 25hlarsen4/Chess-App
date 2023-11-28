#include "piece.h"

Piece::Piece(QObject *parent)
    : QObject{parent}
{
    // all pieces are just knights for now
    pieceImage = QImage(":/backgrounds/Images/knight.png");
}
void Piece::setKnight(QPushButton *space){
    QLabel *pieceLabel = new QLabel(space);
    pieceLabel->setPixmap(QPixmap(":/backgrounds/Images/knight.png"));
    pieceLabel->setScaledContents(true);
    pieceLabel->setGeometry(0, 0, space->width(), space->height());
    pieceLabel->show();
}
