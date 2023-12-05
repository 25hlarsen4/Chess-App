
#include "puzzle.h"
#include "qpainter.h"
#include <QTimer>
#include <memory>

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
    computerMovesIndex = 0;
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
    feedbackLabel = new QLabel();

    menubarLayout->addWidget(feedbackLabel);
    menubarLayout->addStretch();
    menuBarBackground->setLayout(menubarLayout);

    vLayout->addWidget(menuBarBackground);



    //The board
    layout = new QGridLayout();
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    // Vertical spacers
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 8, 1, 1);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 8, 1, 1);

    // Horizontal spacers
    layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 8, 1, 1);
    layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 8, 1, 1);

    for(int i = 7; i >= 0; i--){
        for(int j = 7; j >= 0; j--){

            QPushButton *space = new QPushButton(this);

            space->setProperty("row", j);
            space->setProperty("col", i);


            if((i + j) % 2 == 0){

                space->setStyleSheet("background-color: white;");
                space->setProperty("color", "white");
            }
            else {
                space->setStyleSheet("background-color: brown;");
                space->setProperty("color", "brown");
            }
            allButtons.append(space);

            space->setFixedSize(70,70);

            connect(space, &QPushButton::clicked, this, &Puzzle::selectSpace);

            layout->addWidget(space, j, i);
            //setLayout(layout);


            // now set the pieces and correct moves

            if (boardSetUp.contains(qMakePair(j, i))) {
                Piece* piece = new Piece(boardSetUp[qMakePair(j, i)]);
                piece->setPiece(space);      //(have piece have qlabel member)
                piecePositions[qMakePair(j, i)] = piece;
            }

        }
    }

    vLayout->addLayout(layout);
    this->setLayout(vLayout);
}


