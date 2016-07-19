#include<iostream>
#include<queue>
#include<stack>
using namespace std;

template<class T> 
struct rootnode
{
	T _value;
	rootnode<T> *_leftnode;
	rootnode<T> *_rightnode;
	rootnode<T>(T value)
		: _value(value),
		_leftnode(NULL),
		_rightnode(NULL)
	{}
};

template <class T>
class BinaryTree
{
public:
	BinaryTree<T>( T *str)
	{
		T *tmp = str;
		_root = _BinaryTree(tmp);
	}
	~BinaryTree()
	{
		_Clear(_root);
	}
	BinaryTree<T> (BinaryTree &t)
	{
		_root=_Copy(t._root);
	}
	BinaryTree<T>& operator=(BinaryTree t)
	{
		if (*this != t)
		{
			swap(_root, t._root);
		}
	}
	void Fastorder()
	{
		_Fastorder(_root);
	}
	void Inorder()
	{
		_Inorder(_root);
	}
	void Postorder()
	{
		_Postorder(_root);
	}
	void Levelorder()
	{
		queue<rootnode<T>*> q;
			if (_root == NULL)
			{
				return;
			}
			q.push(_root);
			while (!q.empty())
			{
				rootnode<T>* root = q.front();
				cout << root->_value;
				q.pop();
				if (root->_leftnode != NULL)
				{
					q.push(root->_leftnode);
				}
				if (root->_rightnode != NULL)
				{
					q.push(root->_rightnode);
				}
			}	
	}
	int leafnum()
	{
		int num = 0;
		num=_Leafnum(_root,num);
		return num;
	}
	int Size()
	{
		int size = 0;
		_Size(_root,size);
		return size;
	}
	int Depth()
	{
		int Depth = _Depth(_root);
		return Depth;
	}
	bool check_balance()
	{
		if (_check_balance(_root)<=0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	void NRfastorder()
	{
		stack<rootnode<T>*> s;
		if (_root != NULL)
		{
			s.push(_root);
		}
		while (!s.empty())
		{
			rootnode<T>* front=s.top();
			cout<<front->_value;
			s.pop();
			if (front->_rightnode != NULL)
			{
				s.push(front->_rightnode);
			}
			if (front->_leftnode != NULL)
			{
				s.push(front->_leftnode);
			}
		}
	}
	void NRinorder()
	{
		stack<rootnode<T>*>s;
		rootnode<T>*cur = _root;
		rootnode<T>* top = NULL;
		while (cur||!s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_leftnode;
			}			
			if (top != s.top()->_rightnode)
			{
				top = s.top();
				cout << top->_value;
				s.pop();
				cur = top->_rightnode;
			}
			else
			{
				top = s.top();
				cout << top->_value;
				s.pop();
			}

		}
	}

	void NRpostorder()
	{
		rootnode<T>*cur = _root;
		stack<rootnode<T>*> s;
		rootnode<T>*top = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_leftnode;
			}
			if (s.top()->_rightnode != NULL&&top != s.top()->_rightnode)
			{

				top = s.top();
				cur = top->_rightnode;
			
			}
			else
			{
				top = s.top();
				s.pop();
				cout << top->_value;
			}
		

		}
	}
