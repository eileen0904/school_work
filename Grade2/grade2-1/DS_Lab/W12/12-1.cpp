#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
using namespace std;

template<class T>
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
    friend ostream &operator<<(std::ostream &out, Node n)
    {
        out<<*(n.data);
        return out;
    }
    friend ostream &operator<<(std::ostream &out, Node *n)
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
        size = 0;
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
        size++;
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
        size++;
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
        size++;
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
        size--;
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
        size--;
        return n;
    }
    ListNode<T> *remove(ListNode<T> *n)
    {
        if(!exist(n))
            return NULL;
        if(n == head)
            return removeFromHead();
        if(n == tail)
            return removeFromTail();
        n->getPrev()->setNext(n->getNext());
        n->getNext()->setPrev(n->getPrev());
        n->setNext(NULL);
        n->setPrev(NULL);
        size--;
        return n;
    }
    ListNode<T> *exist(T d)
    {
        ListNode<T> *j = head;
        while(j != NULL)
        {
            if(j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
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
        for(k = 0; k < i && j != NULL; k ++)
            j = j->getNext();
        if(j == NULL)
            throw invalid_argument("index does not exist.");
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
        cout<<endl;
    }
	bool IsEmpty(){
		if(head==NULL && tail==NULL) return true;
		else return false;
	}
    int getSize(){
        return size;
    }
protected:
    ListNode<T> *head, *tail;
    int size = 0;
};

/*
	Please finish the TreeNode class, TreeNode class represent a node in a general tree.
	A general tree is different from binary tree, every node in binary tree have at most two child node, but a node in general tree may have more than two child node.
*/
template<class T>
class TreeNode : public Node<T>
{
public:
    TreeNode() : Node<T>()
    {
        child = new LinkList<TreeNode<T> *>();
    }
    TreeNode(T d) : Node<T>(d)
    {
        child = new LinkList<TreeNode<T> *>();
    }
    /*
    	Add a child to this node.
    */
    void addChild(TreeNode *n)
    {
        child->addFromTail(n);
    }
    /*
    	Add a child to this node.
    */
    void addChild(T d)
    {
        child->addFromTail(new TreeNode<T>(d));
    }
    /*
    	Return the nth child of the node.
    */
    TreeNode<T> *operator[](int n)
    {
        //return child->operator[](n).getData();
        return (*child)[n].getData();
    }
    int _getSize(){
        return child->getSize();
    }
private:
    LinkList<TreeNode<T> *> *child;
};

/*
	Please finish the Tree class. Tree class respresent a general tree, 
	that means node on this tree may have more than two child node.
*/
template<class T>
class Tree
{
public:
    Tree()
    {
        root = NULL;
    }
    /*
    	return the nth node on this tree with level order.
    */
    TreeNode<T> *operator[](int n)
    {
        int j, k;
        if(root == NULL)
            return NULL;
        LinkList<TreeNode<T> *> *q = new LinkList<TreeNode<T> *>();
        q->addFromHead(root);
        TreeNode<T> *temp = q->removeFromTail()->getData();
        for(j = 0; j < n; j ++)
        {
            k = 0;
            while(1)
            {
                try
                {
                    q->addFromHead((*temp)[k]);
                }
                catch(invalid_argument e)
                {
                    break;
                }
                k ++;
            }
            temp = q->removeFromTail()->getData();
        }
        return temp;
    }
    /*
    	return the number of nodes on this tree.
    */
    int count()
    {
        return _count(root);
    }
    /*
    	print all the node on this tree with level order.
    */
    void levelOrder()
    {
        int j, k;
        if(root == NULL)
            return;
        ListNode<TreeNode<T> *> * t;
        LinkList<TreeNode<T> *> *q = new LinkList<TreeNode<T> *>();
        q->addFromHead(root);
        TreeNode<T> *temp = q->removeFromTail()->getData();
        for(j = 0;; j ++)
        {
            cout<<temp<<" ";
            k = 0;
            while(1)
            {
                try
                {
                    q->addFromHead((*temp)[k]);
                }
                catch(invalid_argument e)
                {
                    break;
                }
                k ++;
            }
            t = q->removeFromTail();
            if(t == NULL)
                break;
            else
                temp = t->getData();
        }
        cout<<endl;
    }
    /*
    	print all the node on this tree with preorder.
    */
    void preorder()
    {
		cout<<"Preorder:";
		LinkList<TreeNode<T> *> *s = new LinkList<TreeNode<T> *>();
        TreeNode<T> *temp;
        ListNode<TreeNode<T> *> *t;
		s->addFromHead(root);
		while(!s->IsEmpty()){
            t = s->removeFromTail();
            temp = t->getData();
			cout<<temp<<" ";
            for(int i=temp->_getSize()-1;i>=0;i--){
                s->addFromTail((*temp)[i]);
            }
		}
        cout<<endl;
    }
    /*
    	print all the node on this tree with postorder.
    */
    void postorder()
    {
		cout<<"Postorder:";
		LinkList<TreeNode<T> *> *s = new LinkList<TreeNode<T> *>();
        LinkList<TreeNode<T> *> *result = new LinkList<TreeNode<T> *>();
        TreeNode<T> *temp;
        ListNode<TreeNode<T> *> *t;
		s->addFromHead(root);
		while(!s->IsEmpty()){
            t = s->removeFromTail();
            temp = t->getData();
            result->addFromHead(temp);
            for(int i=0;i<temp->_getSize();i++){
                s->addFromTail((*temp)[i]);
            }
		}
        int size = result->getSize();
        for(int i=0;i<size;i++){
            t = result->removeFromHead();
            cout<<t->getData()<<" ";
        }
        cout<<endl;
    }
    /*
    	set the root of this tree.
    */
    void setRoot(T d)
    {
        root = new TreeNode<T>(d);
    }
private:
    TreeNode<T> *root;
    int _count(TreeNode<T> *r)
    {
        int n = 0;
        int j = 0;
        if(r == NULL)
            return 0;
        while(1)
        {
            try
            {
                n += _count((*r)[j]);
            }
            catch(invalid_argument e)
            {
                break;
            }
            j ++;
        }
        return n + 1;
    }
};

int main()
{
    Tree<int> *tree = new Tree<int>();
    srand(time(NULL));
    int j, k, i;
    for(j = 0; j < 10; j ++)
    {
        if(tree->count() == 0)
            tree->setRoot(j);
        else
        {
            k = rand() % tree->count();
            cout<<k<<", "<<(*tree)[k]<<", "<<j<<endl;
            (*tree)[k]->addChild(j);
        }
    }
    cout<<tree->count()<<std::endl;
    tree->levelOrder();
    tree->preorder();
    tree->postorder();
}
