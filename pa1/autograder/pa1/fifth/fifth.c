#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	int a;
	int rows;

	FILE *fp;
	fp = fopen(argv[1], "r");
	fscanf(fp, "%d\n", &rows);

	if(rows == 1){
		printf("magic");
		return 0;
	} else if (rows == 2){
		printf("not-magic");
		return 0;
	}

	int** matrix;
	matrix = (int**) malloc(rows * sizeof(int *));

	for(int i = 0; i < rows; i++){
		matrix[i] = (int *) malloc(rows * sizeof(int));
	}

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < rows; j++){
			fscanf(fp, "%d", &a);
			matrix[i][j] = a;
		}
	}


	int sum = 0;
	int* array1;
	array1 = (int*) malloc(rows * sizeof(int));	

	//adds each column, put in array;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < rows; j++){
			sum +=  matrix[j][i];
		}
		array1[i] = sum;
		sum = 0;
	}


	int* array2;
	array2 = (int *) malloc(rows * sizeof(int));
	//adds each row, put in array
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < rows; j++){
			sum += matrix[i][j];
		}
		array2[i] = sum;
		sum = 0;
	}

	//adds single diagonal left -> right
	int diagonal1 = 0;
	for(int i = 0; i < rows; i++){
		diagonal1 += matrix[i][i];
	}


	int diagonal2 = 0;
	for(int i = rows-1; i >= 0; i--){
		diagonal2 += matrix[rows-1][(rows-1)-i];
	}

	int notMagic = 0;
	for(int i = 0; i < rows; i++){
		if(array1[i] != array2[i]){
			notMagic = 1;
		}
	}

	if(diagonal1 != diagonal2 || diagonal1 != array1[1]){
			notMagic = 1;
	}

	if(notMagic == 1){
		printf("not-magic");
	} else{
		printf("magic");
	}

	free(array1);
	free(array2);

	for(int i = 0; i < rows; i++){
		free(matrix[i]);
	}
	free(matrix);	
	fclose(fp);


	return 0;

}
