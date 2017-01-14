#ifndef SUDOKU_DIFFICULTY_H
#define SUDOKU_DIFFICULTY_H
#include "../SudokuBoard.h"
#include <vector>
using namespace std;

class SudokuDifficulty{
	//Interface for sudoku difficulty level
public:
	virtual bool digHoles(SudokuBoard& sb) = 0;
	// bool diggingRules(SudokuBoard sb, int row, int col, int limit){
		
	// }
};

#endif