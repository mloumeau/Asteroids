#define _USE_MATH_DEFINES

#include "bullet.h"
#include "uiDraw.h" //math stuff
#include <cmath>

void Bullet::draw()
{
	if (isAlive())
	{
		drawDot(point);
	}
}

void Bullet::fire(const Point& point, float angle)
{
	this->point = point;
	velocity.setDx(-cos(M_PI / 180.0 * -angle) * BULLET_SPEED);
	velocity.setDy(sin(M_PI / 180.0 * -angle) * BULLET_SPEED);

	alive = true;
}

void Bullet::fourtyFrames()
{
	speed += BULLET_SPEED;

	if (speed >= BULLET_SPEED * 20)
	{
		kill();
	}
}