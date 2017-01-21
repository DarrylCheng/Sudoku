#include <iostream>
#include "Configuration.h"
#include "SudokuPuzzle.h"
#include "SudokuBoard.h"
#include "Backtracking.h"
#include "DifficultyLevels/Level.h"
// #include <windows.h>
#include <chrono>
// #include <fstream>
using namespace std;
//Compile in C++11 --std=c++11
//If error, add --std=gnu++0x

int dimension, givens, boxSizeX, boxSizeY;
// int dimension = 4,givens = 4, boxSizeX = 2, boxSizeY = 2, holesDig = 1; // 4
// int dimension = 9,givens = 11, boxSizeX = 3, boxSizeY = 3, holesDig = 1; //9
// int dimension = 12,givens = 15, boxSizeX = 4, boxSizeY = 3, holesDig = 1; //12
// int dimension = 18,givens = 20, boxSizeX = 6, boxSizeY = 3, holesDig = 1; //18

int main(int argc, char * argv[]){
	if(argc==1){
		dimension = 9, givens = 11, boxSizeX = 3, boxSizeY = 3;
	} else if((string)argv[1] == "4"){
		dimension = 4, givens = 4, boxSizeX = 2, boxSizeY = 2;
	} else if((string)argv[1] == "12"){
		dimension = 12, givens = 15, boxSizeX = 4, boxSizeY = 3;
	} else if((string)argv[1] == "18"){
		dimension = 18, givens = 20, boxSizeX = 6, boxSizeY = 3;
	} else {
		dimension = 9,givens = 11, boxSizeX = 3, boxSizeY = 3;
	}

	//Generate sudoku
	auto start = chrono::system_clock::now();
	SudokuPuzzle pz(Level::MEDIUM,dimension);
	auto end = chrono::system_clock::now();
	chrono::duration<double> duration = end - start;
	pz.print();
	cout << "Time elapsed (Generating): " << duration.count() << "\n\n";

	//Try solving with backtracking algorithm
	Backtracking bt;
	start = chrono::system_clock::now();
	bool solvable = bt.solve(pz.getBoard()); //bt solving requires SudokuBoard as parameter instead of SudokuPuzzle
	end = chrono::system_clock::now();
	duration = end - start;
	if(solvable){
		pz.print();
		cout << "Time elapsed (Solving): " << duration.count() << endl;
	} else {
		cout << "Sudoku board is not solvable.\n";
	}





	// SudokuBoard easy, medium, difficult, evil;
	// SudokuBoard easy(18);
	// easy = sb.generate(Level::EASY,18);
	// ofstream file;
	// file.open("results.csv");
	// file << "Easy,Medium,Difficult,Evil\n";
	for(int i=0; i< 1; i++){
		// easy = sb.generate(Level::EASY,18);
		// medium = sb.generate(Level::MEDIUM);
		// difficult = sb.generate(Level::DIFFICULT);
		// evil = sb.generate(Level::EVIL);

		// Backtracking solver;
		// auto start = chrono::system_clock::now();
		// solver.solve(easy);
		// easy.printBoard();
		// auto end = chrono::system_clock::now();
		// chrono::duration<double> duration = end - start;
		// // cout << "\nTime elapsed (Easy): " << duration.count();
		// file << duration.count() << ",";

		// start = chrono::system_clock::now();
		// solver.solve(medium);
		// end = chrono::system_clock::now();
		// duration = end - start;
		// // cout << "\nTime elapsed (medium): " << duration.count();
		// file << duration.count() << ",";

		// start = chrono::system_clock::now();
		// solver.solve(difficult);
		// end = chrono::system_clock::now();
		// duration = end - start;
		// // cout << "\nTime elapsed (difficult): " << duration.count();
		// file << duration.count() << ",";

		// start = chrono::system_clock::now();
		// solver.solve(evil);
		// end = chrono::system_clock::now();
		// duration = end - start;
		// // cout << "\nTime elapsed (evil): " << duration.count();
		// file << duration.count() << "\n";
	}
}