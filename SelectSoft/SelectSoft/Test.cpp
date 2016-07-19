#include<iostream>
#include<assert.h>

using namespace std;

//
//÷±Ω”—°‘Ò≈≈–Ú
void Selectsoft(int *a,size_t size)
{
  assert(a);
  for (size_t i = 0; i < size; i++)
  {
	  int min = i;
	  for (size_t j = i + 1; j < size; j++)
	  {
		  if (a[j] < a[min])
		  {
			  swap(a[min], a[j]);
		  }
	  }
  }
}

void Display(int *a,size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << a[i];
	}
	cout << endl;
}
void Test1()
{
	int array[] = {41,9,5,6,8,3,2,7,10,1};
	Selectsoft(array, 10);
	Display(array,10);
}
int main()
{
	Test1();
	return 0;
}



//∂—≈≈–Ú

//#include<iostream>
//#include<assert.h>
//
//using namespace std;
//
//
//void heapDownsoft(int *a, size_t parent,size_t size)
//{
//	int child = parent * 2 + 1;
//	while ((child+1)<size)
//	{
//		if (a[child] < a[child + 1])
//		{
//			child++;
//		}
//		if (a[child] < a[parent])
//		{
//			break;
//		}
//		if ((child<size)&&a[child]>a[parent])
//		{
//			swap(a[child], a[parent]);
//			parent = child;
//			child = parent * 2 + 1;
//		}
//	}
//}
//void Heapsoft(int *a, size_t size)
//{
//	size_t parent = (size - 2) / 2;
//	for (int i = parent; i >=0; --i)
//	{
//		heapDownsoft(a,i,size);
//	}
//	int j = size;
//	while (j-1)
//	{ 
//		--j;
//		swap(a[j], a[0]);
//		heapDownsoft(a, 0, j);		
//	}
//}
//void Display(int *a,size_t size)
//{
//	for (size_t i = 0; i < size; i++)
//	{
//		cout << a[i] << endl;
//	}
//	cout << endl;
////}
//int main()
//{
//	int array[] = {20,12,35,15,10,80,30,17,2,1};
//	Heapsoft(array, 10);
//	Display(array, 10);
//	return 0;
//}