#ifndef EVIL_H
#define EVIL_H
#include "SudokuDifficulty.h"
#include <cstdlib>
#include <ctime>
#include <vector>

class Evil: public SudokuDifficulty{
	bool digHoles(SudokuBoard& sb) override{
		srand(time(NULL));
		vector<int> index;
		int dim = sb.getDimension()*sb.getDimension();
		index.reserve(dim);

		for(int i=0; i < dim ; ++i){
			index.push_back(i);
		}
		for(int i=0; i < dim/1.26 && !index.empty();){
			int R = rand()%index.size();
			int rowIndex = index[R]%sb.getDimension();
			int colIndex = index[R]/sb.getDimension();

			index.erase(index.begin()+R);
			int temp = sb.getValue(rowIndex,colIndex);
			sb.deleteValue(rowIndex,colIndex);
			if(!isUnique(sb)){
				sb.assignValue(rowIndex,colIndex,temp);
			}else{
				++i;
			}
		}
	}
};

#endif