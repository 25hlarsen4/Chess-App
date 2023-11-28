
#include "puzzle.h"
#include "qpainter.h"

// have enum specifying which puzzle to create
Puzzle::Puzzle(QWidget *parent)
    : QWidget{parent}
{
    background = QImage(":/backgrounds/Images/blankBoard.jpg");

    createBoard();

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

    //painter.drawImage(target, background);

    // just draw the first piece as a test
    QRect pieceTarget(50, 50, 80, 80);
    //painter.drawImage(pieceTarget, piecePositions[qMakePair('a', 1)]->pieceImage);
}
void Puzzle::createBoard(){

    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    // Vertical spacers
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 8, 8, 0);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 0, 8, 0);

    // Horizontal spacers
    layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 8, 8, 0);
    layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 0, 8, 0);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

            QPushButton *space = new QPushButton(this);

            space->setProperty("row", i);
            space->setProperty("col", j);

            if((i + j) % 2 == 0) space->setStyleSheet("background-color: white;");
            else space->setStyleSheet("background-color: brown;");

            space->setFixedSize(70,70);

            Piece piece(Piece::BLACK_KNIGHT);

            if(i == 0 && j == 0)
                piece.setKnight(space);


            connect(space, &QPushButton::clicked, this, &Puzzle::selectSpace);

            layout->addWidget(space, i, j);
            setLayout(layout);

        }
    }
}
void Puzzle::setPiece(QPushButton *space){



}
void Puzzle::selectSpace(){
    Piece piece(Piece::BLACK_KNIGHT);
    QPushButton *selectedSpace = qobject_cast<QPushButton*>(sender());
    piece.setKnight(selectedSpace);
}
