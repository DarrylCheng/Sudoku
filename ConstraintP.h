#ifndef ConstraintP_H
#define ConstraintP_H
#include <vector>
#include <queue>
#include <set>
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
};

struct sortByChoices{
	bool operator()(const Cell& lhs, const Cell& rhs) const{
		return lhs.numOfChoice() > rhs.numOfChoice();
	}
};

class ConstraintP{
	priority_queue<Cell, vector<Cell>, sortByChoices> cells;
public:
	//Returns true if board is solvable
	// bool solve(SudokuBoard& sb){
	// 	populateCells(sb);
	// 	return constraintPropogation(sb);
	// }

	void populateCells(SudokuBoard sb){
		SudokuBoard copy(sb);
		int dimension = copy.getDimension();
		int row,col;
		set<int> possibleVals;
		while(copy.getFirstEmptyCell(row,col)){
			possibleVals = copy.possibleValues(row,col);
			cells.push(Cell(row,col,possibleVals));
			copy.assignValue(row,col,-1);
		}
	}

	void updateCells(SudokuBoard sb){
		while(!cells.empty()){
			cells.pop();
		}
		populateCells(sb);
	}

	bool assignValueWithOneChoice(SudokuBoard& sb){
		bool succeed = true;
		while(!cells.empty()){
			if(cells.top().numOfChoice() != 1){
				updateCells(sb);
				if(cells.top().numOfChoice() > 1){
					succeed = false;
					break;
				}
			} else {
				sb.assignValue(cells.top().x,cells.top().y,cells.top().getFirstNum());
				cells.pop();
			}
		}
		// while(!cells.empty()){
		// 	cout << cells.top().x << " " << cells.top().y << " Possible Values: ";
		// 	for(int i: cells.top().possibleValues){
		// 		cout << i << " ";
		// 	}
		// 	cout << endl;
		// 	cells.pop();
		// }
		return succeed;
	}

};

#endif