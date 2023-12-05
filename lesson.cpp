
#include "lesson.h"

Lesson::Lesson(QWidget *parent)
    : QWidget{parent}
{

}

Lesson::Lesson(LessonType pt, QWidget *parent)
    : QWidget{parent}
{
    nextButton = new QPushButton(this);
    nextButton->setStyleSheet("QPushButton{background-color: brown;"
                              "border-width: 6px; border-radius: 20px;"
                              "border: 2px black;}"
                              "QPushButton::hover{background-color: rgb(50, 255, 50)}");
    nextButton->setGeometry(675,525,100,50);
    nextButton->setText("Next");
    nextButton->show();

    connect(nextButton,
            &QAbstractButton::clicked,
            this,
            &Lesson::nextClicked);


    lessonType = pt;

    if (lessonType == Lesson1) {
        setUpLesson1();
    }

    else if (lessonType == Lesson2) {
        setUpLesson2();
    }

    else if (lessonType == Lesson3) {
        setUpLesson3();
    }

    else if (lessonType == Lesson4) {
        setUpLesson4();
    }

    else if (lessonType == Lesson5) {
        setUpLesson5();
    }

    else if (lessonType == Lesson6) {
        setUpLesson6();
    }
}

void Lesson::setUpLesson1() {
    QLabel *title = new QLabel(this);
    title->setStyleSheet("QLabel { background-color: brown; }");
    setStyleSheet("font-weight: bold;");
    title->setGeometry(50,25,700,100);
    title->setText("DOUBLE ATTACK / FORK");
    title->setFont(QFont("Arial", 25));
    title->setAlignment(Qt::AlignCenter);
    title->show();

    QLabel *mainInfo = new QLabel(this);
    mainInfo->setStyleSheet("QLabel { background-color: white; }");
    mainInfo->setGeometry(50,200,300,200);
    mainInfo->setWordWrap(true);
    mainInfo->setText("A double-attack, or fork, occurs when you move one piece to a position that attacks two of the opponents pieces.");
    mainInfo->show();

    QLabel *imageToDisplay = new QLabel(this);
    imageToDisplay->setPixmap(QPixmap(":/examples/Images/doubleAttackEx.jpg"));
    imageToDisplay->setScaledContents(true);
    imageToDisplay->setStyleSheet("QLabel { background-color: white; }");
    imageToDisplay->setGeometry(420,150,300,300);
    imageToDisplay->show();

    QLabel *funFactOrTip = new QLabel(this);
    funFactOrTip->setStyleSheet("QLabel { background-color: white; }");
    funFactOrTip->setGeometry(25,470,750,50);
    funFactOrTip->setWordWrap(true);
    funFactOrTip->setText("In the example above, the white knight forks black's king and rook. Also, black's pawn forks the white rooks.");
    funFactOrTip->show();
}

