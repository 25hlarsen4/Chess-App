#include <QMouseEvent>
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

    // The Hint part on UI
    QPushButton* helpButton = new QPushButton(this);
    helpButton->setGeometry(600, 100, 180, 25);
    helpButton->setText("Stuck? Click to reveal move.");
    helpButton->setStyleSheet("QPushButton { background-color: red; color: black; border: none; }");
    helpButton->show();
    connect(helpButton, &QPushButton::clicked, this, &Puzzle::onHelpButtonClicked);
    revealedMove = new QLabel(this);
    revealedMove->setStyleSheet("QLabel { background-color: white; color: black; border: none; }");
    revealedMove->setGeometry(600, 130, 180, 25);
    revealedMove->setText("");
    revealedMove->show();
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

    feedbackLabel = new QLabel(); // the feedbackLabel
    menubarLayout->addWidget(feedbackLabel);
    menubarLayout->addStretch();
    menuBarBackground->setLayout(menubarLayout);

    vLayout->addWidget(menuBarBackground);

    QHBoxLayout* rowsAndBoard = new QHBoxLayout();
    QVBoxLayout* spaceForRows = new QVBoxLayout();
    for (int i = 8; i > 0; i--) {
        QLabel* lab = new QLabel(this);
        lab->setStyleSheet("QLabel { color: white; }");
        lab->setText(QString::number(i));
        lab->show();
        spaceForRows->addWidget(lab);
    }

    QWidget *controlsRestrictorWidget = new QWidget();
    QHBoxLayout* spaceForCols = new QHBoxLayout();
    for (int i = 97; i < 105; i++) {
        QLabel* lab = new QLabel(this);
        lab->setStyleSheet("QLabel { color: white; }");
        lab->setAlignment(Qt::AlignCenter);
        lab->setText(QChar(i));
        lab->show();
        spaceForCols->addWidget(lab);
    }
    controlsRestrictorWidget->setLayout(spaceForCols);
    controlsRestrictorWidget->setMaximumWidth(540);

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

            space->setFixedSize(65,65);

            connect(space, &QPushButton::clicked, this, &Puzzle::selectSpace);

            layout->addWidget(space, j, i);

            // now set the pieces and correct moves

            if (boardSetUp.contains(qMakePair(j, i))) {
                Piece* piece = new Piece(boardSetUp[qMakePair(j, i)]);
                piece->setPiece(space);      //(have piece have qlabel member)
                piecePositions[qMakePair(j, i)] = piece;
            }
        }
    }

    // The numbers indicating rows and columns on screen
    rowsAndBoard->addLayout(spaceForRows);
    rowsAndBoard->addLayout(layout);
    vLayout->addLayout(rowsAndBoard);
    vLayout->addWidget(controlsRestrictorWidget);
    this->setLayout(vLayout);
}

