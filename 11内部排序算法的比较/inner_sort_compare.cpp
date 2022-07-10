#include <cstdio>         
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <time.h>  

typedef struct {
	int* rcd;  // rcdָ��Ҫ��¼������
	int length;  // ��ǰ����,0Ϊ����λ
}SqList;

void TestSort(void (Sort)(SqList&));
void test();

bool InitList(SqList& L, int rcd[], int length);  // ��ʼ������ļ�¼˳���
void BubbleSort(SqList& L);  // ð������
void InsertSort(SqList& L);  // ֱ�Ӳ�������
void SelectSort(SqList& L);  // ��ѡ������
void QuickSort(SqList& L, int low, int high);  // ��������
void ShellSort(SqList& L, int d[], int t);  // ϣ������
void HeapSort(SqList& L);  // ������

void FormattingPrint(char* str);  // ��ʽ������ַ���
void PrintList(SqList& L);  // ��ӡ˳����е�ֵ
int* getRandomArr(int length);  // ������������

int* getArr(int length);

int compare_number;  // �Ƚϴ���
int move_number;  // �ƶ�����
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
	for (int i = 1; i <= 85; i++)  // ����̶� 1:30������ 2:55������ 3:85������
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
	
	printf("\t�ƶ�����m:%d\n", move_number);
	printf("\t�Ƚϴ���c:%d\n\n", compare_number);
 }
 
 
 void test() 
 {
 	printf("\n");
 	FormattingPrint((char*)"������������ڲ�����");
 	printf("\n");
 	
 	InitList(L, rcd, length);
 	PrintList(L);
 	printf("\n\n");
 	
 	TestSort(BubbleSort);  // ð������    
 	TestSort(InsertSort);  // ֱ�Ӳ�������
 	TestSort(SelectSort);  // ��ѡ������
 	
 	// ��������
 	InitList(L, rcd, length);  
 	FormattingPrint((char*)"QuickSort");
 	QuickSort(L, 0, L.length);
 	PrintList(L);
 	printf("\t�ƶ�����m:%d\n", move_number);
 	printf("\t�Ƚϴ���c:%d\n\n", compare_number);
 	
 
 	// ϣ������
 	const int d_length = 7;
 	int d[d_length] = {46, 20, 9, 4, 1};
 	InitList(L, rcd, length);
 	ShellSort(L, d, d_length);
 	PrintList(L);
 	printf("\t�ƶ�����m:%d\n", move_number);
 	printf("\t�Ƚϴ���c:%d\n\n", compare_number);
 	
 	// ������
 	TestSort(HeapSort);
 }
 
 
 // ��ʼ������ļ�¼˳���
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
 
 
 // ��������
 void swap(int* a, int* b) 
 {
 	int tmp = 0;
 	tmp = *a;
 	*a = *b;
 	*b = tmp;
 }
 
 
 // ð������
 void  BubbleSort(SqList& L) {
 	FormattingPrint((char*)__func__);  // __func__ ���غ���������
 	compare_number = 0;  // �Ƚϴ��� 
 	move_number = 0;  // �ƶ����� 
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
 				flag = 1; //���û�н���˵���Ѿ��ź�����
 			}
 			compare_number ++ ;
 		}
 	}
 
 }
 
 
 // ֱ�Ӳ�������
 void InsertSort(SqList& L)
 {
 	FormattingPrint((char*)__func__);
 	compare_number = 0;  // �Ƚϴ��� 
 	move_number = 0;  // �ƶ����� 
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
 
 
 // ��ѡ������
 void SelectSort(SqList& L) 
 {
 	FormattingPrint((char*)__func__);
 	compare_number = 0;  // �Ƚϴ��� 
 	move_number = 0;  // �ƶ����� 
 	for (int i = 1; i <= L.length; i ++ ) 
	{
 		int min = i;
 		for (int j = i + 1; j <= L.length; j ++ ) 
		{
 			if (L.rcd[min] > L.rcd[j])  // �ҵ���Сֵ���±�
 			{
 				min = j;
 				move_number ++ ;
 			}
 			compare_number ++ ;
 		}
 		if (min != i)  // ������С��L.rcd[min]�͵�iλ����λ��
 		{
 			swap(&L.rcd[min], &L.rcd[i]);
 			move_number += 2;
 		}
 	}
 
 }
 
 
 //�����ݹ�����Ŀ�������
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
 
 
 // ��������
 void QuickSort(SqList& L, int low, int high) 
 {
 	int pivot;
 	if (low < high) {
 		pivot = Partition(L, low, high);
 		QuickSort(L, low, pivot - 1);
 		QuickSort(L, pivot + 1, high);
 	}
 } 
 
 
 //һ��ϣ������
 void ShellInsert(SqList& L, int d) 
 {
 	//��˳���L��һ��ϣ����������
 	for (int i = d + 1; i <= L.length; i ++ )
 		if (L.rcd[i] < L.rcd[i - d])  // �轫L.rcd[i]�������������ӱ�
 		{
 			L.rcd[0] = L.rcd[i];  // �ݴ���L.rcd[0]
 			move_number ++ ;
 			int j;
 			for (j = i - d; j > 0 && (L.rcd[0] < L.rcd[j]); j -= d)
 			{
 				L.rcd[j + d] = L.rcd[j];   // ��¼���ƣ����Ҳ���λ��
 				move_number ++ ;
 				compare_number ++ ;
 			}
 			L.rcd[j + d] = L.rcd[0];  // ����
 			move_number ++ ;
 			compare_number ++ ;
 		}
 	compare_number ++ ;
 }
 
 
 // ϣ������
 void ShellSort(SqList& L, int dlta[], int t) 
 {
 	// ����������dlta[0..t-1]��˳���L��ϣ������
 	FormattingPrint((char*)__func__);
 	compare_number = 0;  // �Ƚϴ��� 
 	move_number = 0;  // �ƶ����� 
 	for (int k = 0; k < t; k ++ )
 		ShellInsert(L, dlta[k]);
 }
 
 
 // �󶥶ѵ���
 void MaxHeapify(int rcd[], int start, int end, int& compare_number, int& move_number) 
 {
 	// �������ڵ���ӽڵ�ָ��
 	int dad = start;
 	int son = dad * 2;
 	while (son <= end)  // �ӽڵ���ָ����Χ���ٽ��бȽ�
 	{ 
 		if (son + 1 <= end && rcd[son] < rcd[son + 1])  // �Ƚ������ӽڵ㣬ѡ����
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
 
 
 // ������
 void HeapSort(SqList& L) {
 	FormattingPrint((char*)__func__);
 	compare_number = 0;  // �Ƚϴ��� 
	move_number = 0;  // �ƶ����� 
 	int len = L.length;
 	for (int i = len / 2; i >= 1; i--)  // ��ʼ����i�����һ�����ڵ㿪ʼ����
 		MaxHeapify(L.rcd, i, len, compare_number, move_number);
 	for (int i = len; i > 0; i--)  // ����һ���Ѿ��źõ�ǰһ�����н������ٽ��е���
 	{
 		swap(&L.rcd[1], &L.rcd[i]);
 		MaxHeapify(L.rcd, 1, i - 1, compare_number, move_number);
 	}
 }
 

//��ʽ������ַ���
void FormattingPrint(char* str) {
	printf("=====");
	printf("%s", str);
	printf("=====");
	printf("\n");
}


// ��ӡ˳����е�ֵ
void PrintList(SqList& L) 
{
	for (int i = 1; i <= L.length; i++)
	{
		printf("%d ", L.rcd[i]);
	}
	printf("\n");
}


//��������ɵ�˳����еĴ洢�ռ�����
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
