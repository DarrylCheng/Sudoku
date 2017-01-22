#ifndef ConstraintP_H
#define ConstraintP_H
#include <vector>
#include <set>
#include <algorithm>
#include "Backtracking.h"
#include "Configuration.h"
#include "SudokuBoard.h"
using namespace std; 
//Constraint Propogation
//If a cell have only one possible value, delete it from its peers and place the value in the cell.
struct Cell{
	//Stores possible choice
	int x;
	int y;
	set<int> possibleValues;
	Cell(int x, int y, set<int> possibleValues):x(x),y(y),possibleValues(possibleValues){}

	int numOfChoice() const{
		return possibleValues.size();
	}

	int getFirstNum() const{
		set<int>::iterator it = possibleValues.begin();
		int a = *it;
		return a;
	}

	void updatePossibleValues(set<int> possibleValues){
		this->possibleValues.swap(possibleValues);
	}

	void removeValueFromSet(int num){
		possibleValues.erase(num);
	}
};

struct sortByChoices{
	bool operator()(const Cell& lhs, const Cell& rhs) const{
		return lhs.numOfChoice() < rhs.numOfChoice();
	}
};

class ConstraintP{
	vector<Cell> cells;
public:
	//Returns true if board is solvable
	bool solve(SudokuBoard& sb){
		bool solvable = true;
		populateCells(sb);
		if(!assignValueWithOneChoice(sb)){
			Backtracking bt;
			solvable = bt.solve(sb);
		}
		cells.clear();
		return solvable;
	}

	void populateCells(SudokuBoard sb){
		SudokuBoard copy(sb);
		int dimension = copy.getDimension();
		int row,col;
		set<int> possibleVals;
		while(copy.getFirstEmptyCell(row,col)){
			possibleVals = copy.possibleValues(row,col);
			cells.push_back(Cell(row,col,possibleVals));
			push_heap(cells.begin(),cells.end(), [](const Cell& lhs, const Cell& rhs){
						return lhs.numOfChoice() < rhs.numOfChoice();});
			copy.assignValue(row,col,-1);
		}
		sort_heap(cells.begin(),cells.end(), [](const Cell& lhs, const Cell& rhs){
		return lhs.numOfChoice() < rhs.numOfChoice();});
	}

	void updateCells(int row, int col, int numRemoved){
		auto updateX = find_if(cells.begin(), cells.end(), [&row](const Cell& cell){ return cell.x == row;});
		auto updateY = find_if(cells.begin(), cells.end(), [&col](const Cell& cell){ return cell.y == col;});

		while(updateX != cells.end()){
			updateX->removeValueFromSet(numRemoved);
			updateX = find_if(next(updateX), cells.end(), [&row](const Cell& cell){ return cell.x == row;});
		}

		while(updateY != cells.end()){
			updateY->removeValueFromSet(numRemoved);
			updateY = find_if(next(updateY), cells.end(), [&col](const Cell& cell){ return cell.y == col;});
		}

		for (int x = (row/boxSizeY)*boxSizeY; x < (row/boxSizeY)*boxSizeY+boxSizeY; ++x){
			for (int y = (col/boxSizeX)*boxSizeX; y < (col/boxSizeX)*boxSizeX+boxSizeX; ++y){
				auto updateBox = find_if(cells.begin(), cells.end(), [&x,&y](const Cell& cell){ return cell.x == x && cell.y == y;});
				if(updateBox != cells.end()){
					updateBox->removeValueFromSet(numRemoved);
				}
			}
		}

		sort_heap(cells.begin(),cells.end(), [](const Cell& lhs, const Cell& rhs){
		return lhs.numOfChoice() < rhs.numOfChoice();});
	}

	bool assignValueWithOneChoice(SudokuBoard& sb){
		bool computable = true;
		while(!cells.empty() && computable){
			Cell temp = cells[0];
			if(temp.numOfChoice() == 1){
				pop_heap(cells.begin(),cells.end(), [](const Cell& lhs, const Cell& rhs){
					return lhs.numOfChoice() < rhs.numOfChoice();
				});
				cells.pop_back();
				sb.assignValue(temp.x,temp.y,temp.getFirstNum());
				updateCells(temp.x,temp.y,temp.getFirstNum());
			} else {
				computable = false;
			}
		}
		return computable;
	}

};

#endif