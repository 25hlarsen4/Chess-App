#ifndef LESSON_H
#define LESSON_H


#include <QWidget>
#include <QLabel>

class Lesson : public QWidget
{
    Q_OBJECT

public:
    enum LessonType
    {
        Lesson1,
        Lesson2,
        Lesson3,
        Lesson4,
        Lesson5,
        Lesson6
    };

    explicit Lesson(QWidget *parent = nullptr);

    explicit Lesson(LessonType, QWidget *parent = nullptr);

    LessonType lessonType;

private:
    void setUpLesson1();
    void setUpLesson2();
    void setUpLesson3();
    void setUpLesson4();
    void setUpLesson5();
    void setUpLesson6();
};


#endif // LESSON_H
