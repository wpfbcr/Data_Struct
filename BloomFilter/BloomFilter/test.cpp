#include<iostream>
#include<vector>
#include<string>
using namespace std;


template<class T>
struct filt1{
	size_t operator()(const T* str)
	{
		if (!*str)   // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 2166136261;
		while (size_t ch = (size_t)*str++)
		{
			hash *= 16777619;
			hash ^= ch;
		}
		return hash;
	}
};

template<class T>
struct  filt2{

	size_t operator()(const T* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
	}

};


template<class T>
struct  filt3{
	size_t operator()(const T* str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};


template<class T>
struct  filt4{
	size_t operator()(const T* str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

template<class T>
struct  filt5{
	size_t operator()(const T* str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
};
template<class T, class filt1 = filt1<T>, class filt2 = filt2<T>,class filt3 = filt3<T>,class filt4 = filt4<T>, class filt5 = filt5<T>>

class BloomFilter{
public:
	BloomFilter()
	{
		_table.resize(100);
		_size = _table.size();
	}

	bool find(T *str)
	{
		if (!_table[_filt1(str) % _size])
		{
			return false;
		}
		if (!_table[_filt2(str) % _size])
		{
			return false;
		}
		if (!_table[_filt3(str) % _size])
		{
			return false;
		}
		if (!_table[_filt4(str) % _size])
		{
			return false;
		}
		if (!_table[_filt5(str) % _size])
		{
			return false;
		}
		cout << str << "is exist" << endl;
		return true;
	}
	bool Binsert(T *str)
	{
		if (find(str))
		return false;
		_table[_filt1(str) % _size]++;
		_table[_filt2(str) % _size]++;
		_table[_filt3(str) % _size]++;
		_table[_filt4(str) % _size]++;
		_table[_filt5(str) % _size]++;
		return true;
	}
private:
	vector<int> _table;
	size_t _size;
	filt1 _filt1;
	filt2 _filt2;
	filt3 _filt3;
	filt4 _filt4;
	filt5 _filt5;
};

int main()
{
	BloomFilter<char> b;
	b.Binsert("hellowoeld");
	b.Binsert("aaaaaaaaaa");
	b.Binsert("bbbbbbbbbb");
	b.Binsert("cccccccccc");
	b.Binsert("dddddddddd");
	b.find("hellowoeld");
	b.find("aaaaaaaaaa");
	b.find("bbbbbbbbbb");
	b.find("cccccccccc");
	b.find("cccccccccd");
	b.find("dddddddddd");
	b.find("ddddert");
	b.find("dddddrtwer");
	b.find("dddddwwertwer");
	return 0;
}