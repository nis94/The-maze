#pragma warning(disable:4996)
#ifndef __MAZE_H
#define __MAZE_H

#include "Board.h"

// ------------------------ CONSTS ------------------------ //
const unsigned short int MAX_ROW = 25;		//	Including borders.
const unsigned short int MAX_COL = 80;	//	Including borders.

const unsigned short int MIN_ROW = 3;
const unsigned short int MIN_COL = 3;

//const char VISITED = '$';
//const char EMPTY_SPACE = ' ';
//const char WALL = '*';
//const int MAX_NEIGHBORS = 4;


class Maze
{
private:
	//int			m_height;
	//int			m_width;
	//char**		m_board; // Maybe we should change it to Point**, because of this board made from h*w points 
	Board*			m_board;

public:
	// Constructors
	Maze() = delete;
	Maze(Board* board);
	//Maze(int height, int width, const char** board);
	//~Maze();
	//copy c'tor?

// Setters
	inline bool setHeight(int height);
	inline bool setWidth(int width);
	bool setBoard(char board[25][80]); // Use consts within the dimensions?
	// AFTER CHANGING THE C'TOR TO RECEIVE BOARD:
	// keep the setBoard method, but add parameters for height and width?
	// Meaning this method changes the maze completely

// Getters
	int		getHeight()			const;
	int		getWidth()			const;
	//const char**	getBoard()			const;
	Board* getBoard() { return m_board; }


	// General
	void escapeMaze();
	void printBoard() const;
	void cleanBoard();		//	Cleans board from "visited" marks


// Global Functions
	friend char** makeRandBoard();
	friend bool checkBoard();
};

//char** makeRandBoard(int height, int width);
//bool checkBoard(char** board, int h, int w);

#endif // !__MAZE_H

