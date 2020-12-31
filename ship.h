#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#define _USE_MATH_DEFINES

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "math.h"

// Put your Ship class here
class Ship : public FlyingObject
{
private:
    float speed;
    int lives = 3;
public:
    Ship();
    Ship(Point point, Velocity velocity);
    Point getPoint() const { return point; }
    Velocity getVelocity() const { return velocity; }
    float getAngle() { return velocity.getAngle(); }
    int getSize() { return size; }
    float getSpeed() { return speed; }
    int getLives() { return lives; }
    void setLives(int l) { lives = l; }
    void setAlive(bool isA) { alive = isA; }
    void setAngle(float a) { velocity.setAngle(a); }
    void setSpeed(float num) { speed = num; }
    void applyThrustLeft();
    void applyThrustRight();
    void applyThrustBottom();
    void applyThrustTop();
    void advance();
    void draw();
};


#endif /* ship_h */
