#include "Maze.h"
#include "Queue.h"

#include <iostream>
using namespace std;

Maze::Maze(Board* board)
{
	m_board = board;
}

void Maze::printBoard() const
{
	m_board->show();
}

void Maze::cleanBoard()
{
	m_board->cleanVisitedMarks();
}

bool Maze::escapeMaze()
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
	while (q.isEmpty() == false)
	{
		Point p = q.DeQueue();	//	Remove head.
		if (m_board->isEmptySpace(p.getX(), p.getY()))
		{
			m_board->setPointVisited(p);	//	Set the point to visited ($).

				if (p.getX() == m_board->width - 1 && p.getY() == m_board->height - 2)  // Reached exit
					return true;
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
	return false;
}//escapeMaze

bool Maze::checkBoard()
/*
This function checks that the board is right for a maze solution.
Meaning that all the borders are walls, and that the exit and entrance points are clear.
*/
{
	int h = m_board->height;
	int w = m_board->width;
	char** board = m_board->board;

	for (int i = 0; i < h; i++) // Go over rows
	{
		if (i == 1) // If second row - check entrance.
		{
			if (board[1][0] != EMPTY_SPACE || board[1][w - 1] != WALL) // Check entrance
			{
				return false;
			}
		}
		else if (i == h - 2) // If before last row - check exit
		{
			if (board[i][0] != WALL || board[i][w - 1] != EMPTY_SPACE)
			{
				return false;
			}
		}
		else if (board[i][0] != WALL || board[i][w - 1] != WALL) // Not second row or before last row
		{
			return false;
		}
	} //check left and right walls + entrance and exit

	for (int j = 0; j < w; j++)
	{
		if (board[0][j] != WALL || board[h - 1][j] != WALL)
		{
			return false;
		}
	} //check top and bottom walls
	return true;
}


