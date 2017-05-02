#include <stdio.h>
#include <stdlib.h>

unsigned int *buffer;

static void print_all(unsigned int A[], size_t n){
	printf("[0] [1] [2] [3] [4] [5]\n");
	for (int i = 0; i < n; i++){
		printf("%2d  ", A[i]);
	}
	printf("\n");
}

void merge(unsigned int A[], unsigned int B[], int p, int q, int mid)
{
	int i = p;
	int i_end = mid;
	int j =  mid +1;
	int j_end = q;
	int len = q - p + 1;
	int k = p;
	static int count = 1;
	for (k = p; k <= q; k++)
	{
		if (i == mid + 1 || j == q + 1)
		{
			break;
		}
		if (A[i] < A[j]){
			buffer[k] = A[i++];
		}
		else
		{
			buffer[k] = A[j++];
		}

	}
	if (k != (q+1))
	{
		for (; k <= q; k++){
			if (i == mid + 1){
				buffer[k] = A[j++];
			}
			else{
				buffer[k] = A[i++];
			}
		}
	}

	for (i = p; i <= q; i++)
		A[i] = buffer[i];

	printf("²Ä%d¦^¦X, %d,%d\n", count, p,q);
	print_all(A, 6);
	//print_all(buffer, 6);
	count++;
}

void mergesort(unsigned int A[], int p, int q)
{
	unsigned int mid = (p + q) / 2;

	if (buffer == NULL)
		buffer = (unsigned int *)malloc((q - p + 1) << 2);

	if (p < q){
		mergesort(A, p, mid);
		mergesort(A, mid+1, q);
		merge(A, buffer, p, q, mid);
	}
}


void mergesort_main(void)
{
	unsigned int A[] = { 8, 5, 6, 89, 35, 17 };
	unsigned int len = sizeof(A) / sizeof(A[0]);
	print_all(A, len);
	mergesort(A, 0, len - 1);
	print_all(A, len);
	return;
}



