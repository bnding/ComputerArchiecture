#include <stdio.h>
#include <stdlib.h>

struct matrix{
	double** data;
	int rows;
	int cols;
};

struct matrix matrixX;
struct matrix matrixY;

//reads and creates the proper format of matrix x and y
void readMatrixXandY(char* parameter){
	FILE *fp = fopen(parameter, "r");

	if(fp == NULL){
		return;
	}

	fscanf(fp, "%d\n%d\n", &matrixX.cols, &matrixX.rows);

	matrixX.data = (double**) malloc(matrixX.rows * sizeof(double*));
	matrixY.rows = matrixX.rows;
	matrixY.data = (double**) malloc(matrixY.rows * sizeof(double*));
	matrixY.cols = 1;

	matrixX.cols = matrixX.cols+1;
	for(int i =0; i < matrixX.rows; i++){
		matrixX.data[i] = (double *) malloc((matrixX.cols) * sizeof(double));
		matrixY.data[i] = (double *) malloc(sizeof(double));
	}

	double value;
	for(int i = 0; i < matrixX.rows; i++){
		matrixX.data[i][0] = 1.0;
		for(int j = 1; j < matrixX.cols+1; j++){
			fscanf(fp, "%lf,", &value);
			if(j == matrixX.cols){
				matrixY.data[i][0] = value;
			} else {
				matrixX.data[i][j] = value;
			}
		}
	}

	fclose(fp);
}

void solvePrice(char* parameter, struct matrix weight){
	FILE *fp = fopen(parameter, "r");

	if(fp == NULL){
		return;
	}

	int houses;
	double value;

	fscanf(fp, "%d\n", &houses);

	double sum = 0;
	for(int i = 0; i < houses; i++){
		sum = weight.data[0][0];
		for(int j = 1; j < weight.rows; j++){
			fscanf(fp, "%lf,", &value);
			sum += (weight.data[j][0] * value);	
		}	
		printf("%0.0lf\n", sum);
		sum = 0;
	}


	fclose(fp);
}

		

struct matrix transposeX(struct matrix input){
	struct matrix transpose;
	transpose.data = (double**) malloc((input.cols)* sizeof(double*));
	for(int i = 0; i < input.cols; i++){
		transpose.data[i]= (double *) malloc((input.rows) * sizeof(double));
	}
	
	for(int i = 0; i < input.rows; i++){
		for(int j = 0; j < input.cols; j++){
			transpose.data[j][i] = input.data[i][j];
		}
	}

	transpose.rows = input.cols;
	transpose.cols = input.rows;

	return transpose;
}

void printMatrices(struct matrix input){
	for(int i = 0; i < input.rows; i++){
		for(int j = 0; j < input.cols; j++){
			printf("%lf\t", input.data[i][j]);
		}
		printf("\n");
	}
}
 
struct matrix multiply(struct matrix matrix1, struct matrix matrix2){
	struct matrix productMatrix;
	productMatrix.data = (double **) malloc((matrix1.rows)* sizeof(double*));
	for(int i = 0; i < matrix1.rows; i++){
		productMatrix.data[i] = (double *) malloc(matrix2.cols * sizeof(double));
	}

	for(int i = 0; i < matrix1.rows; i++){
		for(int j = 0; j < matrix2.cols; j++){
			double sum = 0;
			for(int k = 0; k < matrix1.cols; k++){
				sum += (matrix1.data[i][k] * matrix2.data[k][j]);
			}
			productMatrix.data[i][j] = sum;
		}
	}

	productMatrix.rows = matrix1.rows;
	productMatrix.cols = matrix2.cols;
	return productMatrix;
}

struct matrix inverse(struct matrix matrix){
	struct matrix inverseMatrix;
	inverseMatrix.rows = matrix.rows;
	inverseMatrix.cols = matrix.cols;
	//setting up the inverse matrix
	inverseMatrix.data = (double**) malloc(matrix.rows * sizeof(double*));
	for(int i = 0; i < matrix.rows; i++){
		inverseMatrix.data[i] = (double*) malloc(matrix.cols * sizeof(double));
	}

	for(int i = 0; i < inverseMatrix.rows; i++){
		for(int j = 0; j < inverseMatrix.cols; j++){
			if(j == i){
				inverseMatrix.data[i][j] = 1;
			}
		}
	}

	//Creating pivot columns
	//getting lower diagonal first.
	for(int i = 0; i < matrix.rows; i++){
		double divisor = 1/matrix.data[i][i];
		for(int j = 0; j < matrix.cols; j++){
			matrix.data[i][j] *= divisor;
			inverseMatrix.data[i][j] *= divisor;
		}

		for(int x = 0; x < matrix.rows; x++){
			double ratio = matrix.data[x][i];
			if(x > i){
				for(int y = 0; y < matrix.cols; y++){
						matrix.data[x][y] -= (ratio* matrix.data[i][y]);
						inverseMatrix.data[x][y] -= (ratio * inverseMatrix.data[i][y]);
				}
			}
		}
	}

	//upper diagonal
	for(int i = matrix.rows-1; i >= 0; i--){
		for(int x = matrix.rows-1; x >= 0; x--){
			double ratio = matrix.data[x][i];
				if(x < i){
					for(int y = matrix.cols-1; y >= 0; y--){
						matrix.data[x][y] -= (ratio* matrix.data[i][y]);
						inverseMatrix.data[x][y] -= (ratio * inverseMatrix.data[i][y]);
	
					}	
				}

		}
	}
	return inverseMatrix;
}

int main(int argc, char** argv){
	if(argc != 3){
		printf("error\n");
		return 0;
	}

	readMatrixXandY(argv[1]);

	if(matrixX.data == NULL || matrixY.data == NULL){
		printf("error\n");
		return 0;
	}

	struct matrix xT;
	xT= transposeX(matrixX);

	struct matrix xTx;
	xTx = multiply(xT, matrixX);
	struct matrix inverseMatrix = inverse(xTx);

	struct matrix temp = multiply(inverseMatrix, xT);

	struct matrix finalMatrix = multiply(temp, matrixY);

	solvePrice(argv[2], finalMatrix);

	return 0;

}
