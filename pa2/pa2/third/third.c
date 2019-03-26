#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int** readSudokuPuzzle(char* parameter){
	FILE *fp = fopen(parameter, "r");
	char val;
	int ** puzzle = (int **) malloc(9 * sizeof(int*));

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
			} else {
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

int empty_i;
int empty_j;
int haveZeroes(int** puzzle){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(puzzle[i][j] == 0){
				empty_i = i;
				empty_j = j;
				return 1;
			}
		}
	}

	return 0;
}

int isRowColsUnique(int rowIndex, int colIndex, int value, int** puzzle){
	for(int i = 0; i < 9; i++){
		if(puzzle[i][colIndex] != 0 && i != rowIndex){
			if(value == puzzle[i][colIndex]){
				return 0;
			}
		}
	}

	for(int j = 0; j < 9; j++){
		if(puzzle[rowIndex][j] != 0 && j != colIndex){
			if(value == puzzle[rowIndex][j]){
				return 0;
			}
		}
	}

	return 1;
}

int isSubgridUnique(int rowIndex, int colIndex, int value, int** puzzle){
	int startingRowIndex;
	int startingColIndex;

	if(rowIndex < 3){
		startingRowIndex = 0;
	} else if(rowIndex < 6) {
		startingRowIndex = 3;
	} else {
		startingRowIndex = 6;
	}

	if(colIndex < 3) {
		startingColIndex = 0;
	} else if(colIndex < 6) {
		startingColIndex = 3;
	} else {
		startingColIndex = 6;
	}

	for(int i = startingRowIndex; i< startingRowIndex+3; i++){
		for(int j = startingColIndex; j < startingColIndex+3; j++){
			if(puzzle[i][j] != 0 && i != rowIndex && j != colIndex){
				if (value == puzzle[i][j]) {
					return 0;
				}
			}
		}
	}

	return 1;
}

void populateSinglePossibleAnswer(int** puzzle){
	int count = 0;
	int value;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			for(int x = 1; x <= 9; x++){
				if(puzzle[i][j] == 0 && (isRowColsUnique(i, j, x, puzzle) == 1) && (isSubgridUnique(i, j, x, puzzle) == 1)) {
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


int solve(int** puzzle){

	//something's wrong here
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
				if((isRowColsUnique(i, j, puzzle[i][j], puzzle) != 1) ){
					return 0;
				}
				if(isSubgridUnique(i, j, puzzle[i][j], puzzle) != 1){
					return 0;
				}
			}
		}

	if(haveZeroes(puzzle) == 0){
		return 1;
	} else {
		for(int x = 1; x <= 9; x++){
			puzzle[empty_i][empty_j] = x;
			if(solve(puzzle) == 1){
				return 1;
			}
						
		}
	}
	puzzle[empty_i][empty_j] = 0;
	return 0;

}

	

int main(int argc, char** argv){

	int** sudoku = readSudokuPuzzle(argv[1]);
	
	if((sudoku == NULL) || (argc != 2)){
		printf("error\n");
		return 0;
	}

	printPuzzle(sudoku);

	


	int solved = solve(sudoku);

	printf("%d\n", solved);

	printf("\n\n\n");

	for(int i = 0; i < 81; i++){
		populateSinglePossibleAnswer(sudoku);
	}

	solved = solve(sudoku);

	populateSinglePossibleAnswer(sudoku);


	printPuzzle(sudoku);

	free(sudoku);




	return 0;
}
