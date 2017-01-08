#include <iostream>
#include "SudokuBoard.h"
#include "Backtracking.h"
#include "GenerateSudoku.h"
#include "DifficultyLevels/Level.h"
#include <windows.h>
#include <chrono>
#include <fstream>
using namespace std;
//Compile in C++11 --std=c++11
//If error, add --std=gnu++0x

int main(){
	GenerateSudoku sb;
	SudokuBoard easy, medium, difficult, evil;
	ofstream file;
	file.open("results.csv");
	file << "Easy,Medium,Difficult,Evil\n";
	for(int i=0; i< 10000; i++){
		easy = sb.generate(Level::EASY);
		medium = sb.generate(Level::MEDIUM);
		difficult = sb.generate(Level::DIFFICULT);
		evil = sb.generate(Level::EVIL);

		Backtracking solver;
		auto start = chrono::system_clock::now();
		solver.solve(easy);
		auto end = chrono::system_clock::now();
		chrono::duration<double> duration = end - start;
		// cout << "\nTime elapsed (Easy): " << duration.count();
		file << duration.count() << ",";

		start = chrono::system_clock::now();
		solver.solve(medium);
		end = chrono::system_clock::now();
		duration = end - start;
		// cout << "\nTime elapsed (medium): " << duration.count();
		file << duration.count() << ",";

		start = chrono::system_clock::now();
		solver.solve(difficult);
		end = chrono::system_clock::now();
		duration = end - start;
		// cout << "\nTime elapsed (difficult): " << duration.count();
		file << duration.count() << ",";

		start = chrono::system_clock::now();
		solver.solve(evil);
		end = chrono::system_clock::now();
		duration = end - start;
		// cout << "\nTime elapsed (evil): " << duration.count();
		file << duration.count() << "\n";
	}
}