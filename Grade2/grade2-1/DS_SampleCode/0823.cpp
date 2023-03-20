#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>

template <class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, Node *n)
	{
		out<<*(n->data);
		return out;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const
	{
		return next;
	}
	ListNode *getPrev() const
	{
		return prev;
	}
	void setNext(ListNode *n)
	{
		next = n;
	}
	void setPrev(ListNode *p)
	{
		prev = p;
	}
	ListNode &operator=(T d)
	{
		this->setData(d);
		return *this;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL)
			at->getNext()->setPrev(node);
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL)
			tail = node;
	}
	ListNode<T> *removeFromHead()
	{
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		/*
			remove n from list here
		*/
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i)
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw std::invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			std::cout<<(*j)<<" ";
			j = j->getNext();
		}
		std::cout<<std::endl;
	}
protected:
	ListNode<T> *head, *tail;
};

template<class T>
class Stack : LinkList<T>
{
public:
	Stack() : LinkList<T>()
	{
	}
	void push(T d)
	{
		this->addFromTail(d);
	}
	ListNode<T> *pop()
	{
		return this->removeFromTail();
	}
	bool isEmpty()
	{
		return this->head == NULL;
	}
private:
};

template<class T>
class TreeNode : public Node<T>
{
public:
	TreeNode() : Node<T>()
	{
		left = NULL;
		right = NULL;
	}
	TreeNode(T d) : Node<T>(d)
	{
		left = NULL;
		right = NULL;
	}
	TreeNode(TreeNode<T> *l, TreeNode<T> *r) : Node<T>()
	{
		left = l;
		right = r;
	}
	TreeNode(T d, TreeNode<T> *l, TreeNode<T> *r) : Node<T>(d)
	{
		left = l;
		right = r;
	}
	void setLeft(TreeNode<T> *l)
	{
		left = l;
	}
	void setRight(TreeNode<T> *r)
	{
		right = r;
	}
	TreeNode *&getLeft()
	{
		return left;
	}
	TreeNode *&getRight()
	{
		return right;
	}
	bool operator>(TreeNode<T> n)
	{
		if(*(this->data) > *(n.data))
			return true;
		return false;
	}
private:
	TreeNode<T> *left, *right;
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
	{
		root = NULL;
		count = 0;
	}
	virtual void insert(T d)
	{
		TreeNode<T> *node = new TreeNode<T>(d);
		if(root == NULL)
		{
			root = node;
		}
		else
		{
			int j = count + 1;
			int k = 1;
			TreeNode<T> *cur = root;
			while(k <= j)
				k = k << 1;
			k = k >> 2;
			while(k > 1)
			{
				if(k & j)
					cur = cur->getRight();
				else
					cur = cur->getLeft();
				k = k >> 1;
			}
			if(k & j)
				cur->setRight(node);
			else
				cur->setLeft(node);
		}
		count ++;
	}
	TreeNode<T> *remove(TreeNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		TreeNode<T> *last = getLast();
		if(last == root)
		{
			count --;
			root = NULL;
			return n;
		}
		TreeNode<T> *lastsFather = getFather(last);
		if(lastsFather->getLeft() == last)
			lastsFather->setLeft(NULL);
		else
			lastsFather->setRight(NULL);
		if(last == n)
		{
			count --;
			return n;
		}
		if(n != root)
		{
			TreeNode<T> *father = getFather(n);
			if(father->getLeft() == n)
				father->setLeft(last);
			else
				father->setRight(last);
		}
		else
		{
			root = last;
		}
		last->setLeft(n->getLeft());
		last->setRight(n->getRight());
		n->setLeft(NULL);
		n->setRight(NULL);
		count --;
		return n;
	}
	TreeNode<T> *getFather(TreeNode<T> *n)
	{
		if(n == root || !exist(n))
			return NULL;
		return _getFather(root, n);
	}
	bool exist(TreeNode<T> *n)
	{
		return _exist(root, n);
	}
	TreeNode<T> *getRoot()
	{
		return root;
	}
	void print()
	{
		_print(root, 0);
	}
protected:
	TreeNode<T> *root;
	int count;
private:
	TreeNode<T> *getLast()
	{
		int j = count, k = 1;
		TreeNode<T> *cur = root;
		while(k <= j)
			k = k << 1;
		k = k >> 2;
		while(k > 0)
		{
			if(k & j)
				cur = cur->getRight();
			else
				cur = cur->getLeft();
			k = k >> 1;
		}
		return cur;
	}
	bool _exist(TreeNode<T> *r, TreeNode<T> *n)
	{
		if(n == r)
			return true;
		if(r->getLeft() && _exist(r->getLeft(), n))
			return true;
		if(r->getRight() && _exist(r->getRight(), n))
			return true;
		return false;
	}
	TreeNode<T> *_getFather(TreeNode<T> *r, TreeNode<T> *n)
	{
		if(r == NULL)
			return NULL;
		if(r->getLeft() == n || r->getRight() == n)
			return r;
		TreeNode<T> *temp;
		temp = _getFather(r->getLeft(), n);
		if(temp != NULL)
			return temp;
		temp = _getFather(r->getRight(), n);
		return temp;
	}
	void _print(TreeNode<T> *r, int n)
	{
		if(r == NULL)
			return;
		int j;
		_print(r->getRight(), n + 1);
		for(j = 0;j < n;j ++)
			std::cout<<"    ";
		std::cout<<r<<std::endl;
		_print(r->getLeft(), n + 1);
	}
};

