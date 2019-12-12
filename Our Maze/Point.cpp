#include "Point.h"

/*----------------------------------------------c'tors------------------------------------------------*/

Point::Point(int x, int y)
{
	setX(x);
	setY(y);
}

/*----------------------------------------------operators------------------------------------------------*/


const Point& Point::operator+(int direction) const
/*
PROBLEM: it's unintuitive that + operation adds 2 instead of 1
This function exists only for the creation of a random maze, so we add 2 values instead of 1 because of the algorithm
But maybe because it's unintuitive it should be located somewhere else, or given a different name?


For DOWN we add 1 and for UP we subtract 1 because of how we view the matrix (upper row is 0, then lower rows increase in value)
*/
{
	// Reminder: according to enum  ------> RIGHT=0, DOWN=1, LEFT=2, UP=3 
	switch (direction)
	{
	case (RIGHT):	//	x+1, same y
		return Point(this->x + 1, this->y);
	case (DOWN):	//	same x, y+1
		return Point(this->x, this->y + 1);
	case (LEFT):	//	x-1, same y
		return Point(this->x - 1, this->y);
	case (UP):		//	same x, y-1
		return Point(this->x, this->y - 1);
	}
}

/*----------------------------------------------setters------------------------------------------------*/

bool Point::setX(int x)
{
	this->x = x;
	return true;
}
bool Point::setY(int y)
{
	this->y = y;

	bool flag = true;
	//boolian check
	return flag;
}


/*----------------------------------------------getters------------------------------------------------*/
int Point::getX()const
{
	return this->x;
}
int Point::getY()const
{
	return this->y;
}



/*----------------------------------------------functions------------------------------------------------*/

bool Point::rangeCheck(int height, int width)const
{
	bool x_pos = true, y_pos = true;

	if (this->x >= width || this->x < 1) { x_pos = false; }

	if (this->y >= height || this->y < 1) { y_pos = false; }

	return (x_pos && y_pos); //check on example
}






