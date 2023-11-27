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
};
#endif // CHESS_H
