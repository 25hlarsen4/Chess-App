#include "celebration.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QTime>

celebration::celebration(QWidget *parent) : QWidget(parent) {
    setFixedSize(800, 600);

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

    createBall();

    // Set up the timer for the simulation step
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &celebration::updateWorld);
    timer->start(updateInterval);

    connect(this, &celebration::ballOutOfBoundSignal, this, &celebration::createBall);
}

celebration::~celebration() {
    delete world;
}

void celebration::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(Qt::blue);

    // Convert Box2D position to pixel position
    b2Vec2 position = ballBody->GetPosition();
    float x = position.x * scale;
    float y = (position.y * scale); // Inverting y-axis for screen coordinates

    painter.drawEllipse(QPointF(x, y), 20, 20); // Draw the ball

    if (x>850 || y > 650 || y < -50 || x < -50){
        emit ballOutOfBoundSignal();
    }
}

void celebration::updateWorld() {
    world->Step(1.0f / 60.0f, 6, 2); // Update the Box2D world

    update(); // Redraw the widget
}

void celebration::createBall() {
    // Create dynamic ball body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    srand(static_cast<unsigned>(time(nullptr)));
    float random = static_cast<float>(rand() % 8000) / 10.0f;
    ballBodyDef.position.Set(random / scale, 0.0f); // Start at top middle
    ballBody = world->CreateBody(&ballBodyDef);
    b2CircleShape ballCircle;
    ballCircle.m_radius = 1.0f; // Radius of 1 meter
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballCircle;
    ballFixtureDef.density = 1.0f;
    ballFixtureDef.restitution = 0.7f; // Bouncy
    ballBody->CreateFixture(&ballFixtureDef);

    // Set the initial velocity for a 45-degree drop
    float initialVelocityMagnitude = 7.0f; // Adjust this value as needed
    if (random > 400){
        ballBody->SetLinearVelocity(b2Vec2(-initialVelocityMagnitude, initialVelocityMagnitude));
    }
    else {
    ballBody->SetLinearVelocity(b2Vec2(initialVelocityMagnitude, initialVelocityMagnitude));
    }
}
