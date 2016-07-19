#include<iostream>
#include<vector>
#include<time.h>
using namespace std;
#define N 100
#define K 10

template<class T>
struct Less
{
	bool operator()(T i, T j)
	{
		return i < j;
	}
};
template<class T>
struct Greater
{
	bool operator()(T i, T j)
	{
		return i>j;
	}
};

template<class T,class com=Less<T>>
class Heap
{
public:
	Heap()
		:_size(0)
	{}
	Heap(T* heap, size_t size)
		:_size(size)
	{
		for (size_t i = 0; i < size;i++)
		{
			_heap.push_back(heap[i]);
		}
		for (int i = (size - 2) / 2; i >= 0; i--)
		{
			Heapdown(i);
		}
	}
	void Push(T x)
	{
		_heap.push_back(x);
		_size += 1;
		Heapout(_heap);
	}
	void Pop()
	{
		swap(_heap[_size - 1], _heap[0]);
		_heap.pop_back();
		_size--;
		//Heapdown(_heap, 0);
	}
	int Size()
	{
		return _size;
	}
	T top()
	{
		return _heap[0];
	}
	bool Empty()
	{
		if (_size > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Display()
	{
		
		for (size_t i = 0; i < _size; i++)
		{
			cout << _heap[i] << endl;
		}
		cout << endl;
	}
	void HeapSoft(int *a, size_t size)
	{

		for (size_t i =  _size-1; i < size; i++)
		{
			_size += 1;
			_heap.push_back(a[i]);
			swap(_heap[0], _heap[_size-1]);
			_heap.pop_back();
			_size -= 1;
			//Heapdown(_heap,0);
		}
	}
protected:
	void Heapdown(size_t parent)
	{
		size_t child = parent* 2 + 1;
		while (child < _size)
		{
			if ((child + 1) < _size&&_com(_heap[child + 1], _heap[child]))
			{
				child++;
			}
			if (_com(_heap[child], _heap[parent]))
			{
				swap(_heap[child], _heap[parent]);
			}
			parent = child;
			child = parent * 2 + 1;
		}
	}
	void  Heapout(vector<T> &heap)
	{
		size_t child = _size - 1;
		size_t parent = (child - 1) / 2;
		while (child>0)
		{
			if (_com(heap[child],heap[parent]))
			{
				swap(heap[child], heap[parent]);
				child = parent;
				parent = (parent - 1) / 2;	
			}
			else
			{
				break;
			}
		}
	}
private:
	vector<T> _heap;
	size_t _size;
	com _com;
};

template<class T, class com = Less<T>>
class PriorityQueue
{
public:
	void Push(T x)
	{
		_queue.Push(x);
	}
	void Pop()
	{
		_queue.Pop();
	}
	T top()
	{
		return _queue.top()
	}
protected:
	Heap<T,com> _queue;
};
template<class T>
Heap<T> Max_Data()
{

}
void Test3()
{
	int a[N] = {0};
	int b[K+1] = {0};
	srand((unsigned)time(NULL));         
	for (int i = 0; i < N; i++)
	{
		a[i] = rand()%100;
	}
	for (int i = 0; i < K+1; i++)
	{
		b[i] = a[i];
	}
	Heap<int,Greater<int>> h(b,K+1);
	h.HeapSoft(a, N);
	h.Pop();
	h.Display();
}
void Test1()
{
	int array[10] = { 9,8,7,6,5,4,3,2,1,0};
	Heap<int> h(array, 10);
	h.Display();
	h.Push(1);
	h.Pop();
}
void Test2()
{
	PriorityQueue<int> p;
	p.Push(2);
	p.Push(5);
	p.Push(10);
	p.Push(1);
}
int main()
{
	Test1();
	//Test2();
	//Test3();
	return 0;
}