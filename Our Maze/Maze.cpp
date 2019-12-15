#include "Maze.h"
#include "Queue.h"

#include <iostream>
using namespace std;


// ------------------------ C'TOR AND D'TOR ------------------------ //
Maze::Maze(Board* board)
{
	m_board = board;
}
Maze::~Maze()
{
	// CHECK:
	cout << "MAZE D'TOR \n";
}


// ------------------------ CONST METHODS ------------------------ //

//int Maze::getHeight()const
//{
//	return m_height;
//}
//int Maze::getWidth()const
//{
//	return m_width;
//}
//const char** Maze::getBoard() const
//{
//	return m_board;
//}


void Maze::printBoard() const
{
	m_board->show();
}

void Maze::cleanBoard()
{
	m_board->cleanVisitedMarks();
}




int		Maze::getHeight()			const
{
	return m_board->getHeight();
}
int		Maze::getWidth()			const
{
	return m_board->getWidth();
}


// ------------------------ NON-CONST METHODS ------------------------ //

//bool Maze::setHeight(int height)
//{
//	if (height<MIN_ROW || height >MAX_ROW)
//		return false;
//	m_height = height;
//	return true;
//}
//bool Maze::setWidth(int width)
//{
//	if(width<MIN_COL || width>MAX_COL)
//		return false;
//	m_width = width;
//	return true;
//}

void Maze::escapeMaze()
/*
This function uses a queue to escape the maze.
It goes over all possible points in the maze, and keeps track of where it's been.
It removes from the head a point, and marks that we've visited it.
If the slot it removed is the exit point of the maze, we're done. Otherwise,
We'll add to the queue all the points we can reach from the current point, which we haven't visited yet.
It checks in this order: right, down, left, up.
*/
{
	Queue q(m_board->height, m_board->width); // CHANGE SO THAT Q RECEIVES 1 PARAMETER AND THE MULTIPLICATION OCCURS HERE OUTSIDE
	int counter = 0;
	while (q.isEmpty() == false)
	{
		Point p = q.DeQueue();	//	Remove head.
		if (m_board->isEmptySpace(p.getX(), p.getY()))
		{
		cout << "Round " << counter++ << endl;
		m_board->show();
			m_board->setPointVisited(p);	//	Set the point to visited ($).

				if (p.getX() == m_board->width - 1 && p.getY() == m_board->height - 2) //Nir: (LAXURY) Use ==operator *****************************************************************************************************
					return;
				//	Else: Not the exit point - now we must add all not-yet-visited-points surrounding the point we got.
					int nextX, nextY;

				for (int i = 0; i < MAX_NEIGHBORS; i++)
				{
					Point neighborP = p + i;	//	i indications direction, according to Point::operator+
					int x = neighborP.getX();
					int y = neighborP.getY();
					if (m_board->coordinateInRange(x, y) && m_board->isEmptySpace(x, y))
						q.EnQueue(neighborP);
				}
		}//if
	}//while
}//escapeMaze
/*
QUESTION ABOUT ESCAPE MAZE
Maybe we should work with a copy of the board, and then send that copy back?
Because we change the board by drawing $$ on it.
That means that once we call this method, the board is "ruined".
So either we use some cleanBoard method at the beginning of this method,
or we work with copies of the board
*/



// ------------------------ GLOBAL FUNCTIONS ------------------------ //

bool checkBoard(char** board, int h, int w)
{
	for (int i = 0; i < h; i++)
	{
		if (i == 1 && board[1][0] != ' ') //check entrance
			return false;

		else if (i == h - 2 && board[h - 2][w - 1] != ' ') //check exit
			return false;

		else if (board[i][0] != '*' || board[i][w - 1] != '*')
			return false;
	} //check left and right walls + entrance and exit

	for (int j = 0; j < w; j++)
	{
		if (board[0][j] != '*' || board[h - 1][j] != '*')
			return false;
	} //check top and bottom walls
}
