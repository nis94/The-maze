#include "Utils.h"
//bool checkBoard(char board[25][80], int h, int w)
//{
//
//		for (int i = 0; i < h; i++)
//		{
//			if (i == 1 && board[1][0] != ' ') //check entrance
//				return false;
//
//			else if (i == h - 2 && board[h - 2][w - 1] != ' ') //check exit
//				return false;
//
//			else if (board[i][0] != '*' || board[i][w - 1] != '*')
//				return false;
//		} //check left and right walls + entrance and exit
//
//		for (int j = 0; j < w; j++)
//		{
//			if (board[0][j] != '*' || board[h-1][j] != '*')
//				return false;
//		} //check top and bottom walls
//
//
//}
