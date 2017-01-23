#ifndef ConstraintP_H
#define ConstraintP_H
#include <vector>
#include <set>
#include <algorithm>
#include "Backtracking.h"
#include "Configuration.h"
#include "SudokuBoard.h"
#include <chrono>
#include <iostream>
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
			// Backtracking bt;
			// solvable = bt.solve(sb);
		}
		cells.clear();
		return solvable;
	}

	bool isUnique(SudokuBoard& sb){
		populateCells(sb);
		if(!assignValueWithOneChoice(sb)){
			return false;
		}
		cells.clear();
		return true;
	}

	void populateCells(SudokuBoard sb){
		cells.clear();
		int dimension = sb.getDimension();
		int row,col;
		set<int> possibleVals;
		while(sb.getFirstEmptyCell(row,col)){
			possibleVals = sb.possibleValues(row,col);
			cells.push_back(Cell(row,col,possibleVals));
			push_heap(cells.begin(),cells.end(), [](const Cell& lhs, const Cell& rhs){
						return lhs.numOfChoice() < rhs.numOfChoice();});
			sb.assignValue(row,col,-1);
		}
		sort_heap(cells.begin(),cells.end(), [](const Cell& lhs, const Cell& rhs){
		return lhs.numOfChoice() < rhs.numOfChoice();});
	}

	void updateCells(int row, int col, int numRemoved){
		int boxStartX((row/boxSizeY)*boxSizeY), boxEndX(boxStartX+boxSizeY);
		int boxStartY((col/boxSizeX)*boxSizeX), boxEndY(boxStartY+boxSizeX);

		auto update = find_if(cells.begin(), cells.end(), [&row,&col,&boxStartY,&boxStartX,&boxEndY,&boxEndX](const Cell& cell){
			return cell.x == row || cell.y == col || (cell.x >= boxStartX && cell.x < boxEndX && cell.y >= boxStartY && cell.y < boxEndY);
		});

		while (update != cells.end()){
			update->removeValueFromSet(numRemoved);
			update = find_if(next(update), cells.end(), [&row,&col,&boxStartY,&boxStartX,&boxEndY,&boxEndX](const Cell& cell){
				return cell.x == row || cell.y == col || (cell.x >= boxStartX && cell.x < boxEndX && cell.y >= boxStartY && cell.y < boxEndY);
			});
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