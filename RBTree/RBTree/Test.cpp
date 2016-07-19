#include<iostream>


using namespace std;

enum{
	RED,
	BLACK
};

template<class K,class V>
struct BRTreenode{	
public:
	K _key;
	V _value;
	short _color;
	BRTreenode<K, V> *_left;
	BRTreenode<K, V> *_right;
	BRTreenode<K, V> *_parent;
	
	BRTreenode(K key, V value)
		:_key(key),
		_value(value),
		_color(RED),
		_left(NULL),
		_right(NULL),
		_parent(NULL)
	{}
};

template<class K,class V>
class RBTree
{
	typedef BRTreenode<K, V> node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool insert(K key, V value)
	{
		if (_root == NULL)
		{
			_root = new node(key, value);
			_root->_color = BLACK;
			return true;
		}

		node *cur = _root;
		node *parent=NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		cur = new node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		while (cur->_color == RED&&parent->_color == RED)
		{
			node *grandparent = parent->_parent;
			if (grandparent->_key > parent->_key)//左边情况
			{
				node *uncle = grandparent->_right;
				if (uncle&&uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandparent->_color = RED;
					cur= grandparent;
					parent = cur->_parent;
					_root->_color = BLACK;
				}
				else
				{
					if (cur->_key > parent->_key)//情况三
					{
						rotateL(parent);
						parent = cur;
					}
					else
						rotateR(grandparent);
						parent->_color = BLACK;	
						grandparent->_color = RED;
						break;
				}
			}
			else//在右边
			{
				if (cur->_color == RED&&parent->_color == RED)
				{
					node *uncle = grandparent->_left;
					if (uncle&&uncle->_color == RED)
					{
						parent->_color = uncle->_color = BLACK;
						grandparent->_color = RED;
						cur = grandparent;
						parent = cur->_parent;
					}
					else
					{
						if (cur->_key < parent->_key)
						{
							rotateR(parent);
							parent = cur;
						}
						rotateL(grandparent);
						parent->_color = BLACK;
						grandparent->_color = RED;
						break;
					}
				}
			}
		}
		_root->_color = BLACK;
		return true;
	}

	node* Find(K key)
	{
		if (_root == NULL)
		{
			return NULL;
		}
		
		node *cur = _root;
		
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else {
				return cur;
			}
		}
		return NULL;
	}

	bool Remove()
	{
		if (_root == NULL)
		{
			return false;
		}

	}

	void Inorder()
	{
		_Inorder(_root);
	}
	bool isBalance()
	{
		if (_root == NULL)
		{
			return false;
		}
		
		if (_root->_color == RED)
		{
			return false;
		}

		node *cur = _root;
		int count = 0;
		while (cur)
		{
			if (cur->_color == BLACK)
			{
				count++;
			}
			cur = cur->_left;
		}
		int k=0;
		return _isBalance(_root, k, count);

	}
protected:
	bool _isBalance(node *root, int k, const int count)
	{
		if (root == NULL)
		{
			return true;
		}
		
		if (root->_color == BLACK)
		{
			++k;
		}

		if (root->_color == RED)
		{
			if (root->_parent->_color == RED)
			{
				return false;
			}
		}

		if (root->_left == NULL&&root->_right == NULL)
		{
			if (count != k)
			{
				return false;
			}
		}
		return _isBalance(root->_left, k, count) && _isBalance(root->_right, k, count);
	}
	void _Inorder(node *&root)
	{
		if (root == NULL)
		{
			return;
		}

		_Inorder(root->_left);
		cout << root->_key << root->_color << endl;
		_Inorder(root->_right);
	}
	void rotateR(node *parent)
	{
		node *PLnode = parent->_left;
		node *PLRnode = PLnode->_right;
		parent->_left = PLRnode;
		if (PLRnode)
		{
			PLRnode->_parent = parent;
			PLRnode->_right = parent;
		}
		PLnode->_right = parent;
		node *ppnode = parent->_parent;
		parent->_parent = PLnode;
		if (ppnode)
		{
			if (ppnode->_key > parent->_key)
			{
				ppnode->_left = PLnode;
				PLnode->_parent = ppnode;
			}
			else
			{
				ppnode->_right = PLnode;
				PLnode->_parent = ppnode;
			}
		}
		else
		{
			PLnode->_parent = NULL;
			_root = PLnode;
		}
	}
	void rotateL(node *parent)
	{
		node *PRnode = parent->_right;
		node *PRLnode = PRnode->_left;
		parent->_right = PRLnode;
		if (PRLnode)
		{
			PRLnode->_parent = parent;
		}
		PRnode->_left = parent;
		node* ppnode = parent->_parent;
		parent->_parent = PRnode;
		if (ppnode)
		{
			if (ppnode->_key > parent->_key)
			{
				ppnode->_left = PRnode;
				PRnode->_parent = ppnode;
			}
			else
			{
				ppnode->_right = PRnode;
				PRnode->_parent = ppnode;
			}
		}
		else
		{
			PRnode->_parent = NULL;
			_root = PRnode;
		}
	}
private:
	node *_root;
};

int main()
{
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	RBTree<int, int> b;
	for (int i = 0; i < 10; ++i)
	{
		b.insert(arr[i], i);
	}
	b.Inorder();
	cout<<b.isBalance()<<endl;
	BRTreenode<int, int> *ret = b.Find(6);
	cout << ret->_key << endl;
	return 0;
}

