#include<iostream>
#include<assert.h>
using namespace std;


void InsertSoft(int *a,size_t size)
{
	assert(a);
	for (size_t i = 1; i < size; i++)
	{
		int tmp = a[i];
		size_t num = i;
		while (num)
		{
			--num;
			if (tmp > a[num])
			{
				break;
			}
			else if (tmp < a[num])
			{
				swap(a[num], a[num + 1]);
			}

		}
		
	}

}


void Shellsoft(int *a, size_t size)
{
	assert(a);
	size_t gap = size / 3 + 1;
	while (gap >= 1)
	{
		for (int i = gap; i < size; i++)
		{
			for (int j = i - gap; j>=0; j-=gap)
			{
				if (a[j]>a[j+gap])
				{
					swap(a[j], a[j+gap]);
				}
			}
		}

		if (gap == 1)
		{
			break;
		}
		gap = gap / 3 + 1;
	}
}
void shellsort3(int a[], int n)
{
	int i, j, gap;

	for (gap = n / 2; gap > 0; gap /= 2)
	for (i = gap; i < n; i++)
	for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
		swap(a[j], a[j + gap]);
}
void Display(int *a, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		cout << a[i];
	}
	cout << endl;
}

void Test1()
{
	int array[] = { 2, 5, 3, 8, 6, 1, 9, 0, 4, 7 };
	InsertSoft(array, 10);
	Display(array, 10);
}
void Test2()
{
	int array[] = { 2,5, 3, 8, 6, 1, 9, 0, 4, 7 };
	Shellsoft(array, 10);
	Display(array, 10);
}

void Test3()
{
	int array[] = { 2, 5, 3, 8, 6, 1, 9, 0, 4, 7 };
	shellsort3(array, 10);
	Display(array, 10);
}


int main()
{
	//Test1();
	Test2();
	//Test3();
	return 0;
}