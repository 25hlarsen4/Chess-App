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

    // Fill the background with white color
    painter.drawPixmap(rect(), backgroundPixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    painter.setBrush(Qt::blue);

    for (b2Body* ball : balls) {
        b2Vec2 position = ball->GetPosition();
        float x = position.x * scale;
        float y = position.y * scale; // Note: Box2D's origin is at the bottom-left corner, so y might need to be inverted

        if (x > width()+50 || y > height()+50 || x < -50 || y < -50) { // Adjust the bounds check as needed
            emit ballOutOfBoundSignal(ball);
        } else {
            painter.drawEllipse(QPointF(x, y), 40, 40); // Draw the ball
        }
    }
}

void celebration::updateWorld() {
    world->Step(1.0f / 60.0f, 6, 2); // Update the Box2D world

    update(); // Trigger a repaint to draw the new positions of the balls
}


b2Body* celebration::createBall() {
    // Create dynamic ball body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    b2Body* newBall = world->CreateBody(&ballBodyDef);
    b2CircleShape ballCircle;
    ballCircle.m_radius = 1.0f; // Radius of 1 meter
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballCircle;
    ballFixtureDef.density = 1.0f;
    ballFixtureDef.restitution = 0.7f; // Bouncy
    newBall->CreateFixture(&ballFixtureDef);

    refreshBall(newBall);

    return newBall;
}

void celebration::refreshBall(b2Body* ball) {

    // Set ball position
    float random = static_cast<float>(QRandomGenerator::global()->bounded(static_cast<quint32>(0), static_cast<quint32>(800 * 10000))) / 10000.0f;
    ball->SetTransform(b2Vec2(random / scale, 0.0f), 0.0f); // Reset position

    // Set the initial velocity for a 45-degree drop
    float initialVelocityMagnitude = 7.0f; // Adjust this value as needed
    if (random > 400){
        ball->SetLinearVelocity(b2Vec2(-initialVelocityMagnitude, initialVelocityMagnitude));
    }
    else {
        ball->SetLinearVelocity(b2Vec2(initialVelocityMagnitude, initialVelocityMagnitude));
    }
}
