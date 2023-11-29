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
    // correct moves, piece set up
    explicit Puzzle(QList<QPair<int, int>>, QHash<QPair<int, int>, Piece::PieceType>, QWidget *parent = nullptr);

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

signals:
    void hideLabel(QLabel*);

public slots:
    void selectSpace();
    void onHideLabel(QLabel*);

};

#endif // PUZZLE_H
