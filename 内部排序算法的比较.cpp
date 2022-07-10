#include <cstdio>         
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <time.h>  

typedef struct {
	int* rcd;  // rcd指向要记录的数组
	int length;  // 当前长度,0为闲置位
}SqList;

void TestSort(void (Sort)(SqList&));
void test();

bool InitList(SqList& L, int rcd[], int length);  // 初始化排序的记录顺序表
void BubbleSort(SqList& L);  // 冒泡排序
void InsertSort(SqList& L);  // 直接插入排序
void SelectSort(SqList& L);  // 简单选择排序
void QuickSort(SqList& L, int low, int high);  // 快速排序
void ShellSort(SqList& L, int d[], int t);  // 希尔排序
void HeapSort(SqList& L);  // 堆排序

void FormattingPrint(char* str);  // 格式化输出字符串
void PrintList(SqList& L);  // 打印顺序表中的值
int* getRandomArr(int length);  // 生成乱序数组

int* getArr(int length);

int compare_number;  // 比较次数
int move_number;  // 移动次数
const int length = 100;
SqList L;

//int* rcd = getRandomArr(length + 1);
int* rcd = getArr(length + 1);

int* getArr(int length)
{
	int* rcd = (int*)malloc(sizeof(int) * length);
	int tmp = 100;
	for (int i = 1; i <= length; i ++ )
		rcd[i] = tmp -- ;
	
	srand((unsigned)time(NULL));
	for (int i = 1; i <= 85; i++)  // 乱序程度 1:30个乱序 2:55个乱序 3:85个乱序
	{
		rcd[i] = rand()%length;
	}
	return rcd;
}

int main( ) {
	test();
	
	return 0;
}


