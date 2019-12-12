#pragma warning(disable:4996)
#ifndef __BOARD_H
#define __BOARD_H

#include "Point.h"

// ------------------------ CONSTS ------------------------ //
const char VISITED = '$';
const char EMPTY_SPACE = ' ';
const char WALL = '*';
const int MAX_NEIGHBORS = 4;

class Board
{
private:
	char**		board;
	int			height;
	int			width;

	// Private Methods
	void setStartingRandBoard();	//	A function to set a starting board of 3x3 squares of walls, with empty spaces in the middle. It's prepartion for making arandom board.
	void findFreeNeighbors(Point& currP, int* unvisitedNeighArr, int& numOfUnvisitedNeighbors);
	Point& wallToRemove(Point& currP, Point& neighborP);
	int maxNum(int a, int b);

public:
	// Constructors
	Board() = delete;
	Board(int height, int width);
	~Board();

	// Const Methods
	void show() const;
	int getHeight() const;
	int getWidth() const;
	bool isEmptySpace(int x, int y) const;
	bool coordinateInRange(int x, int y) const;
	char** getMat() { return board; }


	// Non-const Methods
	bool setNewBoard(char** newBoard, int newHeight, int newWidth);
	bool makeCustomBoard();
	bool makeRandBoard();
	bool setPointVisited(const Point& p);
	bool setPointVisited(int x, int y);
	void cleanVisitedMarks();


	friend class Maze;
};
#endif


