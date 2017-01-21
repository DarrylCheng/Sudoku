#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include "SudokuBoard.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Backtracking{
public:
	//Returns true if board is solvable
	bool solve(SudokuBoard& sb){
		return backtrackingSolver(sb);
	}

	bool backtrackingSolver(SudokuBoard& sb){
		int row = 0;
		int col = 0;

		if (!sb.getFirstEmptyCell(row,col)){
			return true; //Base case
			//If no free cell left, sudoku is solved
			//else row and col is updated with the free cell
		}

		for(int num = 1; num <= sb.getDimension(); num++){
			if(sb.checkCellIfValid(row,col,num)){
				//If num is can be placed on that cell, assign to it.
				sb.assignValue(row,col,num);

				//Go deeper into the board
				//Returns false (backtrack) if cell cannot be assigned
				//any number
				if(backtrackingSolver(sb)){
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