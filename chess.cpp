// should do control stuffs, .ui file -> veiw stuffs

#include "chess.h"
#include "puzzle.h"
#include "lesson.h"
#include "piece.h"
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

    Lesson* less1 = new Lesson(Lesson::Lesson1);
    ui->windows->addWidget(less1);
    connect(ui->lesson1,
            &QPushButton::clicked,
            this,
            &Chess::lesson1);

    Puzzle* puzz1 = new Puzzle(Puzzle::Puzzle1);
//    Puzzle* puzz = new Puzzle;
    ui->windows->addWidget(puzz1);
    connect(ui->puzzle1,
            &QPushButton::clicked,
            this,
            &Chess::puzzle1);

    Lesson* less2 = new Lesson(Lesson::Lesson2);
    ui->windows->addWidget(less2);
    connect(ui->lesson2,
            &QPushButton::clicked,
            this,
            &Chess::lesson2);

    Puzzle* puzz2 = new Puzzle(Puzzle::Puzzle2);
    //    Puzzle* puzz = new Puzzle;
    ui->windows->addWidget(puzz2);
    connect(ui->puzzle2,
            &QPushButton::clicked,
            this,
            &Chess::puzzle2);

    Lesson* less3 = new Lesson(Lesson::Lesson3);
    ui->windows->addWidget(less3);
    connect(ui->lesson3,
            &QPushButton::clicked,
            this,
            &Chess::lesson3);

    Puzzle* puzz3 = new Puzzle(Puzzle::Puzzle3);
    //    Puzzle* puzz = new Puzzle;
    ui->windows->addWidget(puzz3);
    connect(ui->puzzle3,
            &QPushButton::clicked,
            this,
            &Chess::puzzle3);

    Lesson* less4 = new Lesson(Lesson::Lesson4);
    ui->windows->addWidget(less4);
    connect(ui->lesson4,
            &QPushButton::clicked,
            this,
            &Chess::lesson4);

    Puzzle* puzz4 = new Puzzle(Puzzle::Puzzle4);
    //    Puzzle* puzz = new Puzzle;
    ui->windows->addWidget(puzz4);
    connect(ui->puzzle4,
            &QPushButton::clicked,
            this,
            &Chess::puzzle4);

    Lesson* less5 = new Lesson(Lesson::Lesson5);
    ui->windows->addWidget(less5);
    connect(ui->lesson5,
            &QPushButton::clicked,
            this,
            &Chess::lesson5);

    Puzzle* puzz5 = new Puzzle(Puzzle::Puzzle5);
    //    Puzzle* puzz = new Puzzle;
    ui->windows->addWidget(puzz5);
    connect(ui->puzzle5,
            &QPushButton::clicked,
            this,
            &Chess::puzzle5);

    Lesson* less6 = new Lesson(Lesson::Lesson6);
    ui->windows->addWidget(less6);
    connect(ui->lesson6,
            &QPushButton::clicked,
            this,
            &Chess::lesson6);

    Puzzle* puzz6 = new Puzzle(Puzzle::Puzzle6);
    //    Puzzle* puzz = new Puzzle;
    ui->windows->addWidget(puzz6);
    connect(ui->puzzle6,
            &QPushButton::clicked,
            this,
            &Chess::puzzle6);

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

void Chess::lesson1() {
    ui->windows->setCurrentIndex(2);
}

void Chess::puzzle1() {
    ui->windows->setCurrentIndex(3);
}

void Chess::lesson2() {
    ui->windows->setCurrentIndex(4);
}

void Chess::puzzle2() {
    ui->windows->setCurrentIndex(5);
}

void Chess::lesson3() {
    ui->windows->setCurrentIndex(6);
}

void Chess::puzzle3() {
    ui->windows->setCurrentIndex(7);
}

void Chess::lesson4() {
    ui->windows->setCurrentIndex(8);
}

void Chess::puzzle4() {
    ui->windows->setCurrentIndex(9);
}

void Chess::lesson5() {
    ui->windows->setCurrentIndex(10);
}

void Chess::puzzle5() {
    ui->windows->setCurrentIndex(11);
}

void Chess::lesson6() {
    ui->windows->setCurrentIndex(12);
}

void Chess::puzzle6() {
    ui->windows->setCurrentIndex(13);
}




