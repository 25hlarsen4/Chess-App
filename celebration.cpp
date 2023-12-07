#include "celebration.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QTime>

celebration::celebration(QWidget *parent) : QWidget(parent) {
    setFixedSize(800, 600);

    backgroundPixmap.load(":/backgrounds/Images/welldone.jpeg");

    // Initialize Box2D world with gravity
    b2Vec2 gravity(0.0f, 10.0f);
    world = new b2World(gravity);

    // Create ground body at the bottom of the window
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.0f / scale, 600.0f / scale); // Centered at bottom
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(400.0f / scale, 0.1f); // Half-width of window, small height
    groundBody->CreateFixture(&groundBox, 0.0f);

    balls.push_back(createBall());
    balls.push_back(createBall());
    balls.push_back(createBall());
    balls.push_back(createBall());
    balls.push_back(createBall());
    balls.push_back(createBall());

    // Set up the timer for the simulation step
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &celebration::updateWorld);
    timer->start(updateInterval);

    connect(this, &celebration::ballOutOfBoundSignal, this, &celebration::refreshBall);
}

celebration::~celebration() {
    delete world;
}

void celebration::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Fill the background
    painter.drawPixmap(rect(), backgroundPixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    for (size_t i = 0; i < balls.size(); ++i) {
        b2Body* ball = balls[i];
        b2Vec2 position = ball->GetPosition();
        float x = position.x * scale;
        float y = position.y * scale;

        // Set the brush color based on the ball index
        if (i % 3 ==  0) {
            painter.setBrush(Qt::red); // First ball red
        } else if (i % 3 == 1){
            painter.setBrush(Qt::blue); // Second ball blue
        } else {
            painter.setBrush(Qt::yellow); // Thrid ball yellow
        }

        if (x > width() + 50 || y > height() + 50 || x < -50 || y < -50) { // if ball is out of screen
            emit ballOutOfBoundSignal(ball);
        } else {
            painter.drawEllipse(QPointF(x, y), 50, 50); // Draw the ball
        }
    }
}

void celebration::updateWorld() {
    world->Step(1.0f / 60.0f, 6, 2);
    update();
}


b2Body* celebration::createBall() {
    // Create dynamic ball body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    b2Body* newBall = world->CreateBody(&ballBodyDef);
    b2CircleShape ballCircle;
    ballCircle.m_radius = 1.0f;
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballCircle;
    ballFixtureDef.density = 1.0f;
    ballFixtureDef.restitution = 0.7f;
    newBall->CreateFixture(&ballFixtureDef);

    refreshBall(newBall);

    return newBall;
}

void celebration::refreshBall(b2Body* ball) {

    // Set ball position
    float random = static_cast<float>(QRandomGenerator::global()->bounded(static_cast<quint32>(0), static_cast<quint32>(800 * 10000))) / 10000.0f;
    ball->SetTransform(b2Vec2(random / scale, 0.0f), 0.0f); // Reset position

    // Set the initial velocity for a 45-degree drop
    float initialVelocityMagnitude = 5.0f; // Adjust this value as needed
    if (random > 400){
        ball->SetLinearVelocity(b2Vec2(-initialVelocityMagnitude, initialVelocityMagnitude));
    }
    else {
        ball->SetLinearVelocity(b2Vec2(initialVelocityMagnitude, initialVelocityMagnitude));
    }
}
