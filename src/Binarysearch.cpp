#include <stdlib.h>
#include <stdio.h>

int binary_search(unsigned int A[], int p, int q, unsigned int key)
{
	int mid;

	if (p < q){
		mid = (p + q) / 2;
		if (A[mid] == key){
			printf("[binray search] got %d, in %d \n", key, mid);
			return mid;
		}
			
		else if (A[mid] < key){
			binary_search(A, mid+1,q,key);
		}
		else
		{
			binary_search(A, p, mid-1,key);
		}
	}
	printf("[binary search] can't find %d \n", key);
    return 0;
}

void binary_search_test(void)
{
	unsigned int A[] = {1,5,7,10,21};
	printf("[binray search] search key %d\n",7);
	binary_search(A,0,4,7);
}
