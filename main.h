#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
void build();

void arr_func();


int compare(const void *a, const void *b);
int binary_Search(int arr[],int left,int right,int key);
void bs_func();


typedef struct treeNod trn;
struct treeNod{
	int num;
	trn *left,*right;
};
trn *newNode(int number);
trn *insert(trn *node,int number);
void bst_func();


typedef struct list lis;
struct list{
	int num;
	lis *next;
};
lis *newList(int data,lis *current);
void ll_func();

#endif
