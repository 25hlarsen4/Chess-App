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
    explicit Puzzle(QList<QPair<int, int>>, QWidget *parent = nullptr);

private:
    QImage background;

    QHash<QPushButton*, Piece*> spacePieceMap;
    QHash<QPair<char, int>, Piece*> piecePositions;
    QList<QPair<int, int>> correctClickSequence;
    QList<QPair<int, int>> potentialLocations;

    int currSequenceIndex;
    bool selecting;
    bool moving;
    Piece* selectedPiece;

    void paintEvent(QPaintEvent *);
    void createBoard();
    void setPiece(QPushButton *space);

signals:
public slots:
    void selectSpace();

};

#endif // PUZZLE_H
