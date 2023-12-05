#ifndef LESSON_H
#define LESSON_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>

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

signals:
    void lessonFinished(int);


private:
    void setUpLesson1();
    void setUpLesson2();
    void setUpLesson3();
    void setUpLesson4();
    void setUpLesson5();
    void setUpLesson6();
    QPushButton *nextButton;
    void nextClicked();
};


#endif // LESSON_H
