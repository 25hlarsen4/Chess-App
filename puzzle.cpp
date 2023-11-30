
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

    QVBoxLayout *vLayout = new QVBoxLayout(); // the layout that contains the menu bar and the board

    // The menu bar
    QWidget *menuBarBackground = new QWidget(); // menu bar background
    menuBarBackground->setStyleSheet("background-color: white;");

    QHBoxLayout *menubarLayout = new QHBoxLayout(menuBarBackground); // menu bar

    QPushButton* goBackButton = new QPushButton(); //goBackButton
    goBackButton->setMinimumSize(50, 50);
    goBackButton->setMaximumSize(50, 50);
    goBackButton->setStyleSheet("QPushButton { background-color: white; color: black; border: none; }");
    QPixmap pieceImage(":/backgrounds/Images/back.png");
    QPixmap scaledPieceImage = pieceImage.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    goBackButton->setIcon(QIcon(scaledPieceImage));
    goBackButton->setIconSize(QSize(50, 50));
    goBackButton->show();
    connect(goBackButton, &QPushButton::clicked, this, &Puzzle::onGoBackButtonClicked); // calls the slot to emit signal to update view in the control class

    menubarLayout->addWidget(goBackButton);
    menubarLayout->addStretch();
    menuBarBackground->setLayout(menubarLayout);

    vLayout->addWidget(menuBarBackground);

    //The board
    layout = new QGridLayout();
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    // Vertical spacers
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 8, 8, 0);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 0, 8, 0);

    // Horizontal spacers
    layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 8, 8, 0);
    layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 0, 8, 0);

    for(int i = 7; i >= 0; i--){
        for(int j = 7; j >= 0; j--){

            QPushButton *space = new QPushButton(this);

            space->setProperty("row", j);
            space->setProperty("col", i);

            if((i + j) % 2 == 0) space->setStyleSheet("background-color: white;");
            else space->setStyleSheet("background-color: brown;");

            space->setFixedSize(70,70);

            connect(space, &QPushButton::clicked, this, &Puzzle::selectSpace);

            layout->addWidget(space, j, i);
            //setLayout(layout);


            // now set the pieces and correct moves

            if (boardSetUp.contains(qMakePair(i, j))) {
                Piece* piece = new Piece(boardSetUp[qMakePair(i, j)]);
                piece->setPiece(space);      //(have piece have qlabel member)
                piecePositions[qMakePair(i, j)] = piece;
            }

        }
    }

    vLayout->addLayout(layout);
    this->setLayout(vLayout);
}


void Puzzle::selectSpace(){
    QPushButton *selectedSpace = qobject_cast<QPushButton*>(sender());
    QPair<int, int> buttonCoords = qMakePair(selectedSpace->property("row").toInt(), selectedSpace->property("col").toInt());
    for(auto& location : potentialLocations){
        setButtonBackgroundColor(location.first, location.second, "");
    }
    setButtonBackgroundColor(prevPiecePos.first, prevPiecePos.second, "");
    qDebug() << "row: " << selectedSpace->property("row").toInt();
    qDebug() << "col: " << selectedSpace->property("col").toInt();
    if (selecting) {
        // only select if there's a piece in the space
        if (piecePositions.contains(buttonCoords)) {


            setButtonBackgroundColor(selectedSpace->property("row").toInt(), selectedSpace->property("row").toInt(), "rgb(0,255,0)");

            selectedPiece = piecePositions[buttonCoords];

            prevPiecePos = buttonCoords;
            potentialLocations = selectedPiece->getPossibleLocations(prevPiecePos, piecePositions);
            selecting = false;
            moving = true;
            currSequenceIndex++;

            for(auto& location : potentialLocations){
                setButtonBackgroundColor(location.first, location.second, "rgb(0,255,0)");
            }
        }
    }
    else if (moving) {
        QPair<int, int> clickPos = qMakePair(selectedSpace->property("row").toInt(), selectedSpace->property("col").toInt());

        // if a valid move
        if (potentialLocations.contains(clickPos)) {
            // check that it's also the right move for the puzzle
            qDebug() << currSequenceIndex;
            qDebug() << "correctClickSequence: " << correctClickSequence.size();
            if (clickPos == correctClickSequence[currSequenceIndex]) {
                if (piecePositions.contains(prevPiecePos)) {
                    Piece* piece = piecePositions[prevPiecePos];
                    piece->hide();

                    // accept the move and update accordingly
                    // update map, setPiece label
                    piecePositions.remove(prevPiecePos);

                    // hide piece if we're capturing one
                    if (piecePositions.contains(clickPos)) {
                        piecePositions[clickPos]->hide();
                        // should we delete the piece here?
                    }
                    // this will replace if need be (if capturing)
                    piecePositions.insert(clickPos, piece);

                    piece->setPiece(selectedSpace);
                    for(auto& location : potentialLocations){
                        setButtonBackgroundColor(location.first, location.second, "");
                    }
                    setButtonBackgroundColor(prevPiecePos.first, prevPiecePos.second, "");


                    qDebug() << piecePositions;

                    moving = false;
                    selecting = true;
                    currSequenceIndex++;
                    if (currSequenceIndex == correctClickSequence.size()) {
                        // we're done, send success signal
                        qDebug() << "puzzle complete";
                    }
                }
            }
        }
    }
}

void Puzzle::onGoBackButtonClicked(){
    qDebug() << "Go Back button was clicked in Puzzle";
    emit goBackButtonClicked();
}
void Puzzle::setButtonBackgroundColor(int row, int col, QString color){

    for (int i = 0; i < layout->count(); ++i) {

        if(QPushButton *button = qobject_cast<QPushButton*>(layout->itemAt(i)->widget())){

            if(button->property("row").toInt() == row && button->property("col").toInt() == col){

                button->setStyleSheet(QString("background-color: %1;").arg(color));

            }

        }

    }

}


void Puzzle::setUpPuzzle1() {
    boardSetUp[qMakePair(1, 1)] = Piece::BLACK_BISHOP;
    boardSetUp[qMakePair(2, 2)] = Piece::WHITE_PAWN;

    correctClickSequence.append(qMakePair(1, 1));
    correctClickSequence.append(qMakePair(2, 2));
    correctClickSequence.append(qMakePair(2, 2));
    correctClickSequence.append(qMakePair(3, 3));
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
