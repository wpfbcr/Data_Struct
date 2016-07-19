//1 ¹þÏ£±í

// ³ýÁôÓàÊý·¨£¨VT£©
#include<iostream>
#include<vector>
using namespace std;
enum Signtable
{
	EXIST,
	EMPTY,
	DELETE
};
template<class T,class K>
struct Package
{
	T _myValue;
	K _key;
	Signtable _sign;
};

template <class T, class K> 
class HashTable
{
public:
	HashTable()
		:_capacity(0),
		_size(0)
	{
		_Newcapacity();
	}
	void Insert(T t,K k)
	{
		double j = (double)_size / (double)_capacity;
		 if (j>= 0.7)
		{
			_Newcapacity();
		}
			size_t key = _returnkey(k);
			while (_hashTable[key]._sign == EXIST)
			{
				key++;
				if (key > _capacity - 1)
				{
					key = 0;
				}
			}
			_hashTable[key]._myValue = t;
			_hashTable[key]._key = k;
			_hashTable[key]._sign = EXIST;
			_size++;
	}
	bool Find(K k, T t)
	{
		size_ flag = 0;
		size_t key = _returnkey(k);
		while (_hashTable[key]._key != EMPTY)
		{
			if (_hashTable[key]._myValue == t)
			{
				return  true;
			}
			key++;
			if (key > _capacity - 1)
			{
				key = 0;
				flag++;
			}
			if (flag > 1)
			{
				break;
			}
		}
		return false;
		
	}
	bool Remove(K k,T t)
	{
		size_t flag = 0;
		size_t key = _returnkey(k);
		while (_hashTable[key]._key != EMPTY)
		{
			if (_hashTable[key]._myValue == t&&_hashTable[key]._sign==EXIST)
			{
				_hashTable[key]._sign = DELETE;
				return  true;
			}
			key++;
			if (key > _capacity - 1)
			{
				key = 0;
				flag ++ ;
			}
			if (flag > 1)
			{
				break;
			}
			return false;
		}
	}
protected:
	void _Newcapacity()
	{
		if (_capacity == 0)
		{
			_hashTable.resize(10);
			_capacity = 10;
			size_t i = 0;
			for (i = 0; i < _capacity; i++)
			{
				_hashTable[i]._myValue = 0;
				_hashTable[i]._key = 0;
				_hashTable[i]._sign = EMPTY;

			}
		}
		else
		{
			HashTable<T,K> newTable;
			newTable._hashTable.resize(_capacity * 2);
			newTable._capacity = _capacity*2;
			for (size_t i = 0; i < newTable._capacity; i++)
			{
				newTable._hashTable[i]._myValue = 0;
				newTable._hashTable[i]._key = 0;
				newTable._hashTable[i]._sign = EMPTY;

			}
			size_t k = 0;
			while (k<_capacity)
			{
				if (_hashTable[k]._sign != EMPTY)
				{
					newTable.Insert(_hashTable[k]._myValue, _hashTable[k]._key);
				}
				k++;
			}
			newTable._size = _size;;;;;
			*this = newTable;
		}
	}
	size_t _returnkey(K k)
	{
		return k%_capacity;
	}
private:
	vector<Package<T, K>> _hashTable;
	size_t _capacity;
	size_t _size;
};

void Test1()
{
	HashTable<int, int> hash;
	hash.Insert(2, 2);
	hash.Insert(3, 2);
	hash.Insert(4, 2);
	hash.Insert(4, 2);
	hash.Insert(3, 2);
	hash.Insert(4, 2);
	hash.Insert(4, 2);
	hash.Insert(2, 2);
	hash.Insert(3, 2);
	hash.Insert(4, 2);
	hash.Insert(4, 2);
	cout << hash.Remove(4, 2) << endl;
	cout << hash.Find(4, 2) << endl;
}

int main()
{
	Test1();
	return 0;
}

¹þÏ£Í°



#include<iostream>
#include<vector>
#include<string>

