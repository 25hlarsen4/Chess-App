#include "puzzle.h"
#include "qpainter.h"

// have enum specifying which puzzle to create
Puzzle::Puzzle(QWidget *parent)
    : QWidget{parent}
{
    background = QImage(":/backgrounds/Images/blankBoard.jpg");

    // just fully populate board with pieces for now
    for (char letter = 'a'; letter < 'i'; letter++) {
        for (int num = 1; num < 9; num++) {
            piecePositions[qMakePair(letter, num)] = new Piece(Piece::BLACK_KNIGHT);
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

    // a1 maps to 50, 50
    x = 59;
    y = 59;
    for (char letter = 'a'; letter < 'i'; letter++) {
        for (int num = 1; num < 9; num++) {
            QPair<char, int> chessCoords = qMakePair(letter, num);
            if (piecePositions.contains(chessCoords)) {
                QRect pieceTarget(x, y, 60, 60);
                painter.drawImage(pieceTarget, piecePositions[chessCoords]->pieceImage);
            }
            x += 58;
        }
        // reset x
        x = 59;
        y += 58;
    }
}
