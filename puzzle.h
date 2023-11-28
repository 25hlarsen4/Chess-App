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
    explicit Puzzle(QWidget *parent = nullptr);

private:
    QImage background;

    QHash<QPair<char, int>, Piece*> piecePositions;

    void paintEvent(QPaintEvent *);
    void createBoard();
    void setPiece(QPushButton *space);

signals:
public slots:
    void selectSpace();

};

#endif // PUZZLE_H
