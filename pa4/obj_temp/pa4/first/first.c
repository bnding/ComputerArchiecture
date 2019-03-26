#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

struct node{
	unsigned long long int valid;
	unsigned long long int tag;
	unsigned long long int count;
};

int power;
char* assocStr;
int assocNum;
int cacheSize;
int blockSize;
char* cachePolicy;
int setNum;

void noPrefetch(FILE *fp){
	struct node ** noPrefetch = (struct node**) malloc(setNum * sizeof(struct node*)); 
	for(int i = 0; i < setNum; i++){
		noPrefetch[i] = (struct node*) malloc(assocNum * sizeof(struct node));
	}

	for(int i = 0; i < setNum; i++){
		for(int j = 0; j < assocNum; j++){
			noPrefetch[i][j].valid = 0;
			noPrefetch[i][j].tag = -1;
		}
	}

	int counter = 0;	
	int blockOffset = log2(blockSize);
	int setOffset = log2(setNum);
	int hit = 0;
	int read = 0;
	int miss = 0;
	int write = 0;
	unsigned long long int accessedAddress;
	unsigned long long int useless;
	char operation;
	while(fscanf(fp, "%llx: %c %llx", &useless, &operation, &accessedAddress)){
		counter++;
		int smallestCountIndex = 0;
		unsigned long long int currTag = accessedAddress >> (blockOffset + setOffset);

		int setIndex = (accessedAddress >> blockOffset) & ((1 << setOffset) - 1);
		int currentCount = noPrefetch[setIndex][0].count;

		if(operation == 'W'){
			write++;
		}

		int flag = 0;

		for(int i = 0; i < assocNum; i++){
			if(noPrefetch[setIndex][i].count < currentCount){
				smallestCountIndex = i;
				currentCount = noPrefetch[setIndex][i].count;
			}
			if(noPrefetch[setIndex][i].valid == 0){
				noPrefetch[setIndex][i].tag = currTag;
				noPrefetch[setIndex][i].count = counter;
				noPrefetch[setIndex][i].valid = 1;
				read++;
				miss++;
				flag = 1;
				break;
			}else if(noPrefetch[setIndex][i].tag == currTag){
				hit++;
				flag = 1;
				break;
			}

		}

		if(flag == 0){
			noPrefetch[setIndex][smallestCountIndex].tag = currTag;
			noPrefetch[setIndex][smallestCountIndex].count = counter;
			read++;
			miss++;
		}



	}	


	printf("no-prefetch\n");
	printf("Memory reads: %d\n", read);
	printf("Memory writes: %d\n", write);
	printf("Cache hits: %d\n", hit);
	printf("Cache misses: %d\n", miss);


}