protected:
	rootnode<T>* _BinaryTree(T *&str)
	{
		rootnode<T> *root = NULL;
		if (*str != '#'&&*str != '\0')
		{
			root = new rootnode<T>(*str);
			str++;
			root->_leftnode = _BinaryTree(str);
			str++;
			root->_rightnode = _BinaryTree(str);
		}
		return root;
	}
	void _Fastorder(rootnode<T> *&root)
	{
		if (root == NULL)
		{
			
			return;
		}
		else
		{
			cout << root->_value;
			_Fastorder(root->_leftnode);
			_Fastorder(root->_rightnode);
			
		}
	}
	void _Inorder(rootnode<T> *root)
	{
		if (root == NULL)
		{
			return;
		}
		_Inorder(root->_leftnode);
		cout << root->_value;
		_Inorder(root->_rightnode);
	}

	void _Postorder(rootnode<T> *root)
	{
		if (root == NULL)
		{
			return;
		}
		_Postorder(root->_leftnode);
		_Postorder(root->_rightnode);
		cout << root->_value;
	}
	void _Clear(rootnode<T> *root)
	{
		if (root == NULL)
		{
			return;
		}
		rootnode<T> *tmp = root->_leftnode;
		rootnode<T> *tmp2 = root->_rightnode;
		delete root;
		_Clear(tmp);
		_Clear(tmp2);
	}
	rootnode<T>* _Copy(rootnode<T> *root)
	{
		rootnode<T> *newroot = NULL;
		if (root == NULL)
		{
			return newroot;
		}
		newroot = new rootnode<T>(root->_value);
		newroot->_leftnode = _Copy(root->_leftnode);
		newroot->_rightnode = _Copy(root->_rightnode);
		return newroot;
	}
	int _Size(rootnode<T> *root,int &size)
	{
		if (root == NULL)
		{
			return 0;
		}
		size++;
		_Size(root->_leftnode,size);
		_Size(root->_rightnode,size);
		return size;
	}

	int _Depth(rootnode<T>*root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int depth = 1;
		int right = 0;
		int left = 0;
		left = _Depth(root->_leftnode) + depth;
		right = _Depth(root->_rightnode) + depth;
		if (left > right)
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	int _check_balance(rootnode<T> *head)
	{
		if (head == NULL)
		{
			return 0;
		}
		int left = _check_balance(head->_leftnode);
		int right = _check_balance(head->_rightnode);
		if ((left >= 0) && (right >= 0))
		{
			if ((left - right <= 1) && (left - right >= -1))
			{
				return (left >= right ? (left+1) : (right+1)); 
			}
		}
		return -1;
	}
	int _Leafnum(rootnode<T> *root, int &leafnum)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (root->_leftnode == NULL&&root->_rightnode == NULL)
		{
			leafnum += 1;
		}
		_Leafnum(root->_leftnode, leafnum);
		_Leafnum(root->_rightnode, leafnum);
		return leafnum;
	}
private:
	rootnode<T> *_root;
};


enum PointerTag
{
	THREAD,
	LINK
};
template<class T>
struct BinaryTreeXsh
{
	BinaryTreeXsh<T> *_leftnode;
	BinaryTreeXsh<T> *_rightnode;
	BinaryTreeXsh<T> *_parent;
	PointerTag _LeftTag;
	PointerTag _RightTag;
	T _value;
	BinaryTreeXsh(const T& x)
		:_value(x),
		_leftnode(NULL),
		_rightnode(NULL),
		_parent(NULL),
		_LeftTag(LINK),
		_RightTag(LINK)
		{}
};

