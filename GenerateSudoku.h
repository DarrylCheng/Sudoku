#ifndef GENERATE_SUDOKU_H
#define GENERATE_SUDOKU_H
#include <cstdlib> //srand and rand
#include <ctime>
#include "Backtracking.h"
#include "SudokuBoard.h"
#include "DifficultyLevels/SudokuDifficulty.h"
#include "DifficultyLevels/Level.h"
#include "DifficultyLevels/Easy.h"
#include "DifficultyLevels/Medium.h"
#include "DifficultyLevels/Difficult.h"
#include "DifficultyLevels/Evil.h"

class GenerateSudoku{
public:
	SudokuBoard generate(Level level){
		// Returns a randomly generated sudoku board
		SudokuBoard board;
		while(!lasVegas(board)){}

		SudokuDifficulty * sd;
		switch(level){
			case Level::EASY:
				sd = new Easy();
				break;
			case Level::MEDIUM:
				sd = new Medium();
				break;
			case Level::DIFFICULT:
				sd = new Difficult();
				break;
			case Level::EVIL:
				sd = new Evil();
				break;
		}

		//In case if digging holes will cause the sudoku to be unsolvable, might need some modifications here
		sd->digHoles(board);

		return board;
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
			num = 1 + rand()%9;
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
		return bt.tryToSolve(sb);
	}
};

#endif