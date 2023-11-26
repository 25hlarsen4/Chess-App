#include "chess.h"
#include "ui_chess.h"

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

    // Make connections from model to view
    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &Chess::startGame);
}

Chess::~Chess()
{
    delete ui;
}

void Chess::startGame(){
    ui->windows->setCurrentIndex(1);
}
