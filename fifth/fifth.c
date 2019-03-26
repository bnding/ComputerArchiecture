#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int size1, size2;
	printf("enter size1 and size2 \n");
	scanf("%d %d", &size1, &size2);

	int ** matrix;
	matrix = (int**) malloc(size1 * sizeof(int *));

	for(int i = 0; i < size1; i++){
		matrix[i] = (int *)malloc(size2 * sizeof(int));
	}

	for(int i = 0; i < size1; i++){
		for(int j = 0; j < size2; j++){
			matrix[i][j] = j;
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	for(int i = 0; i < size1; i++){
		free(matrix[i]);
	}

	free(matrix);
	return 0;
}
