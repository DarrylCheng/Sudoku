#include <iostream>
#include <chrono>
#include <fstream>
#include <windows.h>
#include "DifficultyLevels/Level.h"
#include "Configuration.h"
#include "SudokuPuzzle.h"
#include "SudokuBoard.h"
#include "Backtracking.h"
#include "ConstraintP.h"
using namespace std;
using namespace std::chrono;
//Compile in C++11 --std=c++11
//If error, add --std=gnu++0x

int dimension, givens, boxSizeX, boxSizeY;
Level level;

int main(int argc, char * argv[]){
	if(argc>1){
		if((string)argv[1] == "4"){
			dimension = 4, givens = 4, boxSizeX = 2, boxSizeY = 2; //4x4
		} else if((string)argv[1] == "9"){
			dimension = 9,givens = 11, boxSizeX = 3, boxSizeY = 3; //9x9
		} else if((string)argv[1] == "12"){
			dimension = 12, givens = 15, boxSizeX = 4, boxSizeY = 3; //12x12
		} else if((string)argv[1] == "18"){
			dimension = 18, givens = 20, boxSizeX = 6, boxSizeY = 3; //18x18
		} 
		if(argc > 2){
			string lvl = (string)argv[2];
			level = (lvl=="4"?Level::EVIL:lvl=="2"?Level::MEDIUM:lvl=="3"?Level::DIFFICULT:Level::EASY);
		} else {
			level = Level::EASY; //Default level
		}
	} else {
		dimension = 9,givens = 11, boxSizeX = 3, boxSizeY = 3, level = Level::EASY; //9x9 default
	}

	while(true){

		//Generate sudoku
		auto start = chrono::high_resolution_clock::now();
		SudokuPuzzle pz1(level,dimension);
		SudokuPuzzle pz2(pz1);
		SudokuPuzzle backup(pz1);
		auto end = chrono::high_resolution_clock::now();
		auto durationGenerate = duration_cast<milliseconds>( end - start ).count();
		pz2.print();
		cout << "Time elapsed (Generating): " << durationGenerate << "ms\n\n";

		//Test constraint propogation
		ConstraintP cp;
		start = chrono::high_resolution_clock::now();
		bool solvableCP = cp.solve(pz2.getBoard());
		end = chrono::high_resolution_clock::now();
		auto durationCP = duration_cast<milliseconds>( end - start ).count();
		if(solvableCP){
			pz2.print();
			cout << "Time elapsed (CPSolving): " << durationCP << "ms\n";
		} else {
			cout << "Sudoku board is not solvable.\n";
		}
		//Try solving with backtracking algorithm
		Backtracking bt;
		start = chrono::high_resolution_clock::now();
		bool solvableBT = bt.solve(pz1.getBoard()); //bt solving requires SudokuBoard as parameter instead of SudokuPuzzle
		end = chrono::high_resolution_clock::now();
		auto durationBT = duration_cast<milliseconds>( end - start ).count();
		if(solvableBT){
			cout << "Time elapsed (BTSolving): " << durationBT << "ms\n";
		} else {
			cout << "Sudoku board is not solvable.\n";
		}


		ofstream file;
		file.open("Results.csv", ios::app);
		file << backup << "," << pz1 << "," << dimension << "x" << dimension << "," << boxSizeX << "," << boxSizeY;
		if(level == Level::EASY)
			file << "," << "EASY";
		else if (level == Level::MEDIUM)
			file << "," << "MEDIUM";
		else if (level == Level::DIFFICULT)
			file << "," << "DIFFICULT";
		else 
			file << "," << "EVIL";
		file << "," << durationGenerate << "," << durationBT << "," << solvableBT << "," << durationCP << "," << solvableCP;
		file << endl;
		file.close();

		Sleep(1000);
	}
}