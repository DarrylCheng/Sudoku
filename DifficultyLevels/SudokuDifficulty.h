#ifndef SUDOKU_DIFFICULTY_H
#define SUDOKU_DIFFICULTY_H
#include "../SudokuBoard.h"

class SudokuDifficulty{
	//Interface for sudoku difficulty level
public:
	virtual bool digHoles(SudokuBoard& sb) = 0;
};

#endif