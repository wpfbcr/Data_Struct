#include<iostream>
using namespace std;

int _flag(int *a, size_t size)
{
	int num = 1;
	int max = 1;
	for (size_t i = 0; i < size; i++)
	{
		while ((a[i]/10)>=max)
		{
			num++;
			max *= 10;;
		}
	}
	return num;
}

void Radixsoft(int *a,size_t size)
{
	int num[10];
	int pos[10];
	int newa[10];
	int flag = _flag(a, size);
	int sum = 1;
	while(flag>0)
	{
		memset(num, 0, sizeof(int)* 10);
		memset(pos, 0, sizeof(int)* 10);
		for (size_t i = 0; i < 10; i++)
		{
			num[(a[i] / sum) % 10]++;
		}
		for (size_t j = 1; j < 10; j++)
		{
			pos[j] = num[j - 1] + pos[j - 1];
		}
		for (size_t i = 0; i < size; i++)
		{
			int number = (a[i] / sum)%10;
			newa[pos[number]++] = a[i];
		}
		flag--;
		sum *= 10;
		memcpy(a, newa, sizeof(int)*size);
	}
}

void Test()
{
	int arr[] = {234,56,24,7,65,89,56,2,1,98};
	Radixsoft(arr, 10);
}

int main()
{
	Test();
	return 0;
}