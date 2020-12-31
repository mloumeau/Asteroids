#include "rocks.h"
#include "uiDraw.h"

Rock::Rock(const Point& point, Velocity velocity, float angle, char type) : Rock(point)
{
	this->point = point;
	this->velocity = velocity;
	velocity.setAngle(angle);
	setType(type);
}

BigRock::BigRock(const Point& point) : Rock(point)
{
	velocity.setDx(1);
	velocity.setDy(1);

	size = BIG_ROCK_SIZE;
	setType('B');
}

BigRock::BigRock(const Point& point, Velocity velocity) : Rock(point)
{
	this->velocity = velocity;

	size = BIG_ROCK_SIZE;
	setType('B');
}

BigRock::BigRock(const Point& point, Velocity velocity, float angle, char type) : Rock(point)
{
	this->point = point;
	this->velocity = velocity;
	velocity.setAngle(angle);
	setType(type);
	size = BIG_ROCK_SIZE;
}

void BigRock::draw()
{
	spin += BIG_ROCK_SPIN;
	if (isAlive())
	   drawLargeAsteroid(getPoint(), spin);
}


MediumRock::MediumRock(const Point& point) : Rock (point)
{
	velocity.setDx(3);
	velocity.setDy(3);

	size = MEDIUM_ROCK_SIZE;
	setType('M');
}

MediumRock::MediumRock(const Point& point, Velocity velocity) : Rock(point)
{
	this->velocity = velocity;

	size = BIG_ROCK_SIZE;
	setType('B');
}

MediumRock::MediumRock(const Point& point, Velocity velocity, float angle, char type) : Rock(point)
{
	this->point = point;
	this->velocity = velocity;
	velocity.setAngle(angle);
	setType(type);
	size = MEDIUM_ROCK_SIZE;
}

void MediumRock::draw()
{
	spin += MEDIUM_ROCK_SPIN;
	if (isAlive())
    	drawMediumAsteroid(getPoint(), spin);
}



SmallRock::SmallRock(const Point& point) : Rock(point)
{
	velocity.setDx(4);
	velocity.setDy(4);

	size = SMALL_ROCK_SIZE;
	setType('S');
}

SmallRock::SmallRock(const Point& point, Velocity v) : Rock(point)
{
	velocity = v;

	size = BIG_ROCK_SIZE;
	setType('B');
}

SmallRock::SmallRock(const Point& point, Velocity velocity, float angle, char type) : Rock(point)
{
	this->point = point;
	this->velocity = velocity;
	velocity.setAngle(angle);
	setType(type);
	size = SMALL_ROCK_SIZE;
}
void SmallRock::draw()
{
	spin += SMALL_ROCK_SPIN;
	if (isAlive())
    	drawSmallAsteroid(getPoint(), spin);
}
