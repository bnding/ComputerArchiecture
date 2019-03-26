#include <stdio.h>
#include <stdlib.h>

void selectionSort(int array[], int size){
	for(int i = 0; i < size; i++){
		int min = i;
		for(int j = i+1; j < size; j++){
			if (array[j] < array[min]){
				min = j;
			}
		}
		int temp = array[min];
		array[min] = array[i];
		array[i] = temp;
	}
}


int main(int argc, char** argv){
	int inputNum;
	int evenCount = 0;
	int oddCount = 0;

	FILE *fp;
	fp = fopen(argv[1], "r");
	fscanf(fp, "%d\n",&inputNum);

	int *array = (int *) malloc(inputNum * sizeof(int));
	for(int i = 0; i < inputNum; i++){
		fscanf(fp, "%d", &array[i]);
		if(array[i] % 2 == 0){
			evenCount++;
		} else {
			oddCount++;
		}
	}

	
	int evenArray[evenCount];
	int evenIndex = 0;
	int oddArray[oddCount];
	int oddIndex = 0;
	

	for(int i = 0; i < inputNum; i++){
		if(array[i] % 2 == 0){
			evenArray[evenIndex] = array[i];
			evenIndex++;
		} else {
			oddArray[oddIndex] = array[i];
			oddIndex++;
		}
	}

	selectionSort(evenArray, evenCount);
	selectionSort(oddArray, oddCount);

	for(int i = 0; i < evenCount; i++){
		array[i] = evenArray[i];
	}

	for(int i = 0; i < oddCount; i++){
		array[i+evenCount] = oddArray[i];

	}


	for(int i = 0; i < inputNum; i++){
		printf("%d\t", array[i]);
	}

	
	fclose(fp);
	free(array);
	return 0;
}
