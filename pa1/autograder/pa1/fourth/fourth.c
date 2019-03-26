#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int a;
	//int b;

	int rows;
	int cols;

	int rows2;
	int cols2;


	FILE *fp;

	//matrix1
	fp = fopen(argv[1], "r");
	fscanf(fp, "%d\t%d\n", &rows, &cols);

	int ** matrix1;
	matrix1 = (int**)  malloc(rows * sizeof(int *));

	for(int i = 0; i < rows; i++){
		matrix1[i] = (int *) malloc(cols * sizeof(int));
	}

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			fscanf(fp, "%d", &a);
			matrix1[i][j] = a;
		}
	}

	fscanf(fp, "%d\t%d\n", &rows2, &cols2);

	if(cols != rows2){
		printf("bad-matrices");
		return 0;
	}

	//matrix2
	int ** matrix2;
	matrix2 = (int**)  malloc(rows2 * sizeof(int *));

	for(int i = 0; i < rows2; i++){
		matrix2[i] = (int *) malloc(cols2 * sizeof(int));
	}

	for(int i = 0; i < rows2; i++){
		for(int j = 0; j < cols2; j++){
			fscanf(fp, "%d", &a);
			matrix2[i][j] = a;
		}
	}

	fclose(fp);

	//multiply
	int ** finalMatrix;
	finalMatrix = (int **) malloc(rows * sizeof(int *));

	for(int i = 0; i < rows; i++){
		finalMatrix[i] = (int *) malloc(cols2 * sizeof(int));
	}

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols2; j++){
			int sum = 0;
			for(int k = 0; k < cols; k++){
				sum += (matrix1[i][k] * matrix2[k][j]);
			}
			finalMatrix[i][j] = sum;
			printf("%d\t", finalMatrix[i][j]);
		}
		printf("\n");
	}

	for(int i = 0; i < rows2; i++){
		free(finalMatrix[i]);
	}

	free(finalMatrix);

	for(int i = 0; i < rows; i++){
		free(matrix1[i]);
	}

	free(matrix1);

	for(int i = 0; i < rows2; i++){
		free(matrix2[i]);
	}

	free(matrix2);

	return 0;

}

