#include "puzzle.h"
#include "qpainter.h"

Puzzle::Puzzle(QWidget *parent)
    : QWidget{parent}
{
    background = QImage(":/backgrounds/Images/blankBoard.jpg");

    // just fully populate board with pieces for now
    for (int letter = 97; letter < 105; letter++) {
        for (int num = 1; num < 9; num++) {
            piecePositions[qMakePair(letter, num)] = new Piece;
        }
    }
}

void Puzzle::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    int x = 3;
    int y = 3;
    int w = 580;
    int h = 580;
    QRect target(x, y, w, h);

    painter.drawImage(target, background);

    // just draw the first piece as a test
    QRect pieceTarget(50, 50, 80, 80);
    painter.drawImage(pieceTarget, piecePositions[qMakePair('a', 1)]->pieceImage);
}
