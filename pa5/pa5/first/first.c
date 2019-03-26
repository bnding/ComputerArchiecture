#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

struct var {
	//when setting input name, malloc by the strlen of input
	char* name;
	int valid;
	int value;

}; 

struct instruction {
	char* directive;
	int* inputs;
	int* outputs;
	int* selectors;
	int inputSize;
	int outputSize;
	int selectorSize;
	struct instruction * next;


};


int** grayCode;


int not(int input){
	if(input == 0){
		return 1;
	}
	return 0;
}

int and(int input1, int input2){
	if((input1*input2) == 1){
		return 1;
	}
	return 0;
}

int or(int input1, int input2){
	if ((input1+input2) == 0){
		return 0;
	}
	return 1;
}

int nand(int input1, int input2){
	return not(and(input1, input2));
}

int nor(int input1, int input2){
	return not(or(input1, input2));
}

int xor(int input1, int input2){
	if(((input1 == 1) && (input2 == 0)) || ((input1 == 0) && (input2 == 1))){
		return 1;
	}
	return 0;
}

int** createGraycode(int numInputs){
	int numLines = pow(2, numInputs);
	int * current = (int*) malloc(numInputs * sizeof(int));

	int ** grayCode = (int**) malloc(numLines * sizeof(int*));
	for(int i = 0; i < numLines; i++){	
		int decimal = i^(i>>1);
		for(int k = numInputs-1; decimal > 0; k--){
			current[k] = decimal%2;
			decimal /= 2;
		}
		grayCode[i] = (int*) malloc(numInputs * sizeof(int));
		for(int j = 0; j < numInputs; j++){
			grayCode[i][j] = current[j];
			printf("%d ", grayCode[i][j]);

		}
		printf("\n");
	}

	return grayCode;
}


void createOutput(int** grayCode, int numInputs){
	int numLines = pow(2, numInputs);
	for(int i = 0; i < numLines; i++){
		for(int j = 0; j < numInputs; j++){



		}
	}





}




int main(int argc, char** argv){
	char * inOut = malloc(12);
	char * names = malloc(100);
	char * out = malloc(100);
	char* muxChan = malloc(100);
	char* selectors= malloc(100);
	char* decIn = malloc(100);
	struct var * variables = malloc(500);
	variables[0].name = "0";
	variables[0].valid = 1;
	variables[0].value = -1;

	variables[1].name = "1";
	variables[1].valid = 1;
	variables[1].value = -1;

	int selectNum;
	int decNum;
	//struct var * vars = (struct var*) malloc(500);

	int inputNums;
	//int outputNums;


	FILE *fp = fopen(argv[1], "r");




	int index = 2;



	while(fscanf(fp, "%s", inOut) != EOF){
		printf("%s\n", inOut);
		if(strcmp(inOut, "INPUTVAR") == 0){
			fscanf(fp, "%d", &inputNums);
			printf("input nums: %d\n", inputNums);
			grayCode = createGraycode(inputNums);
			for(int i = 0; i < inputNums; i++){
				fscanf(fp, "%s", names);
				printf("%s\n", names);
				index += i;
				variables[index].name = names;
				variables[index].valid = 0;
				variables[index].value = -1;
				//vars[i].inputName = names;
			}


			printf("\n");
		} else if (strcmp(inOut, "OUTPUTVAR") == 0){
			fscanf(fp, "%d", &inputNums);
			printf("input nums: %d\n", inputNums);
			for(int i = 0; i < inputNums; i++){
				fscanf(fp, "%s", out);
				printf("%s\n", out);
				index += i;
				variables[index].name = names;
				variables[index].valid = 0;
				variables[index].value = -1;
			}

			printf("\n");
		} else if (strcmp(inOut, "MULTIPLEXER") == 0){
			fscanf(fp, "%d", &inputNums);
			for(int i = 0; i < inputNums; i++){
				fscanf(fp, "%s", muxChan);
				printf("%s\n", muxChan);
			}
			selectNum = log2(inputNums);
			for(int i = 0; i < selectNum; i++){
				fscanf(fp, "%s", selectors);
				printf("%s\n", selectors);
			}

			fscanf(fp, "%s", out);
			printf("%s\n\n", out);

		} else if (strcmp(inOut, "DECODER") == 0){
			fscanf(fp, "%d", &inputNums);
			for(int i = 0; i < inputNums; i++){
				fscanf(fp, "%s", decIn);
				printf("%s\n", decIn);
			}	       

			decNum = pow(inputNums, 2);

			for(int i = 0; i < decNum; i++){
				fscanf(fp, "%s", out);
				printf("%s\n", out);

			}
			printf("\n");
		} else if (strcmp(inOut, "OR") == 0 || strcmp(inOut, "AND") == 0 || strcmp(inOut, "NAND") == 0 || strcmp(inOut, "NOR") == 0 || strcmp(inOut, "XOR") == 0){
			//two inputs
			inputNums = 2;
			for(int i = 0; i < inputNums; i++){
				fscanf(fp, "%s", names);
				printf("%s\n", names);
			}

			fscanf(fp, "%s", out);
			printf("%s\n\n", out);

		} else if (strcmp(inOut, "NOT") == 0){
			fscanf(fp, "%s", names);
			printf("%s\n", names);

			fscanf(fp, "%s", out);
			printf("%s\n\n", out);


		}	


		else {
			break;
		}
	}
}
