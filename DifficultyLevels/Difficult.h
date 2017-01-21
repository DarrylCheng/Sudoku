#ifndef DIFFICULT_H
#define DIFFICULT_H
#include "SudokuDifficulty.h"
#include <cstdlib>
#include <ctime>
#include <vector>

class Difficult: public SudokuDifficulty{
	bool digHoles(SudokuBoard& sb) override{
		//Randomly remove 54 cell locations.
		srand(time(NULL));
		vector<int> index;
		int dim = sb.getDimension()*sb.getDimension();
		index.reserve(dim);

		for(int i=0; i < dim ; ++i){
			index.push_back(i);
		}
		for(int i=0; i < dim/1.5; ++i){
			int R = rand()%index.size();
			int rowIndex = index[R]%sb.getDimension();
			int colIndex = index[R]/sb.getDimension();

			index.erase(index.begin()+R);
			// Here need check digging hole constraint
			sb.deleteValue(rowIndex,colIndex);
		}
	}
};

#endif