#include <stdio.h>
#include <stdlib.h>
int b;

int main(int argc, char** argv){
	if (argc != 2){
		printf("not enough arguments\n");
		return 0;
	}
	FILE *fp;
	int b;
	char a;

	int i;
	for(i = 0; i < argc; i++){
		printf("Argument no. %d is %s\n", i, argv[i]);
	}

	fp = fopen(argv[1], "r");

	while(fscanf(fp, "%c %d\n", &a, &b) != EOF){
		printf("%c %d\n", a, b);
	}

	fclose(fp);
	return 0;
}
