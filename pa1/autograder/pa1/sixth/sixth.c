#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char vowels[11] = {'A','a','E','e','I','i','O','o','U','u'};
int main(int argc, char** argv){

	int count = argc;

	int i;
	for(i = 1; i < count; i++){
		int hasVowel = 0;
		char * current = argv[i];
		int j;
		for(j = 0; j < strlen(vowels); j++){
			if(vowels[j] == current[0]){
				char *temp =(char*) malloc(strlen(current) + 1 + 3);
				strcpy(temp, current);
				strcat(temp, "yay");
				printf("%s ", temp);
				hasVowel = 1;	
				free(temp);
				j = strlen(vowels)-1;
			}
		}


		if(hasVowel == 0){
			char *temp = (char*)malloc(strlen(current) + 1 + 5);
			strcpy(temp, current);
			char *copy = (char*) malloc(strlen(temp));
			
			//might be +1, or none. need to check.
			temp[strlen(temp)] = '\0';
			int k = 0;

			if(strlen(temp) < 2){
				temp[strlen(temp)-1] = temp[0];
				strcat(temp, "ay");
				printf("%s ", temp);
			}else {

				//count how many consonants until first vowel shows up.
			
				int iterations = -1;
				int x;
				for(x = 0; temp[x] != '\0'; x++){
					iterations = iterations+1;

					int y;
					for(y = 0; y < strlen(vowels); y++){
						if(temp[x] == vowels[y]){
							x = strlen(temp)-1;
							y = strlen(vowels)-1;
						}
					}
				}

				//printf("iterations: %d\n\n", iterations);

				while(k <= iterations){
					int j;
					if(iterations < 2){
						for(j = 0; temp[j] != '\0'; j++){
							//printf("Index: %d\n", j);
							//printf("Temp: %s\tCharacter: %c\n", temp, temp[0]);


							temp[strlen(temp)] = temp[0];
							//printf("Temp: %s\n", temp);


							temp[j] = temp[j+1];
							//printf("Temp: %s\n", temp);

							temp[strlen(temp)] = '\0';
							//printf("Temp: %s\n", temp);

							temp++;
							//printf("Temp: %s\n", temp);



							copy = (char*) malloc(strlen(temp) + 1 + 2);
							strcpy(copy, temp);
							temp = (char*) malloc(strlen(temp) + 1 + 2);
						}
					} else if (iterations < 3){
						for(j = 0; temp[j] != '\0'; j++){
							//printf("Index: %d\n", j);
							//printf("Temp: %s\tCharacter: %c\n", temp, temp[0]);


							temp[strlen(temp)] = temp[0];
							//printf("Temp: %s\n", temp);


							temp[j] = temp[j+1];
							//printf("Temp: %s\n", temp);

							temp[strlen(temp)] = temp[0];
							//printf("Temp: %s\n", temp);

							temp[strlen(temp)] = '\0';
							//printf("Temp: %s\n", temp);

							temp++;
							temp++;
							//printf("Temp: %s\n", temp);

							copy = (char*) malloc(strlen(temp) + 1 + 2);
							strcpy(copy, temp);
							temp = (char*) malloc(strlen(temp) + 1 + 2);
						}
					} else {
						for(j = 0; temp[j] != '\0'; j++){
							temp[strlen(temp)] = temp[0];
							//printf("Temp: %s\n", temp);


							temp[j] = temp[j+1];
							//printf("Temp: %s\n", temp);

							temp[strlen(temp)] = temp[0];
							//printf("Temp: %s\n", temp);
							

							temp++;
							temp++;
							//printf("Temp: %s\n", temp);

							temp[strlen(temp)] = temp[0];
							temp++;

							temp[strlen(temp)] = '\0';
							//printf("Temp: %s\n", temp);

							copy = (char*) malloc(strlen(temp) + 1 + 2);
							strcpy(copy, temp);
							temp = (char*) malloc(strlen(temp) + 1 + 2);
						}
					}					
	
					k += 1;
				}

				strcat(copy, "ay");
				printf("%s ", copy);
				free(temp);
				free(copy);
			}
		}
	}



	return 0;
}
