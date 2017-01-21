#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <cstdlib> //srand and rand
#include "Configuration.h"
#include "DifficultyLevels/Level.h"
using namespace std;

class SudokuBoard{
	int ** board;
	int dimension;
public:
	SudokuBoard(int dimension=9):dimension(dimension){
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
			if(x%boxSizeY == 0){
				cout << "|" << setfill('-') << setw(dimension*2+dimension*2/boxSizeX+1) <<"|\n";
			}
			for(int y = 0; y < dimension; y++){
				if(y%boxSizeX == 0){
					cout << "| ";
				}
				if (board[x][y] == 0)
					cout << "_ ";
				else{
					if(board[x][y] < 10)
						cout << board[x][y] << " ";
					else{
						char letter = board[x][y]+55;
						cout << letter << " ";
					}
				}
			}
			cout << "|" << endl;
		}
		cout << "|" << setfill('-') << setw(dimension*2+dimension*2/boxSizeX+1) <<"|\n";
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

		//BoxSizes from configuration

		for (int x = (row/boxSizeY)*boxSizeY; x < (row/boxSizeY)*boxSizeY+boxSizeY; ++x){
			for (int y = (col/boxSizeX)*boxSizeX; y < (col/boxSizeX)*boxSizeX+boxSizeX; ++y){
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
