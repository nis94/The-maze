#include "Board.h"
#include "Stack.h"

#include <time.h>
#include <iostream>
using namespace std;


// ------------------------ C'TOR AND D'TOR ------------------------ //
Board::Board(int height, int width)
{
	this->height = height;
	this->width = width;
	board = new char*[height];
	if (!board)	//	Allocation check
		exit(1);
	for (int i = 0; i < height; ++i)
	{
		board[i] = new char[width+1]; // NIR: added place for '\0'
		if (!board[i])	//	Allocation check
			exit(1);
	}
}
Board::~Board()
{
	for (int i = 0; i < height; ++i)
		delete[](board[i]);
	delete[] board;

	// CHECK:
	cout << "BOARD D'TOR";
}



// ------------------------ CONST METHODS ------------------------ //
void Board::show() const
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
int	Board::getHeight() const
{
	return height;
}
int	Board::getWidth() const
{
	return width;
}
bool Board::isEmptySpace(int x, int y) const
{
	return board[y][x] == EMPTY_SPACE;
}
bool Board::coordinateInRange(int x, int y)	const
{
	if (x<0 || x > width)
		return false;
	if (y<0 || y>height)
		return false;
	return true;
}



// ------------------------ NON-CONST METHODS ------------------------ //
bool Board::setNewBoard(char** newBoard, int newHeight, int newWidth)
{
	for (int i = 0; i < height; i++)
	{
		delete[]board[i];
	}
	delete[]board;

	height = newHeight;
	width = newWidth;

	for (int i = 0; i < newHeight; i++)
	{
		board[i] = strdup(newBoard[i]);
		if (!board[i])	//	Allocation check.
			exit(1);
	}
	return true;
}
bool Board::makeRandBoard()
/*
When creating a random board, we start with a template for a starting board - which is squares of walls, with empty space in the center.
(This also means that random boards can be made only with odd values for height and width)
We create it with a stack that visits all the empty spaces (meaning it jumps 2 points at a time, "over" walls).
For every point at the top of the stack, we choose a random neighbor of that point we haven't yet visited.
We remove the wall between current point and unvisited neighbor point.
We return current point to stack, as well as unvisited neighbor point.
We continue until the stack is empty.
*/
{
	srand((unsigned int)time(NULL));

	//if (height % 2 == 0 || width % 2 == 0)	// Nir:	I think we already take care of this check on the main *******************************************************************************************************************************
	//	return false;
	setStartingRandBoard();		//	Starting board is a board with "boxes" of walls and spaces in the center of each box. spaces at the Entrance and Exit as well

	Stack stack;
	stack.push(Point(1, 1));	// Start the stack with point (1,1).

	int counter = 1;
	while (!stack.isEmpty()) // Stack isn't empty
	{
		//cout << "Round " << counter++ << endl;
		Point currP = stack.pop();		//	Remove top from stack.
		board[currP.getY()][currP.getX()] = VISITED;	//	Mark on board that we've visited this point.

		int unvisitedNeighArr[MAX_NEIGHBORS];	//	Set an array that will indicate how many free neighbors we have, and where (using enum).
		int numOfUnvisitedNeighbors = 0;
		findFreeNeighbors(currP, unvisitedNeighArr, numOfUnvisitedNeighbors);

		if (numOfUnvisitedNeighbors > 0)	//	If we have unvisited neighbors
		{
			int i = rand() % numOfUnvisitedNeighbors;	//	Choose the element in the array randomly.
			int direction = unvisitedNeighArr[i];
			Point wallP = currP + direction;
			Point neighborP = currP + direction;
			neighborP = neighborP + direction;
			//Point neighborP = currP + unvisitedNeighArr[i];	//	Within the array we have numbers corresponding to the enum values RIGHT, DOWN, LEFT, RIGHT. Pick the direction that was chosen randomly for the neighbor point.
			//Point wallP = wallToRemove(currP, neighborP);
			board[wallP.getY()][wallP.getX()] = EMPTY_SPACE; // Remove wall between currP and neighbor and set the space to empty.
			stack.push(currP);
			stack.push(neighborP);
		}
		// Do we need to delete something here?
	}
	cleanVisitedMarks();
	return true;
}
bool Board::setPointVisited(const Point& p)
{
	if (p.rangeCheck(height, width) == false)	//	Check if in range for starters.
		return false;

	int x = p.getX();
	int y = p.getY();

	if (board[y][x] == WALL)
		return false;

	board[y][x] = VISITED;
	return true;
}
bool Board::setPointVisited(int x, int y)
{
	if (coordinateInRange(x, y) == false)
		return false;

	board[y][x] = VISITED;
}
void Board::cleanVisitedMarks()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j] == VISITED)
				board[i][j] = EMPTY_SPACE;
		}
	}
}




// ------------------------ PRIVATE METHODS ------------------------ //
void Board::setStartingRandBoard()
/*
This function creates the "template" from which we generate a random board.
It creates a board built of "squares of walls", 3x3 squares with empty spaces in each one.
*/
{
	// Set the borders
	for (int i = 0; i < width; i++)		//	Top and Bottom rows
		board[0][i] = board[height - 1][i] = WALL;

	for (int j = 0; j < height; j++)   //	Left and Right rows
		board[j][0] = board[j][width - 1] = WALL;

	// Go over "inner" rows (within the borders)
	for (int i = 1; i < height - 1; i++)
	{
		if (i % 2 == 1) // Odd row
		{
			for (int j = 1; j < width - 1; j++)
			{
				if (j % 2 == 1) // Odd column
					board[i][j] = EMPTY_SPACE;
				else
					board[i][j] = WALL;
			}
		}
		else
			for (int j = 1; j < width - 1; j++)
				board[i][j] = WALL;
	}

	// Set entrace and exit points
	board[1][0] = EMPTY_SPACE;
	board[height - 2][width - 1] = EMPTY_SPACE;
}
void Board::findFreeNeighbors(Point& currP, int* unvisitedNeighArr, int& numOfUnvisitedNeighbors)
{
	/*numOfUnvisitedNeighbors = 0; */ // Already with the value 0 ****************************************************************************************************************************************************************************
	for (int i = 0; i < MAX_NEIGHBORS; i++)
	{
		Point p = currP + i;	//	i is RIGHT, DOWN, LEFT or UP, based on the enum in Point class
		p = p + i; // Add another to create a distance of 2


		if (p.rangeCheck(height, width) == true && board[p.getY()][p.getX()] == EMPTY_SPACE)	//	Check if point is within dimensions and if she is empty.
				unvisitedNeighArr[numOfUnvisitedNeighbors++] = i;                              // the i through the enum indicates which neighbor
	}
}
Point& Board::wallToRemove(Point& currP, Point& neighborP)
/*
This function receives two points, and determines what is the point between them.
It checks the x values and y values separately, to see if they're equal or not.
If they're equal, the corresponding value in the return Point is the same.
If they're not equal, the returning value is minus 1 from the maximum of the two values.
(This is because when building a random maze, every two Points are separated by 2)
*/
{
	int x, y;

	if (currP.getX() == neighborP.getX())
		x = currP.getX();
	else
		x = maxNum(currP.getX(), neighborP.getX()) - 1;

	if (currP.getY() == neighborP.getY())
		y = currP.getY();
	else
		y = maxNum(currP.getY(), neighborP.getY()) - 1;

	Point res(x, y);	// INEFFICIENT: Can we use a move constructor?
	return res;
}
int Board::maxNum(int a, int b)
{
	return (a < b) ? b : a;
}