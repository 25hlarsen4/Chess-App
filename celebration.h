#ifndef CELEBRATION_H
#define CELEBRATION_H

#include <QWidget>
#include <QTimer>
#include <Box2D/Box2D.h>

class celebration : public QWidget {
    Q_OBJECT

public:
    explicit celebration(QWidget *parent = nullptr);
    ~celebration() override;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateWorld();

signals:
    void ballOutOfBoundSignal(b2Body *ball);

private:
    b2World *world;
    b2Body *ballBody;
    QTimer *timer;
    const float32 scale = 50.0f; // Pixels per meter
    const int updateInterval = 16; // Timer interval in ms (about 60 FPS)
    float ballRadius = 10.0f;

    b2Body* createBall();
    void refreshBall(b2Body *ball);
    std::vector<b2Body*> balls;

    QPixmap backgroundPixmap;
};

#endif // CELEBRATION_H
