#include <iostream>
#include "SudokuBoard.h"
#include "Backtracking.h"
#include "GenerateSudoku.h"
#include <windows.h>
using namespace std;
//Compile in C++11 --std=c++11
//If error, add --std=gnu++0x

int main(){
	// SudokuBoard sb;
	// sb.printBoard();
	// cout << endl;
	// Backtracking solve(sb);
	// cout << boolalpha << endl << solver.solve() << endl;
	// solver.printSolvedBoard();

	GenerateSudoku sb;
	SudokuBoard yo;
	while(true){
		//Test the generate function for random complete sudoku board.
		yo = sb.generate();
		yo.printBoard();
		cout << endl;
		Sleep(600);
	}
}