void Puzzle::selectSpace(){
    QPushButton *selectedSpace = qobject_cast<QPushButton*>(sender());
    QPair<int, int> buttonCoords = qMakePair(selectedSpace->property("row").toInt(), selectedSpace->property("col").toInt());

    for(auto& button : allButtons){
        setButtonBackgroundColor(button->property("row").toInt(), button->property("col").toInt(), button->property("color").toString());
    }

    if (selecting) {
        // only select if there's a piece in the space & it's the correct selection
        if (piecePositions.contains(buttonCoords) && playerPieces.contains(buttonCoords)) {

            setButtonBackgroundColor(selectedSpace->property("row").toInt(), selectedSpace->property("col").toInt(), "rgb(0,255,0)");

            selectedPiece = piecePositions[buttonCoords];
            prevPiecePos = buttonCoords;
            potentialLocations = selectedPiece->getPossibleLocations(prevPiecePos, piecePositions);

            for(auto& location : potentialLocations){
                setButtonBackgroundColor(location.first, location.second, "rgb(0,255,0)");
            }

            selecting = false;
            moving = true;
            currSequenceIndex++;

        }
    }
    else if (moving) {
        // if a valid move
        if (potentialLocations.contains(buttonCoords)) {
            // check that it's also the right move for the puzzle
            if (piecePositions.contains(prevPiecePos)) {
                Piece* piece = piecePositions[prevPiecePos];
                piece->hide();

                // accept the move and update accordingly
                // update map, setPiece label
                piecePositions.remove(prevPiecePos);
                playerPieces.remove(prevPiecePos);

                // hide piece if we're capturing one
                if (piecePositions.contains(buttonCoords)) {
                    piecePositions[buttonCoords]->hide();
                    // should we delete the piece here?
                }
                // this will replace if need be (if capturing)
                piecePositions.insert(buttonCoords, piece);
                playerPieces.insert(buttonCoords,piece->pieceType);


                piece->setPiece(selectedSpace);

                if (buttonCoords == correctClickSequence[currSequenceIndex]) {

                    currSequenceIndex++;

                    feedbackLabel->setText("Correct move!");
                    feedbackLabel->setStyleSheet("background-color: green; color: white");

                    if (currSequenceIndex == correctClickSequence.size()) {

                        feedbackLabel->setText("Puzzle Complete!");
                    }else{
                        nextMove();

                        moving = false;
                        selecting = true;

                    }



                }else{

                    feedbackLabel->setText("Incorrect move!");
                    feedbackLabel->setStyleSheet("background-color: red; color: white");

                    piecePositions.remove(buttonCoords);
                    playerPieces.remove(buttonCoords);

                    piecePositions.insert(prevPiecePos, piece);
                    playerPieces.insert(prevPiecePos,piece->pieceType);


                    QTimer::singleShot(2000, this, [this, piece] {
                        piece->hide();


                        for(QPushButton* button : allButtons){
                            if(button->property("row") == prevPiecePos.first && button->property("col") == prevPiecePos.second){
                                piece->setPiece(button);
                            }
                        }
                        feedbackLabel->setText("");
                        feedbackLabel->setStyleSheet("");

                    });

                    moving = false;
                    selecting = true;
                    currSequenceIndex--;

                }


            }
        }
        else {
            moving = false;
            selecting = true;
            currSequenceIndex--;
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

/**
 * @brief Puzzle::setUpPuzzle1
 * This method sets up the chess board and moves for a fork puzzle.
 */
void Puzzle::setUpPuzzle1() {
    boardSetUp[qMakePair(1, 1)] = Piece::BLACK_KNIGHT;
    boardSetUp[qMakePair(2, 2)] = Piece::BLACK_KING;
    boardSetUp[qMakePair(3, 0)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(3, 2)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(4, 1)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(2, 6)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(4, 7)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(4, 6)] = Piece::BLACK_ROOK;

    boardSetUp[qMakePair(6, 1)] = Piece::WHITE_KING;
    boardSetUp[qMakePair(4, 2)] = Piece::WHITE_KNIGHT;
    boardSetUp[qMakePair(1, 7)] = Piece::WHITE_ROOK;
    boardSetUp[qMakePair(3, 6)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(4, 0)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(5, 1)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 2)] = Piece::WHITE_PAWN;

    setPlayerPieces();

    correctClickSequence.append(qMakePair(4, 2));
    correctClickSequence.append(qMakePair(3, 4));
    correctClickSequence.append(qMakePair(3, 4));
    correctClickSequence.append(qMakePair(4, 6));

    computerMoves.append(qMakePair(2,2));
    computerMoves.append(qMakePair(2,1));
}
/**
 * @brief Puzzle::setUpPuzzle2
 * This method sets up the chess board and moves for a pinned queen puzzle.
 * the puzzle came from
 * "https://www.google.com/search?q=pinned+queen+puzzles+chess&rlz=1C1CHBF_enUS1043US1043&oq=pinned+&gs_lcrp=EgZjaHJvbWUqCAgAEEUYJxg7MggIABBFGCcYOzIGCAEQRRhAMgYIAhBFGDkyBwgDEAAYgAQyBwgEEAAYgAQyBwgFEAAYgAQyBwgGEAAYgAQyBwgHEAAYgATSAQgxNDU0ajFqOagCALACAA&sourceid=chrome&ie=UTF-8#fpstate=ive&vld=cid:d30812a0,vid:XIlYJjRLc_A,st:0"
 */
void Puzzle::setUpPuzzle2() {

    boardSetUp[qMakePair(0, 0)] = Piece::BLACK_ROOK;
    boardSetUp[qMakePair(0, 2)] = Piece::BLACK_BISHOP;
    boardSetUp[qMakePair(0, 4)] = Piece::BLACK_KING;
    boardSetUp[qMakePair(0, 5)] = Piece::BLACK_QUEEN;
    boardSetUp[qMakePair(1, 4)] = Piece::BLACK_BISHOP;
    boardSetUp[qMakePair(2, 2)] = Piece::BLACK_KNIGHT;
    boardSetUp[qMakePair(1, 0)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 1)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 2)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 3)] = Piece::BLACK_PAWN;

    boardSetUp[qMakePair(0, 6)] = Piece::WHITE_QUEEN;
    boardSetUp[qMakePair(5, 5)] = Piece::WHITE_KNIGHT;
    boardSetUp[qMakePair(7, 0)] = Piece::WHITE_ROOK;
    boardSetUp[qMakePair(7, 4)] = Piece::WHITE_ROOK;
    boardSetUp[qMakePair(7, 1)] = Piece::WHITE_KNIGHT;
    boardSetUp[qMakePair(7, 6)] = Piece::WHITE_KING;
    boardSetUp[qMakePair(2, 5)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 0)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 1)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 2)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 5)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 6)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 7)] = Piece::WHITE_PAWN;

    setPlayerPieces();

    correctClickSequence.append(qMakePair(7, 4));
    correctClickSequence.append(qMakePair(1, 4));
    correctClickSequence.append(qMakePair(2, 5));
    correctClickSequence.append(qMakePair(1, 5));
    correctClickSequence.append(qMakePair(0, 6));
    correctClickSequence.append(qMakePair(0, 5));

    computerMoves.append(qMakePair(2,2));
    computerMoves.append(qMakePair(1,4));
    computerMoves.append(qMakePair(0,4));
    computerMoves.append(qMakePair(0,3));

}

/**
 * @brief Puzzle::setUpPuzzle3
 * smother mate puzzle
 * got the puzzle from "https://lichess.org/study/oJ4jLe50/iGOCuCaa" - Sveshnikov - Ivanov, 1976
 */
