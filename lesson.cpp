
#include "lesson.h"

Lesson::Lesson(QWidget *parent)
    : QWidget{parent}
{

}

Lesson::Lesson(LessonType pt, QWidget *parent)
    : QWidget{parent}
{
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
    nextButton = new QPushButton(this);
    nextButton->setStyleSheet("QPushButton{background-color: brown;"
                                "border-width: 6px; border-radius: 20px;"
                                "border: 2px black;}"
                                "QPushButton::hover{background-color: rgb(50, 255, 50)}");
    nextButton->setGeometry(675,525,100,50);
    nextButton->setText("Next");
    nextButton->show();
    // Move this to the constructor once all lessons are set up
    connect(nextButton,
            &QAbstractButton::clicked,
            this,
            &Lesson::nextClicked);
}

void Lesson::setUpLesson2() {

}
void Lesson::setUpLesson3() {

}
void Lesson::setUpLesson4() {

}
void Lesson::setUpLesson5() {

}
void Lesson::setUpLesson6() {

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
