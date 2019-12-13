//#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Maze.h"
#include "Utils.h"
#include "Stack.h"
#include "Point.h"
#include <iostream>
using namespace std;


// ------------------------ CONSTS ------------------------ //
const unsigned short int CUSTOM = 1;	//	User choice in maze creation.
const unsigned short int RANDOM = 2;	//	User choice in maze creation.


// ------------------------ STATIC FUNCTIONS ------------------------ //
// SUGGESTION: move all these functions to Source?

int chooseCreationMethod();
void makeCustomBoard(Maze& maze);
void chooseParameters(int& height, int& width, int creationMethod);
char** allocateBoard(int height, int width);


// ------------------------ MAIN ------------------------ //
int main()
{
	int creationMethod = chooseCreationMethod();// User choose if to create maze himself, or randomly

	int height, width;
	chooseParameters(height, width, creationMethod); // Read parameters. We send them to the functions tasked with making the board (custom or rand). Parameters are read differently based on whether or not user chose to create randomly or create himself (rand means only odd parameters).

	Board board(height, width);
	Maze maze(&board);
	
	if (creationMethod == CUSTOM)
		makeCustomBoard(maze);
	else // User chose random creation.
		board.makeRandBoard();
		
	maze.escapeMaze();

	cout << "The reasult is: \n\n";
	maze.printBoard();

	//system("pause"); // Eli: I tried this because the console kept closing, making it tough to see final results for debugging. Didn't work :(
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
	cout << "Please choose one option:\n\t1) Make my maze\n\t2) Make a random maze for me\n\n";
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
{

	char** board = maze.getBoard()->getMat();
	//char** tempBoard = new char*[board.getHeight()];
	////ALLOCATION CHECK
	//for (int i = 0; i < board.getHeight(); i++)
	//{
	//	tempBoard[i] = new char[board.getWidth()];
	//	//ALLOCATION CHECK
	//}

	cin.ignore();
	cout << "Please enter your maze:\n\n";
	for (int i = 0; i < maze.getHeight(); i++)
	{
		// char row[MAX_COL]; // QUESTION: maybe allocate string based on width, and read based on that?
		cin.getline(board[i], maze.getWidth() + 1);
		if (strlen(board[i]) < (unsigned)maze.getWidth())
		{
			cout << "Row is shorter than is required. Invalid input.\n";
			// How to deal with longer rows?
			exit(1);
		}

	}

	// Finished reading a board of proper length. 
	//	board.setNewBoard(tempBoard, board.getHeight(), board.getWidth());

}

void chooseParameters(int& height, int& width, int creationMethod)
/*
In this function, the user chooses the parameters for his maze.
*/
{
	//int height;
	cout << "Please enter the number of rows for the maze, from 3 to 25: ";
	cin >> height;
	while (height < 3 || height>25 || (creationMethod == RANDOM && height % 2 == 0))	//	 Height range validity check.
	{
		if (creationMethod == RANDOM)
			cout << "When generating a random maze, dimensions must be odd numbers.\n";
		cout << "Invalid height. Enter value within range: ";
		cin >> height;
	}
	cout << endl;

	//int width;
	cout << "Please enter the number of columns for the maze, from 3 to 80: ";
	cin >> width;
	while (width < 3 || width>80 || (creationMethod == RANDOM && width % 2 == 0))	//	Width range validity check.
	{
		if (creationMethod == RANDOM)
			cout << "When generating a random maze, dimensions must be odd numbers.\n";
		cout << "Invalid width. Enter value within range: ";
		cin >> width;
	}
}


/* General notes:

When user creates his own custom maze - do we need to check that he actually allows a way to the exit?
If not,  meaning if he can create an unsolvable maze, we need our escapeMaze method to know how to deal with that too.
Maybe something to do about when the queue is empty/full (meaning no more points to visit?)
*/

// Nir: I think we need to verify all of the invalid cases that user can do when he creates his own maze 