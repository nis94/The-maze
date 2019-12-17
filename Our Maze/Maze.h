#pragma warning(disable:4996)
#ifndef __MAZE_H
#define __MAZE_H

#include "Board.h"

// ------------------------ CONSTS ------------------------ //
const unsigned short int MAX_ROW = 25;		//	Including borders.
const unsigned short int MAX_COL = 80;		//	Including borders.

const unsigned short int MIN_ROW = 3;
const unsigned short int MIN_COL = 3;



class Maze
{
private:
	Board*			m_board;

public:
// Constructors
	Maze() = delete;
	Maze(Board* board);


// Getters
	inline int		getHeight()	const { return m_board->height; }
	inline int		getWidth()	const { return m_board->width; }
	Board* getBoard() { return m_board; }

	// General
	bool escapeMaze();
	void printBoard() const;
	void cleanBoard();		//	Cleans board from "visited" marks

	bool checkBoard();		//	Check borders of the board as well as exit and entrance points
};

#endif // !__MAZE_H

