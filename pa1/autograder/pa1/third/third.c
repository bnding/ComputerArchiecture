#include <stdlib.h>
#include <stdio.h>

struct node{
	int data;
	struct node * next;
};

struct node * list[10000];
int main(int argc, char** argv){

	FILE *fp;
	fp = fopen(argv[1], "r");


	char heapAction;
	int value;

	while(fscanf(fp, "%c\t%d\n", &heapAction, &value) != EOF){
		//printf("%c\t%d\n", heapAction, value);
		if(heapAction == 'i'){
			int index = abs(value) % 10000;
			struct node * ptr = list[index];
			if(list[index] == NULL){
				struct node *temp = (struct node*) malloc(sizeof(struct node));
				temp -> data = value;
				temp -> next = list[index];
				list[index] = temp;
				printf("inserted\n");
			} else {
				int duplicate = 0;
				if(ptr->data == value){
					duplicate = 1;
				}
				while(ptr->next != NULL && duplicate == 0){
					//printf("hello\n\n");
					if(ptr->data == value){
						duplicate = 1;
					}
					ptr = ptr->next;
					//printf("%d\n\n\n", duplicate);
				}

				if(duplicate == 1){
					printf("duplicate\n");
				} else{
					//printf("hello\n\n\n");
					struct node *temp = (struct node*) malloc(sizeof(struct node));
					temp-> data = value;
					temp -> next = list[index];
					list[index] = temp;
					printf("inserted\n");
				}
			}
		} else if(heapAction == 's'){
			int index = abs(value) % 10000;
			struct node* searchList = list[index];
			while(searchList != NULL){
				if(searchList->data == value){
					printf("present\n");
					break;
				}
				searchList = searchList->next;
			}
			if(searchList == NULL){
				printf("absent\n");
			}
		}
	}

	fclose(fp);
	return 0;





}