void TestSort(void (Sort)(SqList&)) 
{
	InitList(L, rcd, length);
	Sort(L);
	PrintList(L);
	
	printf("\t移动次数m:%d\n", move_number);
	printf("\t比较次数c:%d\n\n", compare_number);
 }
 
 
 void test() 
 {
 	printf("\n");
 	FormattingPrint((char*)"生成随机数的内部排序");
 	printf("\n");
 	
 	InitList(L, rcd, length);
 	PrintList(L);
 	printf("\n\n");
 	
 	TestSort(BubbleSort);  // 冒泡排序    
 	TestSort(InsertSort);  // 直接插入排序
 	TestSort(SelectSort);  // 简单选择排序
 	
 	// 快速排序
 	InitList(L, rcd, length);  
 	FormattingPrint((char*)"QuickSort");
 	QuickSort(L, 0, L.length);
 	PrintList(L);
 	printf("\t移动次数m:%d\n", move_number);
 	printf("\t比较次数c:%d\n\n", compare_number);
 	
 
 	// 希尔排序
 	const int d_length = 7;
 	int d[d_length] = {46, 20, 9, 4, 1};
 	InitList(L, rcd, length);
 	ShellSort(L, d, d_length);
 	PrintList(L);
 	printf("\t移动次数m:%d\n", move_number);
 	printf("\t比较次数c:%d\n\n", compare_number);
 	
 	// 堆排序
 	TestSort(HeapSort);
 }
 
 
 // 初始化排序的记录顺序表
 bool InitList(SqList& L, int rcd[], int length) 
 {
 	if (length <= 0)
 		return false;
 	L.rcd = (int*)malloc(((unsigned long long)length + 1) * sizeof(int));
 	
 	if (L.rcd == NULL)
 	{
 		return false;
 	}
 	
 	for (int i = 1; i <= length; i ++ )
 	{
 		L.rcd[i] = rcd[i];
 		L.length = length;
 	}
 	
 	return true;
 }
 
 
 // 交换函数
 void swap(int* a, int* b) 
 {
 	int tmp = 0;
 	tmp = *a;
 	*a = *b;
 	*b = tmp;
 }
 
 
 // 冒泡排序
 void  BubbleSort(SqList& L) {
 	FormattingPrint((char*)__func__);  // __func__ 返回函数的名字
 	compare_number = 0;  // 比较次数 
 	move_number = 0;  // 移动次数 
 	int flag = 1;
 	for (int i = 1; i < L.length && flag; i ++)
 	{
 		flag = 0;
 		for (int j = L.length; j > i; j--)
 		{
 			if (L.rcd [j] < L.rcd [j - 1])
 			{
 				swap( &L.rcd[j], &L.rcd [j-1]);
 				move_number += 2;
 				flag = 1; //如果没有交换说明已经排好序了
 			}
 			compare_number ++ ;
 		}
 	}
 
 }
 
 
 // 直接插入排序
 void InsertSort(SqList& L)
 {
 	FormattingPrint((char*)__func__);
 	compare_number = 0;  // 比较次数 
 	move_number = 0;  // 移动次数 
 	for (int i = 1; i < L.length; ++i) 
 	{
 		if (L.rcd[i+1] < L.rcd[i]) 
 		{ 
 			L.rcd [0] = L.rcd [i + 1];
 			move_number ++ ;
 			int j = i + 1;
 			do {
 				j -- ;
 				L.rcd [j + 1] = L.rcd [j];
 				move_number ++ ;
 			} while (L.rcd[0] < L.rcd[j-1]);
 			L.rcd [j] = L.rcd [0];
 			move_number ++ ;
 		}
 		compare_number ++ ;
 	}
 }
 
 
 // 简单选择排序
 void SelectSort(SqList& L) 
 {
 	FormattingPrint((char*)__func__);
 	compare_number = 0;  // 比较次数 
 	move_number = 0;  // 移动次数 
 	for (int i = 1; i <= L.length; i ++ ) 
	{
 		int min = i;
 		for (int j = i + 1; j <= L.length; j ++ ) 
		{
 			if (L.rcd[min] > L.rcd[j])  // 找到最小值的下标
 			{
 				min = j;
 				move_number ++ ;
 			}
 			compare_number ++ ;
 		}
 		if (min != i)  // 交换最小数L.rcd[min]和第i位数的位置
 		{
 			swap(&L.rcd[min], &L.rcd[i]);
 			move_number += 2;
 		}
 	}
 
 }
 
 
 //用来递归操作的快速排序
 int Partition(SqList& L, int low, int high) 
 {
 	L.rcd[0] = L.rcd[low];
 	while (low < high) 
 	{
 		while (low < high && L.rcd[0] <= L.rcd[high]) high -- ;
 		compare_number ++ ;
 		L.rcd[low] = L.rcd[high];
 		move_number ++ ;
 		while (low < high && L.rcd[low] <= L.rcd[0]) low ++ ;
 		compare_number ++ ;
 		L.rcd[high] = L.rcd[low];
 		move_number ++ ;
 	}
 	compare_number ++ ;
 	L.rcd[low] = L.rcd[0];
 	move_number ++ ;
 	return low;
 } 
 
 
 // 快速排序
 void QuickSort(SqList& L, int low, int high) 
 {
 	int pivot;
 	if (low < high) {
 		pivot = Partition(L, low, high);
 		QuickSort(L, low, pivot - 1);
 		QuickSort(L, pivot + 1, high);
 	}
 } 
 
 
 //一趟希尔排序
 void ShellInsert(SqList& L, int d) 
 {
 	//对顺序表L作一趟希尔插入排序。
 	for (int i = d + 1; i <= L.length; i ++ )
 		if (L.rcd[i] < L.rcd[i - d])  // 需将L.rcd[i]插入有序增量子表
 		{
 			L.rcd[0] = L.rcd[i];  // 暂存在L.rcd[0]
 			move_number ++ ;
 			int j;
 			for (j = i - d; j > 0 && (L.rcd[0] < L.rcd[j]); j -= d)
 			{
 				L.rcd[j + d] = L.rcd[j];   // 记录后移，查找插入位置
 				move_number ++ ;
 				compare_number ++ ;
 			}
 			L.rcd[j + d] = L.rcd[0];  // 插入
 			move_number ++ ;
 			compare_number ++ ;
 		}
 	compare_number ++ ;
 }
 
 
 // 希尔排序
 void ShellSort(SqList& L, int dlta[], int t) 
 {
 	// 按增量序列dlta[0..t-1]对顺序表L作希尔排序。
 	FormattingPrint((char*)__func__);
 	compare_number = 0;  // 比较次数 
 	move_number = 0;  // 移动次数 
 	for (int k = 0; k < t; k ++ )
 		ShellInsert(L, dlta[k]);
 }
 
 
 // 大顶堆调整
 void MaxHeapify(int rcd[], int start, int end, int& compare_number, int& move_number) 
 {
 	// 建立父节点和子节点指针
 	int dad = start;
 	int son = dad * 2;
 	while (son <= end)  // 子节点在指定范围内再进行比较
 	{ 
 		if (son + 1 <= end && rcd[son] < rcd[son + 1])  // 比较两个子节点，选择大的
 		{
			son ++ ;
			compare_number ++ ; 	
		}
		compare_number ++ ;
 		if (rcd[dad] > rcd[son])   
 			return;
 		else  
 		{ 
 			swap(&rcd[dad], &rcd[son]);
 			move_number += 2;
 			dad = son;
 			son = dad * 2;
 		}
 	}
 }
 
 
 // 堆排序
 void HeapSort(SqList& L) {
 	FormattingPrint((char*)__func__);
 	compare_number = 0;  // 比较次数 
	move_number = 0;  // 移动次数 
 	int len = L.length;
 	for (int i = len / 2; i >= 1; i--)  // 初始化，i从最后一个父节点开始调整
 		MaxHeapify(L.rcd, i, len, compare_number, move_number);
 	for (int i = len; i > 0; i--)  // 将第一个已经排好的前一个进行交换，再进行调整
 	{
 		swap(&L.rcd[1], &L.rcd[i]);
 		MaxHeapify(L.rcd, 1, i - 1, compare_number, move_number);
 	}
 }
 

//格式化输出字符串
void FormattingPrint(char* str) {
	printf("=====");
	printf("%s", str);
	printf("=====");
	printf("\n");
}


// 打印顺序表中的值
void PrintList(SqList& L) 
{
	for (int i = 1; i <= L.length; i++)
	{
		printf("%d ", L.rcd[i]);
	}
	printf("\n");
}


//随机数构成的顺序表中的存储空间内容
int* getRandomArr(int length) 
{
	if (length <= 0)
		return 0;
	int* rcd = (int*)malloc(((unsigned long long)length + 1) * sizeof(int));
	if (rcd == NULL)
		return NULL;
	rcd[0] = 0;
	srand((unsigned)time(NULL));
	for (int i = 1; i <= length; i++)
	{
		rcd[i] = rand()%length;
	}
	return rcd;
}
