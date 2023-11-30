#ifndef PUZZLE_H
#define PUZZLE_H

#include "piece.h"
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class Puzzle : public QWidget
{
    Q_OBJECT
public:
    enum PuzzleType
    {
        Puzzle1,
        Puzzle2,
        Puzzle3,
        Puzzle4,
        Puzzle5,
        Puzzle6
    };

    explicit Puzzle(QWidget *parent = nullptr);

    // correct moves, piece set up
    explicit Puzzle(PuzzleType, QWidget *parent = nullptr);

    PuzzleType puzzleType;

private:
    QImage background;

    QHash<QPair<int, int>, Piece::PieceType> boardSetUp;
//    QHash<QPushButton*, Piece*> spacePieceMap;
    QHash<QPair<int, int>, Piece*> piecePositions;
    QList<QPair<int, int>> correctClickSequence;
    QList<QPair<int, int>> potentialLocations;

    int currSequenceIndex;
    bool selecting;
    bool moving;
    Piece* selectedPiece;
    QPair<int, int> prevPiecePos;

    void paintEvent(QPaintEvent *);
    void createBoard();
    void setPiece(QPushButton *space, Piece*);

    void setUpPuzzle1();
    void setUpPuzzle2();
    void setUpPuzzle3();
    void setUpPuzzle4();
    void setUpPuzzle5();
    void setUpPuzzle6();

signals:
    void goBackButtonClicked();

public slots:
    void selectSpace();
    void onGoBackButtonClicked();

};

#endif // PUZZLE_H
