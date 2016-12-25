#ifndef GENERATE_SUDOKU_H
#define GENERATE_SUDOKU_H
#include <cstdlib> //srand and rand
#include <ctime>
#include "Backtracking.h"
#include "SudokuBoard.h"

class GenerateSudoku{
public:
	SudokuBoard generate(){
		// Returns a randomly generated sudoku board
		SudokuBoard sb;
		while(!lasVegas(sb)){}

		//Continue here
		//Dig holes
		
		return sb;
	}

	bool lasVegas(SudokuBoard& sb){
		//Create a random pattern, and attempt to solve it.
		sb.initializeBoard();

		srand(time(NULL));
		int R, col, row,num, givens = 11; //Randomly insert in 9 cells

		for(int i=0; i< givens; i++){ 
			//Insert of random inserting, each row is guarenteed a random cell.
			//Reduces the probability having a board that takes more than average time to solve.
			R = rand()%81;
			num = rand()%9;
			row = R / 9;
			col = R % 9;

			if(sb.checkCellIfValid(row,col,num)){
				sb.assignValue(row,col,num);
			} else {
				i--;
			}
		}

		//Try to solve it
		Backtracking bt;
		bool solved = bt.tryToSolve(sb);
		return solved;
	}
};

#endif