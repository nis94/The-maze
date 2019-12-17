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
	enum eNeighbours { RIGHT, DOWN, LEFT, UP }; // Use them at + operator

// Constructors
	Point(int x = 0, int y = 0);

// Operators
	Point operator+(int direction) const;

// Setters
	bool setX(int x);
	bool setY(int y);

// Getters
	inline int getX() const { return x; }
	inline int getY() const { return y; }

public:
	bool rangeCheck(int height, int width)const;
};
#endif // !__POINT_H