void Lesson::setUpLesson2() {
    QLabel *title = new QLabel(this);
    title->setStyleSheet("QLabel { background-color: brown; }");
    setStyleSheet("font-weight: bold;");
    title->setGeometry(50,25,700,100);
    title->setText("PINNED QUEEN");
    title->setFont(QFont("Arial", 25));
    title->setAlignment(Qt::AlignCenter);
    title->show();

    QLabel *mainInfo = new QLabel(this);
    mainInfo->setStyleSheet("QLabel { background-color: white; }");
    mainInfo->setGeometry(50,200,300,200);
    mainInfo->setWordWrap(true);
    mainInfo->setText("A pin is a tactic in which a defending piece cannot move out of an attacking piece's line of attack without exposing a more valuable defending piece. Note that a queen can only ever be partially pinned, as it can move in any linear direction to escape.");
    mainInfo->show();

    QLabel *imageToDisplay = new QLabel(this);
    imageToDisplay->setPixmap(QPixmap(":/examples/Images/pinnedQueenEx.jpg"));
    imageToDisplay->setScaledContents(true);
    imageToDisplay->setStyleSheet("QLabel { background-color: white; }");
    imageToDisplay->setGeometry(420,150,300,300);
    imageToDisplay->show();

    QLabel *funFactOrTip = new QLabel(this);
    funFactOrTip->setStyleSheet("QLabel { background-color: white; }");
    funFactOrTip->setGeometry(25,470,750,50);
    funFactOrTip->setWordWrap(true);
    funFactOrTip->setText("In the example above, the black queen is pinned to the black king by the white rook, so the queen cannot move.");
    funFactOrTip->show();
}
void Lesson::setUpLesson3() {
    QLabel *title = new QLabel(this);
    title->setStyleSheet("QLabel { background-color: brown; }");
    setStyleSheet("font-weight: bold;");
    title->setGeometry(50,25,700,100);
    title->setText("SMOTHERED MATE");
    title->setFont(QFont("Arial", 25));
    title->setAlignment(Qt::AlignCenter);
    title->show();

    QLabel *mainInfo = new QLabel(this);
    mainInfo->setStyleSheet("QLabel { background-color: white; }");
    mainInfo->setGeometry(50,200,300,200);
    mainInfo->setWordWrap(true);
    mainInfo->setText("A smothered mate is a checkmate involving the knight. It occurs when the king is surrounded and the knight can jump over the surrounding pieces.");
    mainInfo->show();

    QLabel *imageToDisplay = new QLabel(this);
    imageToDisplay->setPixmap(QPixmap(":/examples/Images/smotheredMateEx.jpg"));
    imageToDisplay->setScaledContents(true);
    imageToDisplay->setStyleSheet("QLabel { background-color: white; }");
    imageToDisplay->setGeometry(420,150,300,300);
    imageToDisplay->show();

    QLabel *funFactOrTip = new QLabel(this);
    funFactOrTip->setStyleSheet("QLabel { background-color: white; }");
    funFactOrTip->setGeometry(25,470,750,50);
    funFactOrTip->setWordWrap(true);
    funFactOrTip->setText("In the example above, the black king is surrounded by its own pieces and thus the white knight has put the king in check.");
    funFactOrTip->show();
}
void Lesson::setUpLesson4() {
    QLabel *title = new QLabel(this);
    title->setStyleSheet("QLabel { background-color: brown; }");
    setStyleSheet("font-weight: bold;");
    title->setGeometry(50,25,700,100);
    title->setText("EN PASSANT MATE");
    title->setFont(QFont("Arial", 25));
    title->setAlignment(Qt::AlignCenter);
    title->show();

    QLabel *mainInfo = new QLabel(this);
    mainInfo->setStyleSheet("QLabel { background-color: white; }");
    mainInfo->setGeometry(30,205,300,200);
    mainInfo->setWordWrap(true);
    mainInfo->setText("Capturing en passant (in passing) describes a pawn capturing an enemy pawn on the same rank and an adjacent file that has just made an initial two-square advance. It is permitted only on the turn immediately after the two-square advance. If this is the case, the capturing pawn can move diagonally forward to the square that the enemy pawn passed, capturing the enemy pawn as if it had moved only one square.");
    mainInfo->show();

    QLabel *image1 = new QLabel(this);
    image1->setPixmap(QPixmap(":/examples/Images/enPassant1.jpg"));
    image1->setScaledContents(true);
    image1->setStyleSheet("QLabel { background-color: white; }");
    image1->setGeometry(360,205,200,200);
    image1->show();

    QLabel *image2 = new QLabel(this);
    image2->setPixmap(QPixmap(":/examples/Images/enPassant2.jpg"));
    image2->setScaledContents(true);
    image2->setStyleSheet("QLabel { background-color: white; }");
    image2->setGeometry(580,230,75,150);
    image2->show();

    QLabel *image3 = new QLabel(this);
    image3->setPixmap(QPixmap(":/examples/Images/enPassant3.jpg"));
    image3->setScaledContents(true);
    image3->setStyleSheet("QLabel { background-color: white; }");
    image3->setGeometry(680,230,75,150);
    image3->show();

    QLabel *funFactOrTip = new QLabel(this);
    funFactOrTip->setStyleSheet("QLabel { background-color: white; }");
    funFactOrTip->setGeometry(25,470,750,50);
    funFactOrTip->setWordWrap(true);
    funFactOrTip->setText("In the example above of the famous Gundersen vs. Faul game, an en passant capture allowed for an en passant mate. The black pawn on g7 made an initial two-square advance, allowing the white pawn on h5 to simultaneously capture the black pawn en passant and check the king.");
    funFactOrTip->show();
}
void Lesson::setUpLesson5() {
    QLabel *mainInfo = new QLabel(this);
    mainInfo->setStyleSheet("QLabel { background-color: white; }");
    mainInfo->setGeometry(0,0,200,200);
    mainInfo->setText("This is the main info for lesson5");
    mainInfo->show();
}
void Lesson::setUpLesson6() {
    QLabel *mainInfo = new QLabel(this);
    mainInfo->setStyleSheet("QLabel { background-color: white; }");
    mainInfo->setGeometry(0,0,200,200);
    mainInfo->setText("This is the main info for lesson6");
    mainInfo->show();
}

void Lesson::nextClicked(){
    if (lessonType == Lesson1) {
        emit lessonFinished(1);
    }

    else if (lessonType == Lesson2) {
        emit lessonFinished(2);
    }

    else if (lessonType == Lesson3) {
        emit lessonFinished(3);
    }

    else if (lessonType == Lesson4) {
        emit lessonFinished(4);
    }

    else if (lessonType == Lesson5) {
        emit lessonFinished(5);
    }

    else if (lessonType == Lesson6) {
        emit lessonFinished(6);
    }
}
