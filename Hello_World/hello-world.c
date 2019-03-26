#include "stdlib.h"
#include "stdio.h"

long factorial (int);

long  mynum = 6;
int main(int argc, char** argv){
	long result;
	printf("hello world\n");
	result = factorial(mynum);
	if(argc != 2){
		printf("Insufficient argumentation");
		return 0;
	}
	
	mynum = atol(argv[1]); //atoi means ascii to integer

	printf("Arguments to this program are:\n");
	for(int i = 0; i < argc; i++){
		printf("Argument no. %d is %s\n", i, argv[i]);
	}
	printf("The factorial of %ld is %ld\n", mynum, result);//%d is used to print an integer
}

long factorial(int n){
	if (n <= 1) return 1;	
	return n*factorial(n-1);
}
