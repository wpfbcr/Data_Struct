#include<iostream>
#include<assert.h>
#include<windows.h>
#include<time.h>
using namespace std;


//√∞≈›≈≈–Ú
//
//void BubbleSort(int *a, size_t size)
//{
//	for (size_t i = 0; i < size; i++)
//	{
//		for (size_t j = 9; j>i;j--)
//		{
//			if (a[j] < a[j - 1])
//			{
//				swap(a[j], a[j - 1]);
//			}
//		}
//	}
//}
//
//void Display(int *a, size_t size)
//{
//	assert(a);
//	for (size_t i = 0; i < size; i++)
//	{
//		cout << a[i] << endl;
//	}
//}
//void Test1()
//{
//	int arr[] = { 7, 8, 3, 4, 0, 1, 2, 9, 5, 6 };
//	BubbleSort(arr, 10);
//	Display(arr, 10);
//}
//int main()
//{
//	Test1();
//	return 0;
//}



// øÏÀŸ≈≈–Ú

//void Quicksort(int *a, int left, int right)
//{
//	if (left >= right)
//	{
//		return;
//	}
//	int start = left;
//	int end = right;
//	int temp = a[start];
//	while (start != end)
//	{
//		while (a[end] >= temp&&end > start)
//		{
//			end--;
//		}
//		while (a[start] <= temp&&start < end)
//		{
//			start++;
//		}
//		if (start < end)
//		{
//			swap(a[start], a[end]);
//		}
//	}
//	swap(a[left], a[start]);
//	Quicksort(a, left, start - 1);
//	Quicksort(a, start +1,right);
//}

int _Quicksort(int *a, int left, int right)
{
	assert(a);
	int prev=left-1;
	int cur = left;
	int end = right;
	int mid = 0;
	while (cur != end)
	{
		if (a[cur] < a[end]&&prev!=cur)
		{
			swap(a[++prev], a[cur]);
		}
		cur++;
	}
	swap(a[++prev], a[end]);
	mid = prev;
	return mid;
}

void Quicksort(int *a,int left,int right)
{
	assert(a);
	if (left< right)
	{
		int mid = _Quicksort(a, left, right);
		Quicksort(a, left, mid - 1);
		Quicksort(a, mid + 1, right);
	}
	else
	{
		return;
	}

}

void Display(int *a, size_t size)
{
	assert(a);
	for (size_t i = 0; i < size; i++)
	{
		cout << a[i] << endl;
	}
}
void Test1()
{
	srand(time);
	int arr[] = { 2, 6, 4, 9, 1, 0, 8, 3, 7, 5 };
	Quicksort(arr, 0, 9);  
	Display(arr, 10);
}



int main()
{
	Test1();
	return 0;
}
