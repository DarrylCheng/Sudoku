#ifndef GENERATE_SUDOKU_H
#define GENERATE_SUDOKU_H
#include <cstdlib> //srand and rand
#include <ctime>
#include "Configuration.h"
#include "Backtracking.h"
#include "DifficultyLevels/SudokuDifficulty.h"
#include "DifficultyLevels/Level.h"
#include "DifficultyLevels/Easy.h"
#include "DifficultyLevels/Medium.h"
#include "DifficultyLevels/Difficult.h"
#include "DifficultyLevels/Evil.h"
#include "SudokuBoard.h"
#include <iostream>
using namespace std;

class GenerateSudoku{
public:
	SudokuBoard generate(Level level, int dimension){
		// Returns a randomly generated sudoku board
		SudokuBoard board(dimension);
		cout << "Generating complete sudoku...(Abort if it takes too long)";
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
		cout << "Proceeding holes digging...\n";

		//In case if digging holes will cause the sudoku to be unsolvable, might need some modifications here
		sd->digHoles(board);

		return board;
	}

	bool lasVegas(SudokuBoard& sb){
		//Create a random pattern, and attempt to solve it.
		sb.initializeBoard();
		int dim = sb.getDimension();
		srand(time(NULL));
		int R, col, row,num; //Randomly insert in 11 cells

		for(int i=0; i< givens; i++){ //Givens is from Configuration
			//Insert of random inserting, each row is guarenteed a random cell.
			//Reduces the probability having a board that takes more than average time to solve.
			R = rand()%(dim*dim);
			num = 1 + rand()%dim;
			row = R / dim;
			col = R % dim;

			if(sb.checkCellIfValid(row,col,num)){
				sb.assignValue(row,col,num);
			} else {
				i--;
			}
		}

		//Try to solve it
		Backtracking bt;
		return bt.solve(sb);
	}
};

#endif