/***********************************************************
 * flyingObject.h
 ***************************************************************/
#ifndef FLYING_OBJECT_H
#define FLYING_OBJECT_H

#define _USE_MATH_DEFINES

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "math.h"
class FlyingObject
{
protected:
    Point point;
    Velocity velocity;
    bool alive = true;
    int size;

public:
    FlyingObject()
    {
        point = Point();
        velocity = Velocity();
        alive = true;
        size = 0;
    };
    virtual ~FlyingObject() {};

    Point getPoint() const { return point; }
    Velocity getVelocity() const { return velocity; }
    int getRadius() const { return size; }
    float xValue() { return point.getX(); }
    float yValue() { return point.getY(); }

    bool isAlive() { return alive; }
    void kill() { alive = false; }

    void setAlive(bool isA) { alive = isA; }
    void setXValue(float num) { point.setX(num); }
    void setYValue(float num) { point.setY(num); }

    void setPoint(Point point) { this->point = point; }
    void setVelocity(Velocity velocity) { this->velocity = velocity; }

    virtual void fire(const Point& point, float angle);
    void advance();
    virtual void draw() = 0;
};

#endif /* lander_h */
