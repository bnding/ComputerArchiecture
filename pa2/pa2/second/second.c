#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int** readSudokuPuzzle(char* parameter){
	FILE *fp = fopen(parameter, "r");
	char val;
	int **puzzle = (int **) malloc(9 * sizeof(int*));

	for(int i = 0; i < 9; i++){
		puzzle[i] = (int*) malloc(9 * sizeof(int));
	}

	if(fp == NULL){
		return puzzle;
	}

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			fscanf(fp, "%c\t", &val);
			if(isdigit(val)){
				puzzle[i][j] = val - '0';
			} else{
				puzzle[i][j] = 0;
			}
		}
	}
	fclose(fp);
	return puzzle;
}

void printPuzzle(int** puzzle){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			printf("%d\t", puzzle[i][j]);
		}
		printf("\n");
	}
}

int haveZeros(int** puzzle){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(puzzle[i][j] == 0){
				return 1;	
			}
		}
	}
	return 0;
}

//checks if current value is unique for its specific row and column
int isRowColsUnique(int rowIndex, int colIndex, int value, int** puzzle){
	for(int i = 0; i < 9; i++){
		if(value == puzzle[i][colIndex]){
			return 0;
		}
	}

	for(int j = 0; j < 9; j++){
		if(value == puzzle[rowIndex][j]){
			return 0;
		}
	}
	return 1;
}

//checks if current value is unique for its specific subgrid
int isSubgridUnique(int rowIndex, int colIndex, int value, int** puzzle){
	int startingRowIndex;
	int startingColIndex;

	if(rowIndex < 3){
		startingRowIndex = 0;
	} else if(rowIndex < 6){
		startingRowIndex = 3;
	} else{
		startingRowIndex = 6;
	}

	if(colIndex < 3){
		startingColIndex = 0;
	} else if(colIndex < 6){
		startingColIndex = 3;
	} else{
		startingColIndex = 6;
	}

	for(int i = startingRowIndex; i < startingRowIndex+3; i++){
		for(int j = startingColIndex; j < startingColIndex+3; j++){
			if (value == puzzle[i][j]){
				return 0;
			}
		}
	}
	
	return 1;
}

void populateSinglePossibleAnswer(int** puzzle){
	//checks if the value makes the rows, cols, and 3x3 grid unique
	int count = 0;
	int value;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			for(int x = 1; x <= 9; x++){
				if(puzzle[i][j] == 0 && (isRowColsUnique(i, j, x, puzzle) == 1) && (isSubgridUnique(i, j, x, puzzle) == 1)){
					count++;
					value = x;
				}
			}
			if(count == 1){
				puzzle[i][j] = value;
			}
			count = 0;
		}
	}

}

int main(int argc, char** argv){

	int** sudoku = readSudokuPuzzle(argv[1]);

	if(sudoku == NULL || argc != 2){
		printf("error\n");
		return 0;
	}	

	for(int i = 0; i < 81; i++){
		populateSinglePossibleAnswer(sudoku);
	}

	if(haveZeros(sudoku) == 1){
			
		printf("no-solution");
	} else {
		printPuzzle(sudoku);
	}

	free(sudoku);

	return 0;



}
