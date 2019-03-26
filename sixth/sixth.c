//simple string characters
#include <stdio.h>
#include <stdlib.h>

char* mystrcpy(char* dest, char* src){
	char* temp = dest;
	while(*src != '\0'){
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return temp;
}

int main(int argc, char** argv){

	//malloc activates chunks of memory. it does not relocate

	int len;
	char c;
	char* ptr;

	printf("enter the number of characters\n");
	scanf("%d\n", &len); //everything is a character. even enter. so you need \n

	ptr = (char*) malloc(sizeof(char) * (len+1));

	for(int i = 0; i < len; i++){
		scanf("%c", &c);
		ptr[i] = c;
		//*(ptr + i) = c;
		//p[0] is same as *(p+0)
		//p[1] = *(p+1)
	}

	ptr[len] = '\0'; //IMPORTANT shows that the string is terminated

	printf("entered string is %s\n", ptr);
	free(ptr);

	char* mynew_string = (char*) malloc(100 * sizeof(char));
	mystrcpy(mynew_string, ptr);
	printf("the copied string is %s\n", mynew_string);

	return 0;




}
