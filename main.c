#include "main.h"
int test_data,query_data;
int main(int argc,char *argv[]){
	test_data = 0,query_data = 0;
	for(int i = 1; i < argc; i++){
		if(!strcmp(argv[i],"-d")){
			i++;
			if(!strcmp(argv[i],"1e4")) test_data = 10000;
			else if(!strcmp(argv[i],"1e5")) test_data = 100000;
			else if(!strcmp(argv[i],"1e6")) test_data = 1000000;
			build();
		}
		else if(!strcmp(argv[i],"-q")){
		        i++;
		        if(!strcmp(argv[i],"1e4")) query_data = 10000;
		        else if(!strcmp(argv[i],"1e5")) query_data = 100000;
		        else if(!strcmp(argv[i],"1e6")) query_data = 1000000;
		}
		else if(!strcmp(argv[i],"-arr"))arr_func();
		else if(!strcmp(argv[i],"-bs")) bs_func();
		else if(!strcmp(argv[i],"-bst")) bst_func();
		else if(!strcmp(argv[i],"-ll"))ll_func();
		else printf("Wrong Demand!\n");
		printf("\n");
	}
	return 0;
}
int test[1000000];
void build(){
	int i;
	srand(1);
	for(i = 0; i < test_data; i++){
		test[i] = rand();
	}
	return;
}

struct  timeval start;
struct  timeval end;
unsigned  long diff;

/**Array*/
void arr_func(){
	printf("arr:\n");
/*build part*/
	gettimeofday(&start, NULL);
	int arr[test_data];
	for(int i = 0; i < test_data; i++){
	        arr[i] = test[i];
	}
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("building time: %f sec\n", diff / 1000000.0);
/*query part*/
	gettimeofday(&start, NULL);
	for(int i = 0; i < query_data; i++){
		for(int j = 0; j < test_data; j++){
			if(test[i] == arr[j])break;
		}
	}
        gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("query time: %f sec\n", diff / 1000000.0);
}

/**Array with Binary Search*/
int compare(const void *a, const void *b){
	int c = *(int *)a;
	int d = *(int *)b;
	if(c < d)return -1;
	else if (c == d)return 0;
	else return 1;
}
int binary_Search(int arr[],int left,int right,int key){
	if(left <= right -1){
		if(arr[left] == key || arr[right] == key)return 1;
		return 0;
	}
	int mid = (right - left)/2;
	if(arr[mid] == key)return 1;
	if(arr[mid] > key) binary_Search(arr,left,mid-1,key);
	else binary_Search(arr,mid+1,right,key);
}
void bs_func(){
	int i;
	printf("bs:\n");
//build part
	gettimeofday(&start, NULL);
	int arr[test_data];
	for(i = 0; i < test_data; i++){
		arr[i] = test[i];
	}
	qsort((void *)arr,test_data,sizeof(arr[0]),compare);
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("building time: %f sec\n", diff / 1000000.0);
//query part
	gettimeofday(&start, NULL);
	for(i = 0; i < query_data; i++){
		binary_Search(arr,0,test_data,test[i]);
	}
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("query time: %f sec\n", diff / 1000000.0);
}

/**Binary Search Tree*/
trn *newNode(int number){
	trn *tmp;
	tmp = (trn *)malloc(sizeof(trn));
	tmp->num = number;
	tmp->left = tmp->right = NULL;
	return tmp;
}
trn *insert(trn *node,int number){
	if(node == NULL) return newNode(number);
	if(node->num > number) node->right = insert(node->right,number);
	else node->left = insert(node->left,number);
	return node;
}
void bst_func(){
	int i;
	printf("bst:\n");
/*build part*/
	gettimeofday(&start,NULL);
        trn *head = (trn *)malloc(sizeof(trn));
	head->num = test[0];
	head->left = head->right = NULL;
	trn *current = head;
	for(i = 1; i < test_data; i++){
		current = insert(current,test[i]);
	}
	gettimeofday(&end,NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("building time: %f sec\n", diff / 1000000.0);
/*query part*/
	gettimeofday(&start,NULL);
	for(i = 0; i < query_data; i++){
		current = head;
		while(current != NULL && current->num != test[i]){
			if(test[i] > current->num) current = current->right;
			else current = current->left;
		}
	}
        gettimeofday(&end,NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("query time: %f sec\n",diff/1000000.0);
}

/**Linked List*/
lis *newList(int data,lis *current){
	lis *following = (lis *)calloc(1,sizeof(lis));
	following->num = data;
	following->next = NULL;
	current->next = following;
	return following;
}
void ll_func(){
	printf("ll:\n");
/*build part*/
	gettimeofday(&start, NULL);
	lis *current;
	lis *head = (lis *)calloc(test_data,sizeof(lis));
	head->num = test[0];
	head->next = NULL;
	current = head;
	for(int i = 1; i < test_data; i++){
		current = newList(test[i],current);
	}
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("building time: %f sec\n", diff / 1000000.0);
/*query part*/
	gettimeofday(&start, NULL);
	for(int i = 0; i < query_data; i++){
		current = head;
		while(current != NULL){
			if(current->num == test[i])break;
			current = current->next;
		}
	}
        gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("query time: %f sec\n", diff / 1000000.0);
}

/**Hash*/
/*
void hash_init(hab *pHB, int capacity){
	pHB->array = (nod **)malloc(capacity*sizeof(nod *));
	for (int i = 0; i < capacity; i++) {
		pHB->array[i] = NULL;	// 空連結串列
	}
	pHB->size = capacity;
	pHB->cnt = 0;
}
void hash_expand(hab *pHB){
	if((pHB->cnt) < (pHB->size))return;
	int i = 0;
	nod *node;
	hab newbucket;  //新的Hash Table
	hash_init(&newbucket, pHB->size * 2);  //擴充成原2倍
	for (i = 0; i < pHB->size; i++){
		for (node = pHB->array[i]; node != NULL; node = node->next){
			hash_insert(&newbucket, node->key);
		}
	}
	hash_destroy(pHB); //刪掉舊的內容
	pHB->array = newbucket.array;
	pHB->size = newbucket.size;
}
int hash_insert(hab *pHB, int input){
	hash_expand(pHB);  //檢查是否有空間
	if(hash_search(pHB, input) != NULL)return -1; //已存在

	int index = input % pHB->size; //這筆資料的value
	nod *first = pHB->array[index];
	nod *node = (nod *)malloc(sizeof(nod));
	node->key = input;
	node->next = NULL;
	first = node->next;
	pHB->array[index] = node;
	pHB->cnt++;
	return 0;
}
nod *hash_search(hab *pHB,int input){
	int index = input % pHB->size;
	nod *cur = pHB->array[index];
	while(cur != NULL){
		if (cur->key == input) return cur;
		cur = cur->next;
	}
	return NULL;
}
void hash_destroy(hab *pHB){
	int i ;
	for (i = 0; i < pHB->size; i++){
	        nod *follow,*cur;
		for (cur = pHB->array[i]; cur != NULL; cur = follow){
		        follow = cur->next;
		        free(cur);
		}
	}
	free(pHB->array);
}
void hash_func(int test_data,int query_data){
	printf("hash:\n");
//build part
	gettimeofday(&start, NULL);
	hab *pHB;
	for(int i = 1; i < test_data; i++){
		hash_insert(pHB,test[i]);
	}
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("building time: %f sec\n", diff / 1000000.0);
//query part
	gettimeofday(&start, NULL);
	for(int i = 0; i < query_data; i++){
		hash_search(pHB,test[i]);
	}
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("query time: %f sec\n", diff / 1000000.0);
}*/
