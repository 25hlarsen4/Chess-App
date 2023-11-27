// should do control stuffs, .ui file -> veiw stuffs

#include "chess.h"
#include "puzzle.h"
#include "ui_chess.h"
#include <QApplication>

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{
    ui->setupUi(this);
    // Set ui styles
    this->setStyleSheet("QMainWindow{background-color: rgb(30, 30, 30)}");
    ui->startPage->setStyleSheet("QWidget#startPage{background-image: url(:/backgrounds/Images/chessboardbackground.png);"
                                 "background-repeat: no-repeat; background-position: center}");
    ui->mainPage->setStyleSheet("QWidget#mainPage{background-color:tan}"
                                "QPushButton{background-color: rgb(210, 70, 51);"
                                "border-width: 6px; border-radius: 20px;"
                                "border: 2px black; height: 75;}"
                                "QPushButton::hover{background-color: rgb(128, 0, 32)}");
    ui->titleLabel->setStyleSheet("QLabel{background: transparent; color:black;}");
    ui->startButton->setStyleSheet("QPushButton{background-color: lightgreen;"
                                   "border-width: 6px; border-radius: 20px;}"
                                   "QPushButton::hover{background-color: rgb(68, 255, 21)}");
    ui->loadButton->setStyleSheet("QPushButton{background-color: rgb(255, 255, 122);"
                                   "border-width: 6px; border-radius: 20px;}"
                                   "QPushButton::hover{background-color: rgb(255, 255, 51)}");
    ui->windows->setCurrentIndex(0);

    styleChessboard();


    // Make connections from model to view
    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &Chess::startGame);
//    connect(ui->lesson1,
//            &QPushButton::clicked,
//            this,
//            &Chess::lesson1);



    ui->windows->addWidget(new Puzzle);
    connect(ui->puzzle1,
            &QPushButton::clicked,
            this,
            &Chess::puzzle1);
}

void Chess::styleChessboard() {
    for (char row = 'a'; row <= 'h'; ++row) {
        for (int col = 1; col <= 8; ++col) {
            QString squareName = QString("%1%2").arg(row).arg(col);
            QPushButton *square = this->findChild<QPushButton *>(squareName);

            if (square) {
                // Corrected logic for color determination
                bool isLightSquare = (row - 'a' + col) % 2 == 1; // Change here

                if (isLightSquare) {
                    square->setStyleSheet("background-color: rgb(255, 206, 158);");
                } else {
                    square->setStyleSheet("background-color: rgb(209, 139, 71);");
                }

                // Set fixed size for squares, you can adjust this as needed
                square->setFixedSize(70, 70);
            }
        }
    }
}

Chess::~Chess()
{
    delete ui;
}

void Chess::startGame() {
    ui->windows->setCurrentIndex(1);
}

//void Chess::lesson1() {
//    ui->windows->setCurrentIndex(2);
//}

void Chess::puzzle1() {
    ui->windows->setCurrentIndex(3);
}




