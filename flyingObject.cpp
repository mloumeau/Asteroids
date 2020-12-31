#include "flyingObject.h"

void FlyingObject::draw()
{
   if (alive)
    {
        drawDot(point);
    }
}

void FlyingObject::advance()
{
    if (isAlive())
    {
        point.setX(point.getX() + velocity.getDx());
        point.setY(point.getY() + velocity.getDy());
    }
    return;
}

void FlyingObject::fire(const Point& point, float angle)
{
    this->point = point;
    velocity.setDx(-cos(M_PI / 180.0 * -angle) * velocity.getDx());
    velocity.setDy(sin(M_PI / 180.0 * -angle) * velocity.getDy());

    alive = true;
}