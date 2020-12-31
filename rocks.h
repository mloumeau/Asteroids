#ifndef rocks_h
#define rocks_h

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10



// Define the following classes here:
//   Rock
class Rock : public FlyingObject
{
protected:
	int spin;
	char type;
public:
	Rock()
	{
		alive = true;
		type = 'a';
		spin = 0;
	};

	Rock(const Point& point)
	{
		alive = true;
		this->point = point;
		type = 'a';
		spin = 0;
	}
	Rock(const Point& point, Velocity velocity, float angle, char type);
	virtual void draw() {};
	int getSize() { return size; }
	virtual char getType() { return type; }
	void setType(char a) { type = a; }
};

//   BigRock
class BigRock : public Rock
{
public:
	BigRock() {};
	BigRock(const Point& point);
	BigRock(const Point& p, Velocity velocity);
	BigRock(const Point& point, Velocity velocity, float angle, char type);
	virtual void draw();
};



//   MediumRock
class MediumRock : public Rock
{
public:
	MediumRock() {};
	MediumRock(const Point& p);
	MediumRock(const Point& p, Velocity v);
	MediumRock(const Point& point, Velocity velocity, float angle, char type);
	virtual void draw();
};

//   SmallRock
class SmallRock : public Rock
{
public:
	SmallRock() {};
	SmallRock(const Point& p);
	SmallRock(const Point& p, Velocity velocity);
	SmallRock(const Point& point, Velocity velocity, float angle, char type);
	virtual void draw();
};


#endif /* rocks_h */
