/*            ------------ MAGNIFICENT MAZE ------------ 
Nir Bar Levav	205489651
Eli Harel		200133304

This program creates a maze and solves it.
The user chooses the dimensions and then decides whether to create the maze randomly based on them,
Or if to design one himself.

The random creation of the maze uses a Stack, the solution of a maze uses a circular Queue.

Note to dear tester: When we perform an exit due to invalid input, we were unsure how to handle all the allocations in the 
*/

#include "Board.h"
#include "Maze.h"
#include "Stack.h"
#include "Point.h"
#include <string.h>
#include <iostream>
using namespace std;


// ------------------------ CONSTS ------------------------ //
const unsigned short int CUSTOM = 1;	//	User choice in maze creation.
const unsigned short int RANDOM = 2;	//	User choice in maze creation.


int chooseCreationMethod();
void makeCustomBoard(Maze& maze);
void chooseParameters(int& height, int& width, int creationMethod);


// ------------------------ MAIN ------------------------ //
int main()
{
	int creationMethod = chooseCreationMethod();	// User chooses if to create maze himself, or randomly
	int height, width;
	chooseParameters(height, width, creationMethod); // Read parameters. We send them to the functions tasked with making the board (custom or rand). Parameters are read differently based on whether or not user chose to create randomly or create himself (rand means only odd parameters).
	Board board(height, width); // Create board based on parameters
	Maze maze(&board);
	
	if (creationMethod == CUSTOM)
		makeCustomBoard(maze);
	else // User chose random creation.
		board.makeRandBoard();
		
	if (maze.escapeMaze())
		maze.printBoard();
	else
		cout << "no solution\n";
}



// ------------------------ FUNCTIONS ------------------------ //
int chooseCreationMethod()
/*
In this function the user only chooses the option of how he wants the maze to be created:
1) Make it himself
2) Make a random maze for him
Function is only about input of the decision.
*/
{
	int option;
	cout << "Maze: 1) From input 2) Random\n";
	cin >> option;
	while (option < 1 || option > 2)
	{
		cout << "Please choose an option within range: ";
		cin >> option;
	}
	cout << endl;
	return option;
}

void makeCustomBoard(Maze& maze)
/*
In this function the user designs his board himself.
The function also performs checks for the board created:
	-	Did he insert invalid chars?
	-	Did he create proper borders?
	-	Did he create exit and entrance points?
	-	Did he create rows with the designated width\len?
*/
{
	char** board = maze.getBoard()->getMat();
	cin.ignore();	//	Remove \n from buffer 
	for (int i = 0; i < maze.getHeight(); i++) // Go over all rows
	{
		cin.getline(board[i], maze.getWidth() + 1); // Read each row
		int width = strlen(board[i]); // Check len of row user chose
		if (width < (unsigned)maze.getWidth()) // Compare row of input to expected row length
		{
			cout << "invalid input\n";
			exit(1);	
		}
		for (int j = 0; j < width; j++) // Check invalid chars within the row
		{
			if (board[i][j] != EMPTY_SPACE && board[i][j] != WALL)
			{
				cout << "invalid input\n";
				exit(1);
			}
		}
	}

	if (!maze.checkBoard()) // Check if the borders are correct
	{	
		cout << "invalid input\n";
		exit(1);
	}
}

void chooseParameters(int& height, int& width, int creationMethod)
/*
In this function, the user chooses the parameters for his maze.
If the creation method chosen is random, then the parameters must be odd.
*/
{
	cin >> height;
	while (height < 3 || height>25 || (creationMethod == RANDOM && height % 2 == 0))	//	 Height range validity check.
	{
		if (creationMethod == RANDOM)
			cout << "When generating a random maze, dimensions must be odd numbers.\n";
		cout << "Invalid height. Enter value within range: ";
		cin >> height;
	}
	cout << endl;

	cin >> width;
	while (width < 3 || width>80 || (creationMethod == RANDOM && width % 2 == 0))	//	Width range validity check.
	{
		if (creationMethod == RANDOM)
			cout << "When generating a random maze, dimensions must be odd numbers.\n";
		cout << "Invalid width. Enter value within range: ";
		cin >> width;
	}
}