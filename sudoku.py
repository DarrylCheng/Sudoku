import numpy as np

class SudokuSolver:
	def __init__(self,sd):
		self.sd = sd
		self.sd.printGrid()
		self.backtrackingSolver()
		print "\n\nSolved:"
		self.sd.printGrid()

	def backtrackingSolver(self):
		rowCol = [0,0]

		if not self.sd.getFirstEmptyGrid(rowCol):
			return True

		row = rowCol[0]
		col = rowCol[1]

		for num in range(1,10):
			if self.sd.check_location_is_safe(row,col,num):
				#assign
				self.sd.grid[row][col] = num

				if(self.backtrackingSolver()):
					return True

				self.sd.grid[row][col] = 0
		return False


class SudokuGrid:
	grid = np.array([[3,0,6,5,0,8,4,0,0],
          [5,2,0,0,0,0,0,0,0],
          [0,8,7,0,0,0,0,3,1],
          [0,0,3,0,1,0,0,8,0],
          [9,0,0,8,6,3,0,0,5],
          [0,5,0,0,9,0,6,0,0],
          [1,3,0,0,0,0,2,5,0],
          [0,0,0,0,0,0,0,7,4],
          [0,0,5,2,0,6,3,0,0]])

	def printGrid(self):
		for row in self.grid:
			print ("{} {} {} {} {} {} {} {} {}".format(*row))


	def getGrid(self):
		return self.grid

	# Returns true in number is not unique
	def checkRowUsed(self,row,num):
		for i in range(9): #Check Row
			if(self.grid[row][i] == num):
				return True
		return False

	# Returns true in number is not unique
	def checkColUsed(self,col,num):
		for i in range(9): #Check Row
			if(self.grid[i][col] == num):
				return True
		return False

	# Returns true in number is not unique
	def checkBoxUsed(self,row,col,num):
		def startingPoint(val):
			return 0 if val < 3 else 3 if val < 6 else 6
		row = startingPoint(row)
		col = startingPoint(col)
		if num in [j for i in self.grid[row:row+3,col:col+3].tolist() for j in i]:
			return True
		else:
			return False

	def check_location_is_safe(self,row,col,num):
		# Must check it's own box, row and column
		#If any return True, means number is not valid
		return not(self.checkColUsed(col,num) or self.checkRowUsed(row,num) or self.checkBoxUsed(row,col,num))
		#Returns TRUE if location is VALID

	def gridIsEmpty(self,row,col):
		return True if self.grid[row][col] == 0 else False

	def getFirstEmptyGrid(self,rowCol):
		for row in range(9):
			for col in range(9):
				if(self.grid[row][col] == 0):
					rowCol[0] = row
					rowCol[1] = col
					return True
		return False



SudokuSolver(SudokuGrid())