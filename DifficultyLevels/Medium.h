#ifndef MEDIUM_H
#define MEDIUM_H
#include "SudokuDifficulty.h"
#include <cstdlib>
#include <ctime>
#include <vector>

class Medium: public SudokuDifficulty{
	bool digHoles(SudokuBoard& sb) override{
		//Randomly remove 48 cell locations.
		srand(time(NULL));
		vector<int> index;

		for(int i=0; i < sb.getDimension()*sb.getDimension() ; ++i){
			index.push_back(i);
		}
		for(int i=0; i < 48; ++i){
			int R = rand()%index.size();
			int rowIndex = index[R]%9;
			int colIndex = index[R]/9;

			index.erase(index.begin()+R);
			// Here need check digging hole constraint
			sb.deleteValue(rowIndex,colIndex);
		}
	}
};

#endif