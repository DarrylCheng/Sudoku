#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cstdlib> //srand and rand
#include "DifficultyLevels/Level.h"
using namespace std;

class SudokuBoard{
	int ** board;
	int dimension;
public:
	SudokuBoard(int dimension=9):dimension(dimension){
		// if(dimension%3 != 0){
		// 	throw dimension;
		// }
		board = new int*[dimension];
		for(int i = 0; i < dimension; i++){
			board[i] = new int[dimension];
		}
		initializeBoard(); // 9x9
	}

	void initializeBoard(){
		for(int i = 0; i < dimension; i++){
			for(int y = 0; y < dimension; y++){
				board[i][y] = 0;
			}
		}
	}

	void printBoard(){
		// system("cls");
		for(int x = 0; x < dimension; x++){
			for(int y = 0; y < dimension; y++){
				if (board[x][y] == 0)
					cout << "_ ";
				else
					cout << board[x][y] << " ";
			}
			cout << endl;
		}
		// Sleep(700);
	}

	bool checkColumnIfValid(int col, int num){
		//Check if _num_ is valid for that column _col_
		//^Sudoku rules, no duplicate values.
		//Return false if not valid
		for(int row = 0; row < dimension; row++){
			if (board[row][col] == num){
				return false;
			}
		}
		return true;
	}

	bool checkRowIfValid(int row, int num){
		//Check if _num_ is valid for that row _row_
		//^Sudoku rules, no duplicate values.
		//Return false if not valid
		for(int col = 0; col < dimension; col++){
			if (board[row][col] == num){
				return false;
			}
		}
		return true;
	}

	bool checkBoxIfValid(int row, int col, int num){
		//Check if _num_ is valid for that box
		//Each value belongs to a row, column and in a box.
		//^Sudoku rules, no duplicate values.
		//Return false if not valid

		//boxSize needs to be dynamic when increasing sudoku dimension
		int boxSize = 3; 

		for (int x = (row/boxSize)*boxSize; x < (row/boxSize)*boxSize+boxSize; ++x){
			for (int y = (col/boxSize)*boxSize; y < (col/boxSize)*boxSize+boxSize; ++y){
				if (board[x][y] == num){
					return false;
				}
			}
		}
		return true;
	}

	//Returns true if cell is empty (0)
	bool checkIfCellEmpty(int row, int col){
		if(board[row][col] == 0)
			return true;
		return false;
	}

	//One call method to call the other 3 methods
	//Checks the sudoku rules if the number is valid on that board location
	bool checkCellIfValid(int row, int col, int num){
		//Returns false if NOT valid
		return checkIfCellEmpty(row,col)?checkBoxIfValid(row,col,num)?checkColumnIfValid(col,num)?checkRowIfValid(row,num):false:false:false;
	}

	//Pass in row and col as reference.
	//Used for the backtracking algorithm
	//Returns false if no empty cell left. 
	bool getFirstEmptyCell(int& row, int& col){
		int rowAndColumn[2];
		for(int x = 0; x < dimension; x++){
			for(int y = 0; y < dimension; y++){
				if(board[x][y] == 0){
					row = x;
					col = y;
					return true;
				}
			}
		}
		return false;
	}

	void assignValue(int row, int col, int num){
		board[row][col] = num;
	}

	bool deleteValue(int row, int col){
		if(board[row][col] == 0){
			return false;
		}else{
			board[row][col] = 0;
			return true;
		}
	}

	int getDimension(){
		return dimension;
	}
};


#endif
