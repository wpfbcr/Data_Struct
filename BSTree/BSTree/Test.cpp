#include<iostream>
using namespace std;


template<typename K,typename V>
struct BStreeNode{
	BStreeNode* _left;
	BStreeNode* _right;
	K _key;
	V _value;
	BStreeNode(K key,V value)
		:_left(NULL),
		_right(NULL),
		_key(key),
		_value(value)
	{}
};

template<typename K,typename V>
class BStree{
	typedef BStreeNode<K, V> Node;
public:
	BStree()
		:_root(NULL)
	{}
	//BStree()
	bool insert(K key,V value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node *cur = _root;
		Node *parent = NULL;
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
		if (parent->_key > key)
		{
			parent->_left = new Node(key, value);
		}
		else
		{
			parent->_right = new Node(key, value);
		}

	}
	void InshowNode()
	{
		 _InshowNode(_root);
	}
	bool remove(K key)
	{
		if (_root == NULL)
		{
			return NULL;
		} 
		Node *cur = _root;
		Node *parent = cur;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = parent->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = parent->_right;
			}
			else
			{
				Node *tmp = cur;
				if (cur->_left == NULL)
				{
					if (parent->_left == cur)
						parent->_left = cur->_right;	
					else if (parent->_right == cur)	
						parent->_right = cur->_right;
					else{
						parent = parent->_right;
						_root = parent;
					}
					return true;
				}
				else if (cur->_right == NULL)
				{
					if (parent->_left == cur)
						parent->_left = cur->_left;
					else if (parent->_right == cur)
						parent->_right = cur->_left;
					else
					{
						parent = parent->_left;
						_root = parent;
					}
					return true;
				}
				else
				{
					tmp = cur->_left;
					parent = cur;
					while (tmp->_right!=NULL)
					{
						parent = tmp;
						tmp = parent->_right;
					}
					cur->_key = tmp->_key;
					cur->_value = tmp->_value;
					if (parent->_left == tmp)
						parent->_left = tmp->_left;
					else
						parent->_right = tmp->_left;
					delete(tmp);
					return true;
				}
			}
		}
		return false;
	}
	Node* find(K key)
	{
		if (_root == NULL)
		{
			return NULL;
		}
		Node *cur = _root;
		while (cur)
		{
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else
				return cur;
		}
	}
	bool Rinsert(K key, V value)
	{
		return _Rinsert(_root,key,value);
	}
	bool RRemove(K key)
	{
		return _RRemove(_root, key);
	}
	Node *Rfind(K key)
	{
		return _Rfind(_root,key);
	}
protected:
	Node *_Rfind(Node * root,K key)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->_key > key)
			return _Rfind(root, key);
		else if (root->_key < key)
			return _Rfind(root, key);
		else {
			return root;
		}
	}
	bool _RRemove(Node *&root, K key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key > key)
			_RRemove(root->_left, key);
		else if (root->_key < key)
			_RRemove(root->_right, key);
		else
		{
			if (root->_left == NULL)
			{
				root = root->_right;
				return true;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
				return true;
			}
			else
			{
				Node *parent = root;
				Node *cur = root->_left;
				while (cur->_right != NULL)
				{
					parent = cur;
					cur = parent->_right;
				}
				parent->_key = cur->_key;
				parent->_value = cur->_value;
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
				{
					parent->_right = tmp->_left;
				}
					return true;
			}
		}
	}
	bool _Rinsert(Node *&root,K key,V value)
	{
		if (root == NULL)
			root = new Node(key, value);
		if (root->_key > key)
			return _Rinsert(root->_left,key,value);
		else if (root->_key < key)
			return _Rinsert(root->_right,key,value);
		else
			return false;
	}
	void _InshowNode(Node *root)
	{
		if (root == NULL)
		{
			return;
		}

		_InshowNode(root->_left);

		cout << root->_key;

		_InshowNode(root->_right);
	}
private:
	Node *_root;
};
int main()
{
	//char arr[] = { 5, 4, 8, 3, 6, 7, 9, 1 };
	char arr[] = { 5, 3, 7,1,6,8,0,9};
	BStree<int,int> b;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		b.insert(arr[i], i);
	}

	b.InshowNode();
	b.RRemove(0);
	cout << endl;
	b.InshowNode();

	//b.RRemove(8);
	//b.RRemove(1);
	//b.RRemove(3);
	//b.RRemove(4);
	////b.remove(5);
	//BStreeNode<int, int> *ret = b.Rfind(5);
	//b.RRemove(7);
	//b.RRemove(9);
	//b.RRemove(5);
	//cout << endl;
	//b.InshowNode();
	return 0;
}