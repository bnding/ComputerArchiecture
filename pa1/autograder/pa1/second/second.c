#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node * next;
};

void delete(struct node** list, int removingData){
	struct node* temp = *list;
	struct node* prev;


	//empty list
	if(temp == NULL){
		return;
	}

	//removing value is head
	if(temp != NULL && temp->data == removingData){
		*list = temp->next;
		free(temp);
		return;
	}

	//searching through
	while(temp != NULL){
		if(temp->data == removingData){
			prev->next = temp->next;
		}
		prev = temp;
		temp = temp->next;
	}

	free(temp);
}

void insert(struct node** list, int val){
	//if it is empty
	struct node * newNode = (struct node*) malloc(sizeof(struct node));
	newNode->data = val;
	
	//if it is an empty list or if the node we're inserting is smaller than the current head
	if(*list == NULL || (*list)->data > val){
		newNode->next = *list;
		*list = newNode;
		return;
	}

	//if this head is equal to the node we're inputting (no repeats)
	if((*list)->data == val){
		return;
	}

	struct node *ptr;
	ptr = (struct node*) malloc(sizeof(struct node));
	ptr = *list;
	//checking if there is a duplicate. if there is none, ptr will be NULL
	while(ptr->next != NULL && ptr->next->data != val){
		ptr = ptr->next;
	}

	//checks if a duplicate has been found
	if(ptr->next != NULL){
		return;
	}	

	//finally traversing through to add new node
	ptr = *list;
	while(ptr->next != NULL && ptr->next->data < val){
		ptr = ptr->next;
	}
	newNode->data = val;
	newNode->next = ptr->next;
	ptr->next = newNode;
}

void traverse(struct node* list){
	struct node *temp = list;
	struct node *temp2 = list;
	int count = 0;

	while(temp2 != NULL){
		count++;
		temp2 = temp2->next;
	}
	free(temp2);
	printf("%d\n", count);
	while(temp != NULL){
		printf("%d\t", temp->data);
		temp = temp->next;	
	}
}

void freeList(struct node* list){
	struct node* ptr;
	while(list != NULL){
		ptr = list;
		list = list->next;
		free(ptr);
	}
}

int main(int argc, char** argv){
	FILE *fp;
	char insertOrDelete;
	int inputValue;

	fp = fopen(argv[1], "r");

	if((argc != 2) || (fp == NULL)){
		printf("error");
		return 0;
	}

	struct node * list = (struct node*) malloc(sizeof(struct node));
	list = NULL;
	while(fscanf(fp, "%c\t%d\n", &insertOrDelete, &inputValue) != EOF){
		if(insertOrDelete == 'd'){
			delete(&list, inputValue);
		} else {
			insert(&list, inputValue);
		}
	}	

	if(list == NULL){
		printf("0\n");
		freeList(list);
		return 0;
	}
	if(list->data == 0){
		list = list->next;
		return 0;
	}

	traverse(list);
	freeList(list);
	fclose(fp);
	return 0;
}
