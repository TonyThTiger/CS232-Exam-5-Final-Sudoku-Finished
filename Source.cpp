#include<iostream>

using namespace std;
const int SIZE = 9;

void initializeCrossArray(int crossArr[][SIZE]);
bool testSquares(int puzzleArr[][SIZE], int crossArr[][SIZE], int currentNum);
void makeHatches(int puzzleArr[][SIZE], int crossArr[][SIZE], int currentNum);
void displayArray(int array[][SIZE]);
void crossRow(int crossArr[][SIZE], int rowPar);
void crossColumn(int crossArr[][SIZE], int colPar);
bool isComplete(int puzzleArray[][SIZE]);


int main() {

	int puzzleArray[SIZE][SIZE] = { {5,3,4,0,7,0,9,1,2},
								   {6,0,0,1,9,5,0,0,0},
								   {0,9,8,0,0,0,0,6,0},
								   {8,0,0,0,6,0,0,0,3},
								   {4,0,0,8,0,3,0,0,1},
								   {7,0,0,0,2,0,0,0,6},
								   {0,6,0,0,0,0,2,8,4},
								   {2,8,7,4,1,9,0,0,5},
								   {3,4,5,0,8,0,0,7,9} };


	int puzzleArray2[SIZE][SIZE] = { {0,6,2,3,0,8,4,0,0},
									{1,8,5,0,2,0,7,0,3},
									{0,7,0,0,0,1,0,0,0},
									{0,0,0,0,4,5,3,9,6},
									{0,9,0,0,0,0,1,0,7},
									{7,0,0,0,9,6,2,8,0},
									{5,3,1,9,0,0,6,0,0},
									{0,4,9,0,5,0,0,0,1},
									{0,2,0,6,0,0,0,4,0} };

	int crossHatch[SIZE][SIZE];
	initializeCrossArray(crossHatch);
	cout << "Unsolved Puzzle: " << endl;
	displayArray(puzzleArray);
	cout << endl;


	while (!isComplete(puzzleArray)) {
		for (int workingNum = 1; workingNum <= 9; workingNum++) {
			makeHatches(puzzleArray, crossHatch, workingNum);
			testSquares(puzzleArray, crossHatch, workingNum);
			initializeCrossArray(crossHatch);
		}
	}
	cout << "Solved Puzzle:" << endl;
	displayArray(puzzleArray);

	return 0;
}



void initializeCrossArray(int crossArr[][SIZE]) {
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			crossArr[i][j] = 0;
		}
	}
}

void makeHatches(int puzzleArr[][SIZE], int crossArr[][SIZE], int currentNum) { //could be optimized further
	for (int row = 1; row <= 9; row++) {
		for (int col = 1; col <= 9; col++) {
			if (puzzleArr[row - 1][col - 1] == currentNum) {
				crossRow(crossArr, row - 1);
				col = 10;
			}
		}
	}

	for (int col = 1; col <= 9; col++) {
		for (int row = 1; row <= 9; row++) {
			if (puzzleArr[row - 1][col - 1] == currentNum) {
				crossColumn(crossArr, col - 1);
				row = 10;
			}
		}
	}

	for (int i = 0; i < SIZE; i++) //marks spaces that are already filled
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (puzzleArr[i][j] != 0) {
				crossArr[i][j] = 1;
			}
		}
	}
}

void displayArray(int array[][SIZE]) {
	for (int row = 1; row <= SIZE; row++)
	{
		for (int col = 1; col <= SIZE; col++)
		{
			cout << array[row - 1][col - 1];
			if (col % 3 == 0 && col != 9) {
				cout << "|";
			}
		}
		cout << endl;
		if (row % 3 == 0 && row != 9) {
			cout << "-----------" << endl;
		}
	}
}

void crossRow(int crossArr[][SIZE], int rowPar) {
	for (int col = 1; col <= SIZE; col++)
	{
		crossArr[rowPar][col - 1] = 1;
	}

}
void crossColumn(int crossArr[][SIZE], int colPar) {
	for (int row = 1; row <= SIZE; row++)
	{
		crossArr[row - 1][colPar] = 1;
	}
}

bool isComplete(int puzzleArray[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (puzzleArray[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool testSquares(int puzzleArr[][SIZE], int crossArr[][SIZE], int currentNum) {
	int count = 0;
	int saveRow, saveCol;
	int row = 0, col = 0;
	bool isInSquare = false;
	for (int squareNum = 0; squareNum < 9; squareNum++) {
		count = 0;
		isInSquare = false;
		for (int tempRow = row; tempRow < row + 3; tempRow++) {
			for (int tempCol = col; tempCol < col + 3; tempCol++)
			{
				if (crossArr[tempRow][tempCol] == 0) {
					count++;
					saveRow = tempRow;
					saveCol = tempCol;
				}
				if (puzzleArr[tempRow][tempCol] == currentNum) {
					isInSquare = true;
				}
			}
		}
		if (count == 1 && isInSquare == false && puzzleArr[saveRow][saveCol] == 0) {
			puzzleArr[saveRow][saveCol] = currentNum;
			return true;
		}
		switch (squareNum) {
		case 0:
			row = 0;
			col = 3;
			break;
		case 1:
			row = 0;
			col = 6;
			break;
		case 2:
			row = 3;
			col = 0;
			break;
		case 3:
			row = 3;
			col = 3;
			break;
		case 4:
			row = 3;
			col = 6;
			break;
		case 5:
			row = 6;
			col = 0;
			break;
		case 6:
			row = 6;
			col = 3;
			break;
		case 7:
			row = 6;
			col = 6;
			break;
		default:
			squareNum = 10;
			break;
		}
	}

	return false;
}