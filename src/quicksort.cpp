#include <stdio.h>
#include <stdlib.h>


static void swap(unsigned int *x, unsigned int *y){
	unsigned int temp = *x;
	*x = *y;
	*y = temp;
}

unsigned int partition(unsigned int A[], int p, int q)
{
	int i;
	int j;
	int pivot;

	i = p;
	pivot = p;

	for (j = p; j <= q; j++)
	{
		if (A[j] < A[pivot]){
			i = i + 1;
			swap(&A[j], &A[i]);
		}
	}
	swap(&A[pivot], &A[i]);
	return i;
}

void print_all(unsigned int A[], size_t n){
	printf("[0] [1] [2] [3] [4] [5]\n");
	for (int i = 0; i < n;  i++){
		printf("%2d  ",A[i]);
	}
	printf("\n");
}

void quicksort(unsigned int A[], int p, int q)
{
	int r;
	if (p < q)
	{
		r = partition(A, p, q);
		quicksort(A, p, r-1);
		quicksort(A, r + 1, q);
	}
}

void quicksort_main(void)
{
	unsigned int A[] = { 8, 5, 6, 1, 10, 20 };
	printf("Unsorted array\n");
	print_all(A, sizeof(A)/sizeof(A[0]));
	quicksort(A,0,5);
	printf("sorted array\n");
	print_all(A, sizeof(A) / sizeof(A[0]));
	return;
}

