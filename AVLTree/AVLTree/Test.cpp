#include<iostream>

using namespace std;

template<class K,class V>
struct treeNode{
	K _key;
	V _value;
	short _bf;
	treeNode<K, V> *_left;
	treeNode<K, V> *_right;
	treeNode<K, V> *_parent;
	treeNode(K key,V value)
		:_key(key),
		_value(value),
		_bf(0),
		_left(NULL),
		_right(NULL),
		_parent(NULL)
	{}
};


template<class K, class V>
class AVLTree{
	typedef treeNode<K,V> node;
public:
	AVLTree()
		:_root(NULL)
	{}
	bool insert(K key,V value)
	{
		if (_root == NULL)
		{
			_root = new node(key, value);
			return true;
		}
		node *parent = NULL;
		node *cur = _root;
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
				return false;
		}
		if (parent->_key>key)
		{
			cur = new node(key, value);
			parent->_left = cur;
			cur->_parent = parent;
		}
		else{
			cur = new node(key, value);
			parent->_right =cur;
			cur->_parent = parent;
		}
		parent = cur->_parent;
		while (parent != NULL)
		{
			if (parent->_left == cur)
			{
				parent->_bf--;
			}
			else{
				parent->_bf++;
			}
			if (parent->_bf == 0)
			{
				break;
			}
			if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == -2)
				{
					if (cur->_bf == -1) //ÓÒÐý
					{
						rotateR(parent);
						break;
					}
					else{//×óÓÒË«è¯
						node *tmpP = parent;
						node *tmpPL = cur;
						node *tmpPLR = tmpPL->_right;
						rotateL(cur);
						rotateR(parent);
						if (tmpPLR->_left)
						{
							tmpPL->_bf = -1;
						}
						else{
							tmpP->_bf = 1;
						}
						break;

					}
				}
				else if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						rotateL(parent);
						break;
					}
					else //ÓÒ×óË«è¯
					{
						rotateR(cur);
						rotateL(parent);
						node *tmpP = parent;
						node *tmpPR = cur;
						node *tmpPRL = tmpPR->_left;
						if (tmpPRL->_left)
						{
							tmpPR->_bf = 1;
						}
						else{
							tmpP->_bf = -1;
						}
						break;
					}
				}
			}
			cur = parent;
			parent = parent->_parent;
		}
	}
	int height()
	{
		return _height(_root);
	}
	bool Isbalance()
	{
		if (_root == NULL)
		{
			return true;
		}
		int left = _height(_root->_left);
		int right = _height(_root->_right);
		return abs(left - right) <= 1;
	}
	void Inorder()
	{
		_Inorder(_root);
	}
protected:
	int _height(node *&root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int left = _height(root->_left);
		int right = _height(root->_right);
		return (left > right) ? left + 1 : right + 1;
	}
	void _Inorder(node *&root)
	{
		if (root == NULL)
		{
			return;
		}
		_Inorder(root->_left);
		cout << root->_key <<root->_bf<< endl;
		_Inorder(root->_right);
	}
	void rotateL(node *&parent)
	{
		node *nodeR = parent->_right;
		node *nodeRL = nodeR->_left;
		parent->_bf = 0;
		nodeR->_bf = 0;
		parent->_right = nodeRL;
		if (nodeRL)
		{
			nodeRL->_parent = parent;
			nodeRL->_bf = 0;
		}
		
		nodeR->_left = parent;
		node *ppnode = parent->_parent;
		parent->_parent = nodeR;
		if (ppnode)
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = nodeR;
				nodeR->_parent = ppnode;
			}
			else
			{
				ppnode->_right = nodeR;
				nodeR->_parent = ppnode;
			}
			return;
		}
		nodeR->_parent = NULL;
		_root = nodeR;
		return;

	}
	void rotateR(node *&parent)
	{
		node *nodeL = parent->_left;
		node *nodeLR = nodeL->_right;
		parent->_bf = 0;
		nodeL->_bf = 0;
		
		parent->_left = nodeLR;
		nodeL->_right = parent;	
		if (nodeLR)
		{
			nodeLR->_parent = parent;
			nodeLR->_bf = 0;
		}
	
		node *ppnode = parent->_parent;
		parent->_parent = nodeL;
		if (ppnode)
		{
			if (ppnode->_right == parent)
			{
				ppnode->_right = nodeL;
				nodeL->_parent = ppnode;
			}
			else{
				ppnode->_left = nodeL;
				nodeL->_parent = ppnode;
			}
			return;
		}
		nodeL->_parent = NULL;
		_root = nodeL;
		return;
	}
private:
	node *_root;
};


int main()
{

	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int,int> t;
	for (int i = 0; i < 10; i++)
	{
		t.insert(arr[i], i);
	}
	t.Inorder();
	cout<<t.Isbalance()<<endl;
	return 0;
}
