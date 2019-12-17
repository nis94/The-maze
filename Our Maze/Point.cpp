#include "Point.h"

/*----------------------------------------------c'tors------------------------------------------------*/

Point::Point(int x, int y)
{
	setX(x);
	setY(y);
}

/*----------------------------------------------operators------------------------------------------------*/
Point Point::operator+(int direction) const
/*
This operator returns a new point, made by the current point's coordinates as well as the chosen diretion.
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
	return true;
}



/*----------------------------------------------functions------------------------------------------------*/

bool Point::rangeCheck(int height, int width)const
{
	bool x_pos = true, y_pos = true;

	//Check that the Point within Board Sizes:

	if (this->x > width-1 || this->x < 0) { x_pos = false; } 

	if (this->y > height-1 || this->y < 0) { y_pos = false; } 

	return (x_pos && y_pos); 
}






