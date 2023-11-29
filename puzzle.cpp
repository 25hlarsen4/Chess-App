
#include "puzzle.h"
#include "qpainter.h"

Puzzle::Puzzle(QWidget *parent)
    : QWidget{parent}
{

}

// have enum specifying which puzzle to create
Puzzle::Puzzle(PuzzleType pt, QWidget *parent)
    : QWidget{parent}
{
    background = QImage(":/backgrounds/Images/blankBoard.jpg");

    puzzleType = pt;
    currSequenceIndex = 0;
    selecting = true;
    moving = false;

    if (puzzleType == Puzzle1) {
        setUpPuzzle1();
    }

    else if (puzzleType == Puzzle2) {
        setUpPuzzle2();
    }

    else if (puzzleType == Puzzle3) {
        setUpPuzzle3();
    }

    else if (puzzleType == Puzzle4) {
        setUpPuzzle4();
    }

    else if (puzzleType == Puzzle5) {
        setUpPuzzle5();
    }

    else if (puzzleType == Puzzle6) {
        setUpPuzzle6();
    }

    createBoard();
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

            connect(space, &QPushButton::clicked, this, &Puzzle::selectSpace);

            layout->addWidget(space, i, j);
            setLayout(layout);


            // now set the pieces and correct moves

            if (boardSetUp.contains(qMakePair(i, j))) {
                Piece* piece = new Piece(boardSetUp[qMakePair(i, j)]);
                piece->setPiece(space);      //(have piece have qlabel member)
                piecePositions[qMakePair(i, j)] = piece;
            }

        }
    }
}


void Puzzle::selectSpace(){
    QPushButton *selectedSpace = qobject_cast<QPushButton*>(sender());

    QPair<int, int> buttonCoords = qMakePair(selectedSpace->property("row").toInt(), selectedSpace->property("col").toInt());

    if (selecting) {
        // only select if there's a piece in the space
        if (piecePositions.contains(buttonCoords)) {
            selectedPiece = piecePositions[buttonCoords];

            prevPiecePos = buttonCoords;
            potentialLocations = selectedPiece->getPossibleLocations(prevPiecePos, piecePositions);
            selecting = false;
            moving = true;
            currSequenceIndex++;
        }
    }
    else if (moving) {
        QPair<int, int> clickPos = qMakePair(selectedSpace->property("row").toInt(), selectedSpace->property("col").toInt());

        // if a valid move
        if (potentialLocations.contains(clickPos)) {
            // check that it's also the right move for the puzzle
            if (clickPos == correctClickSequence[currSequenceIndex]) {
                // hide where the piece used to be (should always contain just check just in case)
                if (piecePositions.contains(prevPiecePos)) {
                    // call piece.hide() on the corresponding piece
                    Piece* piece = piecePositions[prevPiecePos];
                    piece->hide();

                    // accept the move and update accordingly
                    // update map, setPiece label
                    piecePositions.remove(prevPiecePos);
                    piecePositions[clickPos] = piece;

                    piece->setPiece(selectedSpace);

                    currSequenceIndex++;
                }
            }
        }
    }
}


void Puzzle::setUpPuzzle1() {
    boardSetUp[qMakePair(1, 1)] = Piece::BLACK_BISHOP;
    boardSetUp[qMakePair(2, 1)] = Piece::BLACK_PAWN;

    correctClickSequence.append(qMakePair(1, 1));
    correctClickSequence.append(qMakePair(2, 2));
}

void Puzzle::setUpPuzzle2() {

}
void Puzzle::setUpPuzzle3() {

}
void Puzzle::setUpPuzzle4() {

}
void Puzzle::setUpPuzzle5() {

}
void Puzzle::setUpPuzzle6() {

}
