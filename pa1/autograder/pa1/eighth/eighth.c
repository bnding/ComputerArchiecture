#include <stdlib.h>
#include <stdio.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
};

struct node* insert(struct node* root, int value, int count){
	if(root == NULL) {
		root= (struct node*) malloc(sizeof(struct node));
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		printf("inserted %d\n", count);
	} else if(root->data > value) {
		root->left = insert(root->left, value, count+=1);
	} else if (root->data < value){
		root->right = insert(root->right, value, count+=1);
	} else{
		printf("duplicate\n");
	}
	return root;
}

void printInorder(struct node* root){
	if(root == NULL){
		return;
	}
	printInorder(root->left);
	printf("data: %d\n", root->data);
	printInorder(root->right);
}

void search(struct node* root, int value, int count){
	if (root == NULL){
		printf("absent\n");
		return;
	} else if(root->data == value){
		printf("present %d\n", count);
		return;
	} else if(root->data >= value){
		search(root->left, value, count+=1);
	} else{
		search(root->right, value, count+=1);
	}

	
}

int main(int argc, char** argv){


	FILE *fp;
	fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("error");
		return 0;
	}

	struct node *root = (struct node*) malloc(sizeof(struct node));
	root = NULL;
	char call;
	int inputValue;

	int count = 1;
	while(fscanf(fp, "%c\t%d\n", &call, &inputValue) != EOF){
		if(call == 'i'){
			root = insert(root, inputValue, count);
			count = 1;
		} else{
			search(root, inputValue, count);
			count = 1;
		}
	}

	//printInorder(root);

	fclose(fp);
	free(root);

	return 0;

}
