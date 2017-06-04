/*********************************************************/
/*【程式名稱】: 8_h_sort.c                               */
/*【程式功能】: 堆積排序法－按「鍵值不遞增」排序         */
/*       輸入 : 一組未經排序的整數鍵值                   */
/*       輸出 : 每一回合排序之結果                       */
/*【資料結構】: 陣列結構                                 */
/*********************************************************/
/*【變數名稱及用途】                                     */
/*        d[] : 儲存待排序的鍵值以及排序過程中每一回合之 */
/*              結果                                     */
/*     Size,n : 陣列 d 的大小(元素個數)                  */
/*********************************************************/

#include <stdio.h>
#define Size 8

static void print_org_data(const int d[], int n);
static void print_array_data(const int d[], int low, int high);
static void swap(int *x, int *y);
void move_up(int d[], int n);
void move_down(int d[], int n);
int output_and_delete_root(int d[], int *n);
void heap_sort_descending(int d[], int low, int high);


/*------------------------------------------------*/
/*   列印排序前的鍵值資料(陣列 d 共有 n 個元素)   */
/*------------------------------------------------*/
static void print_org_data(const int d[], int n)
{
	int i;

	//  clrscr( );
	printf("陣列元素   d[0] [1] [2] [3] [4] [5] [6] [7] \n");
	printf("----------------------------------------------\n");
	printf("<排序前> ==> ");
	for (i = 0; i < n; i++){
		printf("%2d  ", d[i]);
	}
	printf("\n----------------------------------------------\n");
}

/*---------------------------------------------*/
/*   印出陣列 d 的內容(從 d[low] 到 d[high])   */
/*---------------------------------------------*/
static void print_array_data(const int d[], int low, int high)
{
	int i;

	for (i = low; i <= high; i++){
		printf("%2d  ", d[i]);
	}
	printf("\n");
}

/*---------------------------*/
/*   將 x,y 兩變數之值互換   */
/*---------------------------*/
static void swap(int *x, int *y)
{
	int z = *x;

	*x = *y;
	*y = z;
}

/*--------------------------------------------------*/
/*   從 d[n] 節點往樹根追蹤，將二元樹調整為堆積樹   */
/*--------------------------------------------------*/
void move_up(int d[], int n)
{
	int temp;

	temp = d[n];
	while (n / 2 > 0 && temp > d[n / 2]){
		d[n] = d[n / 2];
		n /= 2;
	}
	d[n] = temp;
}

/*------------------------------------------*/
/*   從樹根 d[1] 開始將二元樹調整為堆積樹   */
/*------------------------------------------*/
void move_down(int d[], int n)
{
	int i, left;
	int temp;

	temp = d[1];
	i = 1;
	while (i <= n / 2){
		left = 2 * i;
		if (left < n && d[left] < d[left + 1])
			left++;
		if (temp < d[left]){
			d[i] = d[left];
			i = left;
		}
		else break;
	}
	d[i] = temp;
}

/*------------------------------------------------------------*/
/* 輸出樹根之值，將最後一個節點之鍵值搬到樹根，再調整為堆積樹 */
/*------------------------------------------------------------*/
int output_and_delete_root(int d[], int *n)
{
	int root;

	root = d[1];
	swap(&d[1], &d[*n]);
	*n = *n - 1;
	move_down(d, *n);
	return root;
}

/*-------------------------------*/
/*   堆積排序法                  */
/*     1.陣列 d 共有 n 個元素    */
/*     2.按「鍵值不遞增」排序    */
/*-------------------------------*/
void heap_sort_descending(int d[], int low, int high)
{
	int i, j, n, y[Size + 1], step;

	step = 0;
	/*---------------------------------------------------*/
	/*   建造完整二元樹並儲存在陣列 y[] 之中             */
	/*   (為方便起見 y[0] 保留不用，以 y[1] 為樹根位置   */
	/*---------------------------------------------------*/
	n = 0;
	for (j = low; j <= high; j++){
		y[++n] = d[j];
		move_up(y, n);
	}
	/*--------------*/
	/*   堆積排序   */
	/*--------------*/
	for (i = high; i >= low; i--){
		d[i] = output_and_delete_root(y, &n);
		printf(" 第%d回合 ==> ", ++step);
		print_array_data(d, low, high);
		printf(" ==> 輸出 %d\n", d[i]);
	}
}

void heap_main_test(void)
{
	int d[Size] = { 83, 66, 55, 21, 88, 18, 88, 99 };

	print_org_data(d, Size); /* 列印排序前之鍵值資料 */

	/* 將陣列 d 裡的 d[0] 到 d[Size-1] 等鍵值按「鍵值不遞減」排序 */
	heap_sort_descending(d, 0, Size - 1);
    return;
}


static void my_swap(int *x, int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
	return;
}


static void my_move_up(int *h, int index)
{
	int p_i;
	p_i = index / 2;
	while (p_i > 0 && h[index] > h[p_i])
	{
		my_swap(&h[index], &h[p_i]);
		index = p_i;
		p_i = index / 2;
	}

}

static void my_move_down(int *heap, int index, int high)
{
	int L_child;
	int R_child;
	int is_swapped;
	int largest;

	L_child = index * 2;
	R_child = index * 2 + 1;
	largest = index;
	is_swapped = 0;
	do
	{
		is_swapped = 0;
		index = largest;
		L_child = index * 2;
		R_child = index * 2 + 1;

		if (heap[index] < heap[L_child] && L_child < high)
		{
			largest = L_child;
		}
		if (heap[largest] < heap[R_child] && R_child < high)
		{
			largest = R_child;
		}
		if (largest != index)
		{
			swap(&heap[index], &heap[largest]);
			is_swapped = 1;
		}
	} while (is_swapped);
}

static void my_delete_heapify(int *heap, int low, int high)
{
	my_swap(&heap[low], &heap[high]);
	my_move_down(heap, low, high - 1);

}
void my_heap_sort_descending(int d[], int low, int high)
{
	int i = 0;
	//build MAX HEAP
	int heap[9];
	int size;

	size = high - low + 1;
	for (i = 0; i < size; i++){
		heap[i + 1] = d[i];
		my_move_up(heap, i + 1);
	}
	printf("Max heap data \n");
	print_array_data(heap, 1, 8);
	//delete and repeat
	for (i = 0; i < size; i++){
		printf(" 第%d回合 ==> ", i);
		print_array_data(heap, 1, 8);
		my_delete_heapify(heap, 1, size - i);

	}
	printf("sorted heap data \n");
	print_array_data(heap, 1, 8);
}


void my_heap_main_test(void)
{
	int d[Size] = { 83, 66, 55, 21, 88, 18, 88, 99 };

	print_org_data(d, Size); /* 列印排序前之鍵值資料 */

	/* 將陣列 d 裡的 d[0] 到 d[Size-1] 等鍵值按「鍵值不遞減」排序 */
	my_heap_sort_descending(d, 0, Size - 1);
}