void Puzzle::setUpPuzzle3() {

    boardSetUp[qMakePair(0, 0)] = Piece::BLACK_ROOK;
    boardSetUp[qMakePair(2, 4)] = Piece::BLACK_BISHOP;
    boardSetUp[qMakePair(0, 5)] = Piece::BLACK_KING;
    boardSetUp[qMakePair(3, 7)] = Piece::BLACK_QUEEN;
    boardSetUp[qMakePair(1, 0)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(2, 1)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 5)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 7)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(2, 6)] = Piece::BLACK_PAWN;

    boardSetUp[qMakePair(4, 5)] = Piece::WHITE_QUEEN;
    boardSetUp[qMakePair(6, 7)] = Piece::WHITE_KING;
    boardSetUp[qMakePair(4, 3)] = Piece::WHITE_BISHOP;
    boardSetUp[qMakePair(2, 2)] = Piece::WHITE_KNIGHT;
    boardSetUp[qMakePair(6, 0)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 5)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 6)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(5, 7)] = Piece::WHITE_PAWN;

    setPlayerPieces();

    correctClickSequence.append(qMakePair(4, 5));
    correctClickSequence.append(qMakePair(2, 3));
    correctClickSequence.append(qMakePair(2, 2));
    correctClickSequence.append(qMakePair(1, 4));
    correctClickSequence.append(qMakePair(1, 4));
    correctClickSequence.append(qMakePair(2, 6));
    correctClickSequence.append(qMakePair(2, 3));
    correctClickSequence.append(qMakePair(0, 5));
    correctClickSequence.append(qMakePair(2, 6));
    correctClickSequence.append(qMakePair(1, 4));

    computerMoves.append(qMakePair(0,5));
    computerMoves.append(qMakePair(0,6));
    computerMoves.append(qMakePair(0,6));
    computerMoves.append(qMakePair(0,5));
    computerMoves.append(qMakePair(0,5));
    computerMoves.append(qMakePair(0,6));
    computerMoves.append(qMakePair(0,0));
    computerMoves.append(qMakePair(0,5));

}

/**
 * @brief Puzzle::setUpPuzzle4
 * overloading puzzle
 */
void Puzzle::setUpPuzzle4() {

    boardSetUp[qMakePair(0, 7)] = Piece::BLACK_KING;
    boardSetUp[qMakePair(0, 3)] = Piece::BLACK_QUEEN;
    boardSetUp[qMakePair(6, 5)] = Piece::BLACK_ROOK;
    boardSetUp[qMakePair(1, 0)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 1)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 6)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 7)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(6, 7)] = Piece::BLACK_PAWN;

    boardSetUp[qMakePair(7, 7)] = Piece::WHITE_KING;
    boardSetUp[qMakePair(4, 6)] = Piece::WHITE_QUEEN;
    boardSetUp[qMakePair(4, 4)] = Piece::WHITE_ROOK;
    boardSetUp[qMakePair(4, 5)] = Piece::WHITE_BISHOP;
    boardSetUp[qMakePair(3, 2)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(4, 1)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(5, 2)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 0)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 6)] = Piece::WHITE_PAWN;

    setPlayerPieces();

    correctClickSequence.append(qMakePair(4, 4));
    correctClickSequence.append(qMakePair(1, 4));
    correctClickSequence.append(qMakePair(4, 6));
    correctClickSequence.append(qMakePair(0, 2));
    correctClickSequence.append(qMakePair(0, 2));
    correctClickSequence.append(qMakePair(0, 5));

    computerMoves.append(qMakePair(0,3));
    computerMoves.append(qMakePair(1,4));
    computerMoves.append(qMakePair(1,4));
    computerMoves.append(qMakePair(0,5));

}
void Puzzle::setUpPuzzle5() {

}
void Puzzle::setUpPuzzle6() {

}
void Puzzle::nextMove(){

    feedbackLabel->setText("Correct move!");
    feedbackLabel->setStyleSheet("background-color: green; color: white;");

    Piece* piece = piecePositions[computerMoves[computerMovesIndex]];
    piece->hide();
    piecePositions.remove(computerMoves[computerMovesIndex]);

    computerMovesIndex++;

    for(QPushButton* button : allButtons){
        if(button->property("row") == computerMoves[computerMovesIndex].first && button->property("col") == computerMoves[computerMovesIndex].second){
            piece->setPiece(button);
        }
    }

    piecePositions.insert(computerMoves[computerMovesIndex], piece);

    computerMovesIndex++;
}

void Puzzle::setPlayerPieces(){

    for(const auto& key : boardSetUp.keys()){

        Piece::PieceType pieceType = boardSetUp[key];
        Piece* piece = new Piece(pieceType);

        if(piece->whitePiece(piece)){
            playerPieces[key] = pieceType;
        }

    }

}