void Puzzle::mousePressEvent(QMouseEvent * e) {
    qDebug() << e->pos().x();
    qDebug() << e->pos().y();
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
            // clear help message if there was one
            revealedMove->setText("");

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
                // clear help message if there was one
                revealedMove->setText("");

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
                        feedbackLabel->setStyleSheet("background-color: orange; color: white");
                        if (puzzleType == Puzzle1) {
                            emit puzzleComplete(1);
                        }

                        else if (puzzleType == Puzzle2) {
                            emit puzzleComplete(2);
                        }

                        else if (puzzleType == Puzzle3) {
                            emit puzzleComplete(3);
                        }

                        else if (puzzleType == Puzzle4) {
                            emit puzzleComplete(4);
                        }

                        else if (puzzleType == Puzzle5) {
                            emit puzzleComplete(5);
                        }

                        else if (puzzleType == Puzzle6) {
                            emit puzzleComplete(6);
                        }
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
    currSequenceIndex = 0;
    computerMovesIndex = 0;

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

void Puzzle::onHelpButtonClicked() {
    QPair<int, int> pieceCoords;
    if (selecting) {
        pieceCoords = correctClickSequence[currSequenceIndex];
    }
    else if (moving) {
        pieceCoords = correctClickSequence[currSequenceIndex - 1];
    }

    QString helpMessage;

    Piece* piece = piecePositions[pieceCoords];

    QString pieceType;
    if (piece->pieceType == Piece::BLACK_QUEEN || piece->pieceType == Piece::WHITE_QUEEN) {
        pieceType = "queen";
    }
    else if (piece->pieceType == Piece::BLACK_KING || piece->pieceType == Piece::WHITE_KING) {
        pieceType = "king";
    }
    else if (piece->pieceType == Piece::BLACK_ROOK || piece->pieceType == Piece::WHITE_ROOK) {
        pieceType = "rook";
    }
    else if (piece->pieceType == Piece::BLACK_BISHOP || piece->pieceType == Piece::WHITE_BISHOP) {
        pieceType = "bishop";
    }
    else if (piece->pieceType == Piece::BLACK_KNIGHT || piece->pieceType == Piece::WHITE_KNIGHT) {
        pieceType = "knight";
    }
    else if (piece->pieceType == Piece::BLACK_PAWN || piece->pieceType == Piece::WHITE_PAWN) {
        pieceType = "pawn";
    }


    if (selecting) {
        helpMessage = "Select " + pieceType + " on " + QChar(97 + pieceCoords.second) + QString::number(8 - pieceCoords.first);
    }
    else if (moving) {
        helpMessage = "Move " + pieceType + " to " + QChar(97 + correctClickSequence[currSequenceIndex].second) + QString::number(8 - correctClickSequence[currSequenceIndex].first);
    }

    revealedMove->setText(helpMessage);
}

/**
 * @brief Puzzle::setUpPuzzle1
 * This method sets up the chess board and moves for a fork puzzle.
 */
void Puzzle::setUpPuzzle1() {

    boardSetUp.clear();
    correctClickSequence.clear();
    computerMoves.clear();

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

/**
 * @brief Puzzle::setUpPuzzle5
 * doubling pinned king. end game puzzle.
 */
void Puzzle::setUpPuzzle5() {

    boardSetUp[qMakePair(0, 3)] = Piece::BLACK_KING;
    boardSetUp[qMakePair(0, 0)] = Piece::BLACK_ROOK;
    boardSetUp[qMakePair(0, 7)] = Piece::BLACK_ROOK;
    boardSetUp[qMakePair(2, 4)] = Piece::BLACK_BISHOP;
    boardSetUp[qMakePair(4, 1)] = Piece::BLACK_BISHOP;
    boardSetUp[qMakePair(1, 3)] = Piece::BLACK_KNIGHT;
    boardSetUp[qMakePair(4, 4)] = Piece::BLACK_KNIGHT;
    boardSetUp[qMakePair(1, 0)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 1)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(2, 2)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 5)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 6)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(1, 7)] = Piece::BLACK_PAWN;

    boardSetUp[qMakePair(7, 2)] = Piece::WHITE_KING;
    boardSetUp[qMakePair(7, 3)] = Piece::WHITE_ROOK;
    boardSetUp[qMakePair(7, 7)] = Piece::WHITE_ROOK;
    boardSetUp[qMakePair(4, 5)] = Piece::WHITE_BISHOP;
    boardSetUp[qMakePair(6, 4)] = Piece::WHITE_BISHOP;
    boardSetUp[qMakePair(4, 0)] = Piece::WHITE_KNIGHT;
    boardSetUp[qMakePair(7, 6)] = Piece::WHITE_KNIGHT;
    boardSetUp[qMakePair(6, 0)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 1)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 2)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 6)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 7)] = Piece::WHITE_PAWN;

    setPlayerPieces();

    correctClickSequence.append(qMakePair(7, 3));
    correctClickSequence.append(qMakePair(4, 3));
    correctClickSequence.append(qMakePair(4, 3));
    correctClickSequence.append(qMakePair(4, 1));
    correctClickSequence.append(qMakePair(4, 1));
    correctClickSequence.append(qMakePair(1, 1));
    correctClickSequence.append(qMakePair(4, 5));
    correctClickSequence.append(qMakePair(1, 2));
    correctClickSequence.append(qMakePair(1, 1));
    correctClickSequence.append(qMakePair(1, 0));
    correctClickSequence.append(qMakePair(1, 0));
    correctClickSequence.append(qMakePair(0, 0));
    correctClickSequence.append(qMakePair(0, 0));
    correctClickSequence.append(qMakePair(7, 7));

    computerMoves.append(qMakePair(4, 4));
    computerMoves.append(qMakePair(6, 5));
    computerMoves.append(qMakePair(6, 5));
    computerMoves.append(qMakePair(7, 7));
    computerMoves.append(qMakePair(7, 7));
    computerMoves.append(qMakePair(6, 5));
    computerMoves.append(qMakePair(0, 3));
    computerMoves.append(qMakePair(0, 2));
    computerMoves.append(qMakePair(4, 2));
    computerMoves.append(qMakePair(2, 0));
    computerMoves.append(qMakePair(0, 2));
    computerMoves.append(qMakePair(1, 2));

}
void Puzzle::setUpPuzzle6() {
    boardSetUp[qMakePair(1, 0)] = Piece::BLACK_KING;
    boardSetUp[qMakePair(1, 3)] = Piece::BLACK_ROOK;
    boardSetUp[qMakePair(2, 1)] = Piece::BLACK_ROOK;
    boardSetUp[qMakePair(1, 5)] = Piece::BLACK_BISHOP;
    boardSetUp[qMakePair(1, 6)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(2, 5)] = Piece::BLACK_PAWN;
    boardSetUp[qMakePair(2, 7)] = Piece::BLACK_PAWN;

    boardSetUp[qMakePair(7, 7)] = Piece::WHITE_KING;
    boardSetUp[qMakePair(4, 2)] = Piece::WHITE_ROOK;
    boardSetUp[qMakePair(3, 2)] = Piece::WHITE_KNIGHT;
    boardSetUp[qMakePair(4, 3)] = Piece::WHITE_KNIGHT;
    boardSetUp[qMakePair(5, 4)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(5, 7)] = Piece::WHITE_PAWN;
    boardSetUp[qMakePair(6, 6)] = Piece::WHITE_PAWN;

    setPlayerPieces();

    correctClickSequence.append(qMakePair(4, 2));
    correctClickSequence.append(qMakePair(4, 0));
    correctClickSequence.append(qMakePair(3, 2));
    correctClickSequence.append(qMakePair(1, 3));
    correctClickSequence.append(qMakePair(1, 3));
    correctClickSequence.append(qMakePair(2, 1));

    computerMoves.append(qMakePair(1, 0));
    computerMoves.append(qMakePair(0, 1));
    computerMoves.append(qMakePair(0, 1));
    computerMoves.append(qMakePair(1, 1));


}
void Puzzle::nextMove(){

    this->setEnabled(false);
    QTimer::singleShot(4000, this, [this]() {
        this->setEnabled(true);
    });
    feedbackLabel->setText("Correct move!");
    feedbackLabel->setStyleSheet("background-color: green; color: white;");

    Piece* piece = piecePositions[computerMoves[computerMovesIndex]];

    computerMovesIndex++;

    for(QPushButton* button : allButtons){
        if(button->property("row") == computerMoves[computerMovesIndex].first
            && button->property("col") == computerMoves[computerMovesIndex].second){

            QTimer::singleShot(2000, this, [this, piece, button] {
                piece->hide();
                piece->setPiece(button);
            });
        }

    }

    piecePositions.remove(computerMoves[computerMovesIndex]);
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
