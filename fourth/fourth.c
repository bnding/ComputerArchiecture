#include <stdio.h>
#include <stdlib.h>

struct listnode {
	//pointers in C are reeferences in java
	int value;
	struct listnode * next;
};	

void traverse(struct listnode*);
void cleanup(struct listnode*);

void traverse(struct listnode* mylist){

	struct listnode* t1 = mylist;
	
	while(t1 != NULL){
		printf("%d\n", t1-> value);
		t1 = t1->next;
	}
	return;
}

void cleanup(struct listnode* mylist){
	struct listnode* t1 = mylist;
	struct listnode* t2 = NULL;

	while(t1 != NULL){
		t2 = t1;
		t1 = t1->next;
		free(t2);
	}
}
	

int main(int argc, char** argv){
	//creating an array that dynamically changes size
//	int * points;
	int num;
	int a;
	struct listnode * head = NULL;

	printf("how many elements\n");
	scanf("%d", &num);
	
	for(int i = 0; i < num; i++){
		scanf("%d", &a);
		//created new structure and space. This is linked list. 
		struct listnode * temp = (struct listnode *)malloc(1* sizeof(struct listnode));
		temp -> value = a;
		temp -> next = head;
		head = temp;
	}

	printf("\n\n");
	traverse(head);
	cleanup(head);
	return 0;
}

//	printf("how many elements\n");
//	scanf("%d", &num);
	
	//allocates space in the heap type "man malloc" in terminal
//	points = (int *) malloc(num * sizeof(int)); //memory allocation. returns the address. cast integer pointer pointing to what malloc returns. sizeof int gives number of bytes. Do not hard code number of bytes.

//	if (points == NULL){
//		printf("not able to allocate memory\n");
//		return 0;
//	}
	
//	for(int i = 0; i < num; i++){
//		scanf("%d", &points[i]);
//	}

//	free(points); //clears memory.
//	return 0;

	//started with arrays. declared arrays. wanted to do something better by making array dynamically change size. did dynamic memory allocation. used malloc. Declared pointer inside of an array. This pointer represents the array
	//malloc takes the size of the function in bytes. this is stored in num. but malloc takes in bytes. Need to pass the number of integers multiplied by sizeof(int). If you want to allocate any datatype use malloc.
	//need to allocate space in the heap. need to clean up. use free and use the exact address returned by malloc.
	//DO NOT DO int points[num] ALL TEST CASES WILL FAIL

//}
