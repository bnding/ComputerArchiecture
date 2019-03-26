#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
	//must be read in the argument. not in a file. add all characters into a string and then implement from bottom code.
	//int count = 0;
	for(int i = 1; i < argc; i++){	
		char * temp = argv[i];
		int count = 0;
		while(temp[count] != temp[strlen(temp)-1]){
			count += 1;
		}
		printf("%c", temp[count]);
	}

	return 0;
			










}
