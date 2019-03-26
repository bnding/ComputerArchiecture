#include <stdio.h>
#include <stdlib.h>
void swap(int *, int *);

void swap(int *a, int *b){

	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

//pointer is an address
int main(int argc, char** argv){
	
//	int a=42;
//	int * q; //points to nothing. this is the start of the linked list. type integer pointer
//	q = &a; //q is pointing to a

//	*q = 54;
//	a = 64;
//
	int p, q;
	printf("enter the value of p\n");
	scanf("%d", &p);
	printf("enter the value of q\n");
	scanf("%d", &q);

	printf("[before swap] a = %d, b=%d\n", p, q);
	swap(&p,&q);
	printf("[after swap] a = %d, b = %d\n", p, q);// not swapping here. out of scope. need a pointer

//	printf("a is %d\a\n", a);
//	printf("value at the location pointed by q is %d\n", *q);
	return 0;
}
