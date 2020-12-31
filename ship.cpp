/********************************************************************
 * ship.cpp
 **********************************************************************/

#include "ship.h"

Ship::Ship()
{
    setAlive(true);
    velocity.setDx(0.0);
    velocity.setDy(0.0);
    point.setX(0.0);
    point.setY(0.0);
    size = SHIP_SIZE;
}

Ship::Ship(Point point, Velocity velocity)
{
    setPoint(point);
    setVelocity(velocity);
    setAlive(true);
    size = SHIP_SIZE;
}

void Ship::advance()
{
    point.setX(point.getX() + velocity.getDx());
    point.setY(point.getY() + velocity.getDy());
    if (point.getX() < -200)
        point.setX(200);
    if (point.getX() > 200)
        point.setX(-200);
    if (point.getY() < -200)
        point.setY(200);
    if (point.getY() > 200)
        point.setY(-200);
    return;
}

void Ship::applyThrustLeft()
{
    setAngle(velocity.getAngle() + ROTATE_AMOUNT);
    return;
}

void Ship::applyThrustRight()
{
    setAngle(velocity.getAngle() - ROTATE_AMOUNT);
    return;
}

void Ship::applyThrustBottom()
{
    velocity.setDx(velocity.getDx() - 0.5 * -sin(M_PI / 180.0 * velocity.getAngle()));
    velocity.setDy(velocity.getDy() - 0.5 * cos(M_PI / 180.0 * velocity.getAngle()));
    return;
}

void Ship::applyThrustTop()
{
    velocity.setDx(velocity.getDx() + 0.5 * -sin(M_PI / 180.0 * velocity.getAngle()));
    velocity.setDy(velocity.getDy() + 0.5 * cos(M_PI / 180.0 * velocity.getAngle()));
    return;
}

void Ship::draw()
{
    drawShip(point, velocity.getAngle(), true);
    return;
}
