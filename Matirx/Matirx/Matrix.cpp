#include<iostream>
#include<vector>
using namespace std;

template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T *arr,size_t row,size_t col)
		:_row(row),
		_col(col)
	{
			for (size_t i = 0; i < row; i++)
			{
				for (size_t j = 0; j < col; j++)
				{
					if (i >= j)
						_array.push_back(arr[i*row+j]);
					else
						break;
				}
			}
	}
	void ChangeOne(size_t row,size_t col,T x)
	{
		size_t index = 0;
		while (index < _array.size())
		{
			if (_array[row*(row+1)/2+col]==_array[index])
			{
				_array[index] = x;
				break;
			}
			index++;
		}
	}
	void Display(size_t row, size_t col)
	{
		if (row < col)
		{
			size_t i = row;
			row = col;
			col = i;
			cout << _array[row*(row + 1) / 2 + col];
		}
		else
		{
			cout << _array[row*(row + 1) / 2 + col];
		}
		
	}
protected:
	vector<T> _array;
	size_t _row;   //ÐÐ
	size_t _col;   //ÁÐ
};


void Test1()
{
	int arr[5][5] =
	{
		{ 0, 1, 2, 3, 4 },
		{ 1, 0, 2, 3, 4 },
		{ 2, 2, 0, 3, 4 },
		{ 3, 3, 3, 0, 4 },
		{ 4, 4, 4, 4, 0 },
	};
	SymmetricMatrix<int>s((int*)arr,5,5);
	s.ChangeOne(0, 1, 2);
	s.Display(0, 1);
}
int main()
{
	Test1();
	return 0;
}


#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct Triple
{
	size_t row;
	size_t col;
	T _value;
};

template<class T>
class SparseMatrix
{
public:
	SparseMatrix(T *arr, size_t rowsize, size_t colsize,T invaild)
		:_rowsize(rowsize),
		_colsize(colsize),
		_invaild(invaild)
	{
		for (size_t i = 0; i < _rowsize; i++)
		{
			for (size_t j = 0; j < _colsize; j++)
			{
				Triple<T> t;
				if (arr[i*_colsize + j] != invaild)
				{
					t.row = i;
					t.col = j;
					t._value = arr[i*_colsize + j];
					_array.push_back(t);
				}
			}
		}
	}
	SparseMatrix(size_t rowsize, size_t colsize, T invaild)
		:_rowsize(rowsize),
		_colsize(colsize),
		_invaild(invaild)
	{}
	SparseMatrix()
	{}
	SparseMatrix<T> TransposeMatrix()
	{
		SparseMatrix<T> sm(_colsize, _rowsize, _invaild);
		for (size_t i = 0; i < _colsize; i++)
		{
			size_t index = 0;
			while (index < _array.size())
			{
				if (_array[index].col == i)
				{
					Triple<T> t;
					t.col = _array[index].row;
					t.row = _array[index].col;
					t._value = _array[index]._value;
					sm._array.push_back(t);
				}
				++index;
			}
		}
		return sm;
	}
	SparseMatrix<T> FastsposeMatrix(T *array)
	{
		SparseMatrix<T> sm(array,_colsize,_rowsize,0);
		int index = 0;
		int newsize[7];
		int newsign[7];
		memset(newsize, 0, sizeof(newsize));
		memset(newsign, 0, sizeof(newsign));
		for (size_t i = 0; i < _array.size(); i++)
		{
			++newsize[_array[i].col];
		}
		for (size_t i = 1; i < _colsize; i++)
		{
			newsign[i] = newsign[i - 1] + newsize[i - 1];
		}
		for (size_t i = 0; i < _array.size(); i++)
		{
			int index = newsign[_array[i].col];
			sm._array[index].col = _array[i].row;
			sm._array[index].row = _array[i].col;
			sm._array[index]._value = _array[i]._value;	
			newsign[_array[i].col]++;
		}
		return sm;
	}
	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _rowsize; i++)
		{
			for (size_t j = 0; j < _colsize; j++)
			{
				if (_array[index].row == i&&_array[index].col == j&&index<_array.size())
				{
					cout << _array[index]._value;
					index += 1;
				}
				else
				{
					cout << _invaild;
				}
			}
			cout << "\n" << endl;
		}
	}

protected:
	size_t _rowsize;
	size_t _colsize;
	T _invaild;
	vector<Triple<T>> _array;
};

void Test1()
{
	int arr[5][7] =
	{
		{ 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 1 },
	};
	SparseMatrix<int> s((int *)arr, 5, 7, 0);
	SparseMatrix<int> sm1;
	SparseMatrix<int> sm2;
	sm1=s.TransposeMatrix();
	sm2 = s.FastsposeMatrix((int*)arr);
	s.Display();
	sm1.Display();
	sm2.Display();
}
int main()
{
	Test1();
	return 0;


}


