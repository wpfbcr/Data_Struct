#include<iostream>
using namespace std;


void Merge(int *sou,int *dst,size_t start,size_t mid,size_t end)
{
	size_t i  =start;
	size_t num = start;
	size_t j = mid + 1;
	while (i <= mid&&j <= end)
	{
		if (sou[i] < sou[j])
		{
			dst[num] = sou[i];
			i++;
			num++;
		}
		else
		{
			dst[num] = sou[j];
			j++;
			num++;
		}
	
	}
	while (i <= mid)
	{
		dst[num++] = sou[i++];
	}
	while (j <= end)
	{
		dst[num++] = sou[j++];
	}
	for (size_t i = start; i <= end; i++)
	{
		sou[i] = dst[i];
	}
}

void Display(int *a, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << a[i] << endl;
	}
}

void Mergesoft(int *a,int *b,size_t start,size_t end)
{
	if (start < end)
	{
		size_t mid = (start + end) / 2;
		Mergesoft(a, b, start, mid);
		Mergesoft(a, b, mid + 1, end);
		Merge(a, b, start, mid, end);
	}
}


void Test()
{
	int arr[] = { 1,2,3,6,5};
	int dst[5];
	Mergesoft(arr, dst, 0, 4);
	Display(arr, 5);

}
int main()
{
	Test();
	return 0;
}


//#include <stdlib.h>
//#include <stdio.h>
//
//void Merge(int sourceArr[], int tempArr[], int startIndex, int midIndex, int endIndex)
//{
//	int i = startIndex, j = midIndex + 1, k = startIndex;
//	while (i != midIndex + 1 && j != endIndex + 1)
//	{
//		if (sourceArr[i] >= sourceArr[j])
//			tempArr[k++] = sourceArr[j++];
//		else
//			tempArr[k++] = sourceArr[i++];
//	}
//	while (i != midIndex + 1)
//		tempArr[k++] = sourceArr[i++];
//	while (j != endIndex + 1)
//		tempArr[k++] = sourceArr[j++];
//	for (i = startIndex; i <= endIndex; i++)
//		sourceArr[i] = tempArr[i];
//}
//
//内部使用递归
//void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
//{
//	int midIndex;
//	if (startIndex < endIndex)
//	{
//		midIndex = (startIndex + endIndex) / 2;
//		MergeSort(sourceArr, tempArr, startIndex, midIndex);
//		MergeSort(sourceArr, tempArr, midIndex + 1, endIndex);
//		Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
//	}
//}
//
//int main(int argc, char * argv[])
//{
//	int a[8] = { 50, 10, 20, 30, 70, 40, 80, 60 };
//	int i, b[8];
//	MergeSort(a, b, 0, 7);
//	for (i = 0; i<8; i++)
//		printf("%d ", a[i]);
//	printf("\n");
//	return 0;
//}