void withPrefetch(FILE *fp){
	struct node ** noPrefetch = (struct node**) malloc(setNum * sizeof(struct node*)); 
	for(int i = 0; i < setNum; i++){
		noPrefetch[i] = (struct node*) malloc(assocNum * sizeof(struct node));
	}

	for(int i = 0; i < setNum; i++){
		for(int j = 0; j < assocNum; j++){
			noPrefetch[i][j].valid = 0;
			noPrefetch[i][j].tag = -1;
		}
	}

	int counter = 0;	
	int blockOffset = log2(blockSize);
	int setOffset = log2(setNum);
	int hit = 0;
	int read = 0;
	int miss = 0;
	int write = 0;
	unsigned long long int accessedAddress;
	unsigned long long int useless;
	char operation;
	while(fscanf(fp, "%llx: %c %llx", &useless, &operation, &accessedAddress)){
		counter++;
		int smallestCountIndex = 0;
		unsigned long long int currTag = accessedAddress >> (blockOffset + setOffset);

		int setIndex = (accessedAddress >> blockOffset) & ((1 << setOffset) - 1);
		int currentCount = noPrefetch[setIndex][0].count;

		if(operation == 'W'){
			write++;
		}

		int flag = 0;
		int flag3 = 0;

		for(int i = 0; i < assocNum; i++){
			if(noPrefetch[setIndex][i].count < currentCount){
				smallestCountIndex = i;
				currentCount = noPrefetch[setIndex][i].count;
			}
			if(noPrefetch[setIndex][i].valid == 0){
				noPrefetch[setIndex][i].tag = currTag;
				noPrefetch[setIndex][i].count = counter;
				noPrefetch[setIndex][i].valid = 1;
				read++;
				miss++;
				flag = 1;
				flag3 = 1;
				break;
			}else if(noPrefetch[setIndex][i].tag == currTag){
				hit++;
				flag = 1;
				break;
			}

		}

		if(flag == 0){
			noPrefetch[setIndex][smallestCountIndex].tag = currTag;
			noPrefetch[setIndex][smallestCountIndex].count = counter;
			flag3 = 1;
			read++;
			miss++;
		}


		if(flag3 == 1){
			counter++;
			int prefSmallest= 0;
			unsigned long long int prefTag = (accessedAddress+blockSize) >> (blockOffset + setOffset);

			int prefSetIndex = ((accessedAddress+blockSize) >> blockOffset) & ((1 << setOffset) - 1);
			int prefCurrentCount = noPrefetch[prefSetIndex][0].count;

			int flag2 = 0;

			for(int i = 0; i < assocNum; i++){
				if(noPrefetch[prefSetIndex][i].count < prefCurrentCount){
					prefSmallest= i;
					prefCurrentCount = noPrefetch[prefSetIndex][i].count;
				}
				if(noPrefetch[prefSetIndex][i].valid == 0){
					noPrefetch[prefSetIndex][i].tag = prefTag;
					noPrefetch[prefSetIndex][i].count = counter;
					noPrefetch[prefSetIndex][i].valid = 1;
					read++;
					flag2 = 1;
					break;
				}else if(noPrefetch[prefSetIndex][i].tag == prefTag){
					flag2 = 1;
					break;
				}

			}

			if(flag2 == 0){
				noPrefetch[prefSetIndex][prefSmallest].tag = prefTag;
				noPrefetch[prefSetIndex][prefSmallest].count = counter;
				read++;
			}
		}






	}	


	printf("with-prefetch\n");
	printf("Memory reads: %d\n", read);
	printf("Memory writes: %d\n", write);
	printf("Cache hits: %d\n", hit);
	printf("Cache misses: %d\n", miss);





}


int isPowerOfTwo(int num){
	while(num >= 2){
		num = num % 2;
	}

	if(num == 0){
		return 1;
	} else {
		return 0;
	}

}

int checkInputs(int argc, char** argv){
	if(argc != 6){
		return 0;
	}



	cacheSize = atoi(argv[1]);
	if(isPowerOfTwo(cacheSize) == 0){
		return 0;
	} else {	
	}

	assocStr = argv[2];
	blockSize = atoi(argv[4]);
	power = 0;
	if(strcmp(assocStr, "direct") == 0){
		setNum = cacheSize/blockSize;
		assocNum = 1;

		//		printf("direct\n");
	} else if (strcmp(assocStr, "assoc") == 0){
		setNum = 1;
		assocNum = cacheSize/blockSize;
		//		printf("associative cache\n");
	} else if (strstr(assocStr, "assoc:") != NULL){
		for(int i = 0; i < strlen(assocStr); i++){
			if(isdigit(assocStr[i])){
				if(power == 0){
					power = assocStr[i] - '0';
				} else if(power > 0){
					power = power * 10 + assocStr[i] - '0';
				} else {
					return 0;
				}
			}
			if(isPowerOfTwo(power) == 0){
				return 0;
			}
		}
		setNum = (cacheSize/blockSize)/power;
		assocNum = power;
		//		printf("associative cache with a power of %d\n", power);
	} else {
		return 0;
	}


	cachePolicy = argv[3];
	if (strcmp(cachePolicy, "fifo") == 0){
		//		printf("first in first out\n");
	} else {
		return 0;
	}
	if (blockSize > 0){
		//		printf("block size: %d\n\n\n", blockSize);
	} else {
		return 0;
	}
	return 1;
}


int main(int argc, char** argv){
	if(checkInputs(argc, argv) == 0){
		printf("error\n");
		return 0;
	}

	FILE *fp = fopen(argv[5], "r");
	if(fp == NULL){
		printf("error\n");
		fclose(fp);
		return 0;

	}

	noPrefetch(fp);
	fclose(fp);
	FILE *fp2 = fopen(argv[5], "r");
	withPrefetch(fp2);
	fclose(fp2);



	return 0;



}
