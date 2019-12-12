#pragma warning(disable:4996)
#ifndef __POINT_H
#define __POINT_H

#include <iostream>
using namespace std;

class Point
{
	int x;              // Col >
	int y;              // Row ^

public:
	enum eNeighbours { RIGHT, DOWN, LEFT, UP }; // Use then at + operator

// Constructors
	Point(int x = 0, int y = 0);

	// Operators
	const Point& operator+(int direction) const; // This is the signature that we want to the operator? ---- Do we wat also (int)+(point) ?

// Setters
	bool setX(int x);
	bool setY(int y);

	// Getters
	int getX() const;
	int getY() const;

public:
	bool rangeCheck(int height, int width)const;
	//Point& chooseRandNeighbor()const;
};
#endif // !__POINT_H
