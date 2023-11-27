#ifndef PIECE_H
#define PIECE_H

#include "qimage.h"
#include <QObject>

class Piece : public QObject
{
    Q_OBJECT
public:
    explicit Piece(QObject *parent = nullptr);

    QImage pieceImage;

private:


signals:

};

#endif // PIECE_H