template<class T>
class BinaryTreeThd
{
public:
	BinaryTreeThd<T>(T *str)
	{
		T *tmp = str;
		_root = _BinaryTreeThd(tmp);
	}
	void PrevorderThreading()
	{
		BinaryTreeXsh<T> *prev = NULL;
		_PrevorderThreading(_root, prev);
	}
	void Prevorder()
	{
		BinaryTreeXsh<T>*cur = _root;
		while (cur)
		{
			cout << cur->_value;
			if (cur->_LeftTag == LINK)
			{
				cur = cur->_leftnode;
			}
			else
			{
				cur = cur->_rightnode;
			}
		}
	}
	void InorderThreading()
	{
		BinaryTreeXsh<T> *prev = NULL;
		_InorderThreading(_root, prev);
	}
	void Inorder()
	{
		BinaryTreeXsh<T>* cur = _root;
		if (cur == NULL)
		{
			return;
		}
		while (cur)
		{
			while (cur->_LeftTag != THREAD)
			{
				cur = cur->_leftnode;
			}
			cout << cur->_value;
			while (cur->_RightTag != LINK)
			{
				cur = cur->_rightnode;
				cout << cur->_value;
			}
			cur = cur->_rightnode;
		}
	}
	void PostorderThreading()
	{
		BinaryTreeXsh<T>*prev = NULL;
		_PostorderThreading(_root, prev);
	}
	void Postorder()
	{
		BinaryTreeXsh<T> *cur = _root;
		BinaryTreeXsh<T> *prev= NULL;
		int flag = 0;
		if (cur == NULL)
		{
			return;
		}
		while (cur)
		{
			while (cur&&cur->_LeftTag != THREAD)
			{
				cur = cur->_leftnode;
			}
			while (cur&&cur->_RightTag != LINK)
			{
				cout << cur->_value;
				prev = cur;
				cur = cur->_rightnode;
			}
			while(cur&&cur->_rightnode==prev)
			{
				cout << cur->_value;
				prev = cur;
				cur = cur->_parent;
			}
			if (cur == NULL)
			{
				break;
			}
			cur = cur->_rightnode;
		}

	}
protected:
	BinaryTreeXsh<T>* _BinaryTreeThd(T *&str)
	{
		BinaryTreeXsh<T> *root = NULL;
		if (*str != '#'&&*str != '\0')
		{
			root = new BinaryTreeXsh<T>(*str);
			str++;
			root->_leftnode = _BinaryTreeThd(str);
			if (root->_leftnode)
			{
				root->_leftnode->_parent=root;
			}
			str++;
			root->_rightnode = _BinaryTreeThd(str);
			if (root->_rightnode)
			{
				root->_rightnode->_parent=root;
			}
		}
		return root;
	}
	void _PrevorderThreading(BinaryTreeXsh<T> *cur, BinaryTreeXsh<T> *&prev)
	{
		if (cur == NULL)
		{
			return;
		}
		if (cur->_leftnode==NULL)
		{
			cur->_LeftTag=THREAD;
			cur->_leftnode=prev;
		}
		if (prev&&prev->_rightnode==NULL)
		{
			prev->_RightTag = THREAD;
			prev->_rightnode = cur;
		}
		prev = cur;
		if (cur->_LeftTag == LINK)
		{
			_PrevorderThreading(cur->_leftnode, prev);
		}
		if (cur->_RightTag == LINK)
		{
			_PrevorderThreading(cur->_rightnode, prev);
		}
	}
	void _InorderThreading(BinaryTreeXsh<T>* root, BinaryTreeXsh<T> *&prev)
	{
		BinaryTreeXsh<T>*cur = root;
		if (cur == NULL)
		{
			return;
		}
		_InorderThreading(cur->_leftnode, prev);
		
		if (cur->_leftnode == NULL)
		{
			cur->_LeftTag = THREAD;
			cur->_leftnode = prev;
		}
		if (prev&&prev->_rightnode == NULL)
		{
			prev->_RightTag = THREAD;
			prev->_rightnode = cur;
		}
		prev = cur;
		_InorderThreading(cur->_rightnode, prev);
	}
	void _PostorderThreading(BinaryTreeXsh<T>*root, BinaryTreeXsh<T>*&prev)
	{
		BinaryTreeXsh<T>*cur = root;
		if (cur == NULL)
		{
			return;
		}
		_PostorderThreading(cur->_leftnode, prev);
		_PostorderThreading(cur->_rightnode, prev);
		if (cur->_leftnode==NULL)
		{
			cur->_LeftTag = THREAD;
			cur->_leftnode = prev;
		}
		if (prev&&prev->_rightnode == NULL)
		{
			prev->_RightTag = THREAD;
			prev->_rightnode = cur;
		}
		prev = cur;
	}
private:
	BinaryTreeXsh<T> *_root;
};

void Test1()
{
	char *str = "123##45##6##78###";
	BinaryTree<char> b1(str);
	//BinaryTree<char> b2(b1);
	//BinaryTree<char> b3 = b2;
	b1.Fastorder();
	//cout << endl;
	//b1.Inorder();
	//cout << endl;
	//b1.Postorder();
	//cout << endl;
	//b2.Fastorder();
	//cout << endl;
	//b3.Fastorder();
	//cout << endl;
	//cout << b3.Size()<<endl;
	//cout << b3.Depth() << endl;
	//b3.Levelorder();
	//cout << endl;
	//cout << b3.leafnum()<<endl;
}



void Test2()
{
	char *str = "123456#######";
	char *str2 = "123##4#####";
	BinaryTree<char> b1(str2);
	//b1.NRfastorder();
	//cout << endl;
	//b1.NRinorder();
	//cout << endl;
	//b1.NRpostorder();
	if (b1.check_balance())
	{
		cout << true;
	}
	else
	{
		cout << false;
	}
}
void Test3()
{
	/*char *str = "123##4##56##";
	BinaryTreeThd<char> b1(str);
 	b1.PrevorderThreading();
	b1.Prevorder();
	cout << endl;
	char *str2 = "123##4##56##";
	BinaryTreeThd<char> b2(str2);
	b2.InorderThreading();
	b2.Inorder();*/
	char *str = "123##4##56##";
	BinaryTreeThd<char> b1(str);
	b1.PostorderThreading();
	b1.Postorder();

}
void Test4()
{
	char *str = "123##4##56###";
	BinaryTree<char> b1(str);
	cout<<b1.leafnum()<<endl;
}
int main()
{
	//Test1();
	Test2();
	//Test3();
	//Test4();
	return 0;
}