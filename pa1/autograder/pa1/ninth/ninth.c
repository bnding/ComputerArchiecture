#include <stdlib.h>
#include <stdio.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
};

struct node* insert(struct node* root, int value, int count){
	if(root == NULL) {
		//struct node * newNode = (struct node*) malloc(sizeof(struct node));
		//newNode->data = value;
		//newNode->left = NULL;
		//newNode->right = NULL;
		//root = newNode;
		root = (struct node*) malloc(sizeof(struct node));
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		//root = newNode;
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


struct node* removeNode(struct node* root, int value){
	//did not find it
	if(root == NULL){
		printf("fail\n");
		return root;
	}

	if(root->data > value) {
		root->left = removeNode(root->left, value);
	} else if(root->data < value){
		root->right = removeNode(root->right, value);
	} else{
		if(root->left == NULL){
			printf("success\n");
			return root->right;
		} else if(root->right == NULL){
			printf("success\n");
			return root->left;
		}

		struct node* ptr  = malloc(sizeof(struct node));
		ptr = root->right;
		while(ptr->left != NULL){
			ptr = ptr->left;
		}

		root->data = ptr->data;
		root->right = removeNode(root->right, ptr->data);
		free(ptr);
	}

	return root;

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

void printInorder(struct node* root){
	if(root == NULL){
		return;
	}
	printInorder(root->left);
	printf("data: %d\n", root->data);
	printInorder(root->right);
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
		} else if(call == 'd'){
			root = removeNode(root, inputValue);
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
