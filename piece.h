#ifndef PIECE_H
#define PIECE_H

#include "qimage.h"
#include <QObject>
#include <QPushButton>
#include <QLabel>

class Piece : public QObject
{
    Q_OBJECT
public:
    explicit Piece(QObject *parent = nullptr);

    QImage pieceImage;

    void setKnight(QPushButton* space);

private:


signals:

};

#endif // PIECE_H
