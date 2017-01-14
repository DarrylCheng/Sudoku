#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include "SudokuBoard.h"
#include <iostream>
using namespace std;

class Backtracking{
	int numOfRecursions;
public:
	//Returns true if board is solvable
	bool solve(SudokuBoard& sb){
		numOfRecursions = 0;
		return backtrackingSolver(sb,-1);
	}

	//During generation of sudoku, some board might take forever to get solved
	bool tryToSolve(SudokuBoard& sb){
		numOfRecursions = 0;
		return backtrackingSolver(sb,1000000);
	}

	bool backtrackingSolver(SudokuBoard& sb, int limit){
		// sb.printBoard();
		// cout << endl << endl;
		int row = 0;
		int col = 0;
		numOfRecursions++;
		if(limit != -1 && numOfRecursions > limit)
			return false;
		// sb.printBoard();
		if (!sb.getFirstEmptyCell(row,col)){
			return true; //Base case
			//If no free cell left, sudoku is solved
			//else row and col is updated with the free cell
		}

		//9 needs to be replaced with sb.getDimSize()
		for(int num = 1; num <= sb.getDimension(); num++){
			if(sb.checkCellIfValid(row,col,num)){
				//If num is can be placed on that cell, assign to it.
				sb.assignValue(row,col,num);

				//Go deeper into the board
				//Returns false (backtrack) if cell cannot be assigned
				//any number
				if(backtrackingSolver(sb,limit)){
					return true; //Base case
				}

				//If the code reaches here, means solver returned false
				//backtracking needed
				//Assign empty (0) to the cell just assigned
				sb.assignValue(row,col,0);
				//Continue next for loop iteration
			}
		}
		//If there is empty cell and none of the for loop can assign
		//a value, returns false (initiate backtracking)
		return false;
	}
};

#endif