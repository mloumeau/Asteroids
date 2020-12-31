#ifndef BULLET_H
#define BULLET_H

#include "flyingObject.h"
#define BULLET_SIZE 2

static const float BULLET_SPEED = 10.0;

class Bullet : public FlyingObject
{
private:
	float speed = 0;
public:
	Bullet()
	{
		alive = true;
	}

	void fire(const Point& point, float angle);
	void draw();
	int getSize() { return BULLET_SIZE; }
	float getSpeed() { return speed; }
	void fourtyFrames();
};

#endif
