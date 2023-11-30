
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
