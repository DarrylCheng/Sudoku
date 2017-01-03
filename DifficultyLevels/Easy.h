#ifndef EASY_H
#define EASY_H
#include "SudokuDifficulty.h"
#include <cstdlib>
#include <ctime>

class Easy: public SudokuDifficulty{
	bool digHoles(SudokuBoard& sb) override{
		for (int i = 0; i < sb.getDimension(); ++i)
		{
			for (int j = 0; j < sb.getDimension(); ++j)
			{
				int todel = rand()%9;
			}
		}
	}
};

#endif