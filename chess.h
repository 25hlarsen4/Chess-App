#ifndef CHESS_H
#define CHESS_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class Chess; }
QT_END_NAMESPACE

class Chess : public QMainWindow
{
    Q_OBJECT

public:
    Chess(QWidget *parent = nullptr);
    ~Chess();

private:
    Ui::Chess *ui;
    void startGame();
    void styleChessboard();

    void lesson1();
    void puzzle1();

    void lesson2();
    void puzzle2();

    void lesson3();
    void puzzle3();

    void lesson4();
    void puzzle4();

    void lesson5();
    void puzzle5();

    void lesson6();
    void puzzle6();

    void enablePuzzle(int);
    void completePuzzle(int);

};
#endif // CHESS_H
