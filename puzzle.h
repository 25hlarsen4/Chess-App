#ifndef PUZZLE_H
#define PUZZLE_H

#include "piece.h"
#include <QWidget>

class Puzzle : public QWidget
{
    Q_OBJECT
public:
    explicit Puzzle(QWidget *parent = nullptr);

private:
    QImage background;

    QHash<QPair<char, int>, Piece*> piecePositions;

    void paintEvent(QPaintEvent *);

signals:

};

#endif // PUZZLE_H