template<class T>
class MaximumHeap : public BinaryTree<T>
{
public:
	MaximumHeap() : BinaryTree<T>()
	{
	}
	void insert(T d)
	{
		TreeNode<T> *node = new TreeNode<T>(d);
		if(this->root == NULL)
			this->root = node;
		else
		{
			int j = this->count + 1;
			int k = 1;
			TreeNode<T> *cur = this->root;
			while(k <= j)
				k = k << 1;
			k = k >> 2;
			while(1)
			{
				if(*node > *cur)
				{
					TreeNode<T> *temp = cur;
					TreeNode<T> *father = this->getFather(cur);
					if(father == NULL)
						this->root = node;
					else
						if(father->getLeft() == cur)
							father->setLeft(node);
						else
							father->setRight(node);
					node->setLeft(cur->getLeft());
					node->setRight(cur->getRight());
					cur = node;
					node = temp;
					node->setLeft(NULL);
					node->setRight(NULL);
				}
				if(k <= 1)
					break;
				if(k & j)
					cur = cur->getRight();
				else
					cur = cur->getLeft();
				k = k >> 1;
			}
			if(k & j)
				cur->setRight(node);
			else
				cur->setLeft(node);
		}
		this->count ++;
	}
	TreeNode<T> *removeRoot()
	{
		if(this->root == NULL)
			return NULL;
		TreeNode<T> *node = this->root;
		this->remove(node);
		TreeNode<T> *cur = this->root;
		if(cur == NULL)
			this->root = NULL;
		while(cur)
		{
			if((cur->getLeft() != NULL && *cur->getLeft() > *cur && cur->getRight() == NULL) || (cur->getRight() != NULL && cur->getLeft() != NULL && *cur->getLeft() > *cur && *cur->getLeft() > *cur->getRight()))
			{
				TreeNode<T> *father = this->getFather(cur);
				TreeNode<T> *temp = cur->getLeft();
				TreeNode<T> *curR = cur->getRight();
				if(father != NULL)
					if(father->getRight() == cur)
						father->setRight(temp);
					else
						father->setLeft(temp);
				else
					this->root = temp;
				cur->setRight(temp->getRight());
				cur->setLeft(temp->getLeft());
				temp->setLeft(cur);
				temp->setRight(curR);
			}
			else if(cur->getRight() != NULL && *cur->getRight() > *cur )
			{
				TreeNode<T> *father = this->getFather(cur);
				TreeNode<T> *temp = cur->getRight();
				TreeNode<T> *curL = cur->getLeft();
				if(father != NULL)
					if(father->getRight() == cur)
						father->setRight(temp);
					else
						father->setLeft(temp);
				else
					this->root = temp;
				cur->setRight(temp->getRight());
				cur->setLeft(temp->getLeft());
				temp->setRight(cur);
				temp->setLeft(curL);
			}
			else
				break;
		}
		return node;
	}
private:
};

template<class T>
class BinarySearchTree : public BinaryTree<T>
{
public:
	BinarySearchTree() : BinaryTree<T>()
	{
	}
	void insertRecursion(T d)
	{
		TreeNode<T> *node = new TreeNode<T>(d);
		_insertRecursion(&(this->root), node);
	}
	void insert(T d)
	{
		TreeNode<T> *node = new TreeNode<T>(d);
		if(this->root == NULL)
			this->root = node;
		else
		{
			TreeNode<T> *cur = this->root;
			while(1)
			{
				if(*node > *cur)
				{
					if(cur->getRight() == NULL)
					{
						cur->setRight(node);
						break;
					}
					else
						cur = cur->getRight();
				}
				else if(*cur > *node)
				{
					if(cur->getLeft() == NULL)
					{
						cur->setLeft(node);
						break;
					}
					else
						cur = cur->getLeft();
				}
				else
					break;
			}
		}
	}
	void printLoop()
	{
		Stack<TreeNode<T> *> *stack = new Stack<TreeNode<T> *>();
		TreeNode<T> *cur = this->root;
		while(1)
		{
			if(cur == NULL)
			{
				if(stack->isEmpty())
					break;
				cur = stack->pop()->getData();
				std::cout<<cur<<" ";
				cur = cur->getRight();
				continue;
			}
			stack->push(cur);
			cur = cur->getLeft();
		}
	}
private:
	void _insertRecursion(TreeNode<T> **r, TreeNode<T> *node)
	{
		if(*r == NULL)
			*r = node;
		else
			if(**r > *node)
				_insertRecursion(&((*r)->getLeft()), node);
			else	if(*node > **r)
				_insertRecursion(&((*r)->getRight()), node);
	}
};

int main()
{
	BinarySearchTree<int> *tree = new BinarySearchTree<int>();
	TreeNode<int> *node;
	//srand(time(NULL));
	int j, k, n;
	std::cin>>n;
	for(j = 0;j < n;j ++)
	{
		k = rand() % 100;
		std::cout<<k<<" ";
		tree->insertRecursion(k);
	}
	std::cout<<std::endl;
	tree->print();
	tree->printLoop();
	//tree->print();
	//tree->remove(tree->getRoot()->getLeft());
	//tree->print();
	return 0;
}