using namespace std;
static size_t Pri;
template<class T>
struct BasicType
{
	size_t operator()(T t,size_t capacity)
	{
		return t%capacity;
	}
};
static size_t BKDRHash(const char *str)
	{
		unsigned int seed = 131; // 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}


template<class T>
struct StringType
{
	
	size_t operator()(T t, size_t capacity)
	{
		size_t size = BKDRHash(t.c_str());
		return size%capacity;
	}
};


template<class T,class K>
struct KV
{
	T _myValue;
	K _key;
	KV *_next;
public:
	KV<T,K>(T t, K k)
		:_myValue(t),
		_key(k),
		_next(NULL)
	{}
};

template<class T,class K,class Type=BasicType<K>>
class Hsahbucket
{
public:
	Hsahbucket()
		:_size(0),
		_capacity(0)
	{
		Newcapacity();
	}
	~Hsahbucket()
	{
		_hashTable.~vector();
	}
	void Insert(T t, K k)
	{
		if (_size == _capacity)
		{
			Newcapacity();
		}
		size_t key = Returnkey(k);
		if (_hashTable[key] != NULL)
		{
			KV<T, K>* cur = _hashTable[key];
			KV<T, K>*tmp = new KV<T, K>(t, k);
			_hashTable[key]=tmp;
			tmp->_next = cur;
		}
		else
		{
			_hashTable[key] = new KV<T, K>(t, k);
		}
		_size++;
	}
	bool Find(T t,K k)
	{
		size_t key = Returnkey(k);
		if (_hashTable[key == NULL])
		{
			return false;
		}
		else
		{
			KV<T, K> *cur = _hashTable[key];
			while (cur)
			{
				if (cur->_myValue == t)
				{
					return true;
				}
				cur = cur->_next;
			}
			return false;
		}
	}
	bool Remove(T t, K k)
	{
		size_t key = Returnkey(k);
		if (_hashTable[key == NULL])
		{
			return false;
		}
		else
		{
			KV<T, K> *cur = _hashTable[key];
			if (cur->_next == NULL)
			{
				if (cur->_myValue == t)
				{
					delete cur;
					cur = NULL;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (cur->_myValue == t)
				{
					delete cur;
					cur = NULL;
					return true;
				}
				else
				{
					KV<T, K> *tmp = cur->_next;
					while (tmp)
					{
						if (tmp->_myValue == t)
						{
							cur->_next = tmp->_next;
						}
						cur = cur->_next;
						tmp = tmp->_next;
					}
				}
			}
		}
	}
protected:
	
	size_t Capa(size_t _capacity, size_t &Pri)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		if (_capacity == _PrimeList[_PrimeSize])
		{
			return _PrimeList[_PrimeSize];
		}
		if (_capacity > _PrimeList[Pri])
		{
			return _PrimeList[++Pri];
		}
	}

	void Newcapacity()
	{
		Pri = 1;
		if (_capacity == 0)
		{
			_hashTable.resize(53);
			_capacity = 53;
			size_t i = 0;
		}
		else
		{
			Hsahbucket<T, K,Type> newhash;
			size_t capa = Capa(_capacity, Pri);
			newhash._hashTable.resize(capa);
			size_t num = _capacity;
			newhash._capacity = capa;
			for (size_t i = 0; i < _capacity; i++)
			{
				if (_hashTable[i] != NULL)
				{
					KV<T, K> *cur = _hashTable[i];
					while (cur!= NULL)
					{
						size_t key = Returnkey(cur->_key);
						if (newhash._hashTable[key]!= NULL)
						{
							KV<T, K> *tmp = newhash._hashTable[key];
							KV<T, K> *head = new KV<T, K>(cur->_myValue, cur->_key);
							newhash._hashTable[key] = head;
							head->_next = tmp;
						}
						else
						{
							newhash._hashTable[key] = new KV<T, K>(cur->_myValue, cur->_key);
						} 
						cur = cur->_next;
					}
				}
			}
			newhash._size = _size;
			*this = newhash;
		}
	}
	size_t Returnkey(K k)
	{
		return _type(k,_capacity);
	}
private:
	vector<KV<T, K>*> _hashTable;
	size_t _size;
	size_t _capacity;
	Type _type;
};

void Test1()
{
	Hsahbucket<string, int> Hash;
	Hash.Insert("zhangbochao", 10);
	Hash.Insert("zhangbochao", 9);
	Hash.Insert("zhangbochao", 12);
	Hash.Insert("zhangbochao", 11);
	//for (int i = 0; i < 100; i++)
	//{
	//	Hash.Insert("zhangbochao", i);
	//}
	cout << Hash.Find("zhangbochao", 10) << endl;
	cout << Hash.Remove("zhangbochao", 11) << endl;
}

void Test2()

{
	Hsahbucket<string, string,StringType<string>>hash;
	hash.Insert("China", "sdfasdf");
}
int main()
{
	//Test1();
	Test2();
	return 0;
}