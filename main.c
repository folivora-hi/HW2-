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
	int *arr = (int *)malloc(test_data*sizeof(int));
	for(int i = 0; i < test_data; i++){
	        arr[i] = test[i];
	}
	gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("building time: %f sec\n", diff / 1000000.0);
	/*query part*/
	gettimeofday(&start, NULL);
	for(int i = 0; i < query_data; i++){
		for(int j = 0; j < test_data; i++){
			if(test[i] == arr[j])break;
		}
	}
        gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("query time: %f sec\n", diff / 1000000.0);
}

/**Array with Binary Search*/
void traversal(int data,int len,int *arr){
	int *ptr = arr;
	if(len == 0){
		arr[0] = test[0];
		return;
	}
	int pos = 0;
	while(*ptr && pos < len){
	        if(ptr[pos] > data)pos = pos*2+2;
	        else pos = pos*2+1;
	}
	arr[pos] = data;
	return;
}
void bs_func(){
	int i,len,pos;
	printf("bs:\n");
	/*build part*/
	gettimeofday(&start, NULL);
        int *arr = (int *)calloc(test_data,sizeof(int));
	for(i = 0; i < test_data; i++){
		traversal(test[i],i,arr);
	}
        gettimeofday(&end, NULL);
	diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("building time: %f sec\n", diff / 1000000.0);
	/*query part*/
	gettimeofday(&start, NULL);
        for(i = 0; i < query_data; i++){
		pos = 0;
		while(test[i] != arr[pos] && pos < test_data){
			if(arr[pos] > test[i])pos = pos*2+2;
			else pos = pos*2+1;
		}
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

