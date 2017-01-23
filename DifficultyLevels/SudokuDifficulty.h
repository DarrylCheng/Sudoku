#ifndef SUDOKU_DIFFICULTY_H
#define SUDOKU_DIFFICULTY_H
#include "../SudokuBoard.h"
#include <vector>
#include "../ConstraintP.h"
using namespace std;

class SudokuDifficulty{
	//Interface for sudoku difficulty level
public:
	virtual bool digHoles(SudokuBoard& sb) = 0;
	bool isUnique(SudokuBoard sb){
		ConstraintP cp;
		return cp.isUnique(sb);
	}
};

#endif