#ifndef SUDOKUPUZZLE_H
#define SUDOKUPUZZLE_H
#include "SudokuBoard.h"
#include "GenerateSudoku.h"
#include "DifficultyLevels/Level.h"

class SudokuPuzzle{
	SudokuBoard sb;
public:
	SudokuPuzzle(Level levels, int dimension){
		GenerateSudoku gen;
		sb = gen.generate(levels,dimension);
	}

	SudokuPuzzle(SudokuPuzzle& pz):sb(pz.getBoard()){}

	void print(){
		sb.printBoard();
	}

	SudokuBoard& getBoard(){
		return sb;
	}

	friend ostream& operator<<(ostream&os, SudokuPuzzle& pz){
		SudokuBoard sb = pz.getBoard();
		int** boardArray = sb.getBoard();
		int dimension = sb.getDimension();
		for(int i=0;i<dimension;i++){
			for(int z=0;z<dimension;z++){
				os << boardArray[i][z] << " ";
			}
		}
		return os;
	}
};

#endif