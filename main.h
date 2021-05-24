#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

typedef struct treeNod trn;
struct treeNod{
	int num;
	trn *left,*right;
};


typedef struct list lis;
struct list{
	int num;
	lis *next;
};


void build();

void arr_func();

void traversal(int data,int len,int *arr);
void bs_func();

trn *newNode(int number);
trn *insert(trn *node,int number);
void bst_func();

lis *newList(int data,lis *current);
void ll_func();


#endif
