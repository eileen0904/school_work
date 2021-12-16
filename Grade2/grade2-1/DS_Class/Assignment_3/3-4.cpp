#include <iostream>
#include <queue>
#include <ctime>
using namespace std;

template<class T>
class ListNode{
public:
    ListNode(){
        prev = NULL;
        next = NULL;
    }
    ListNode(T d){
        prev = NULL;
        next = NULL;
        data = d;
    }
    void setPrev(ListNode *p){
        prev = p;
    }
    void setNext(ListNode *n){
        next = n;
    }
    ListNode *getPrev() const{
        return prev;
    }
    ListNode *getNext() const{
        return next;
    }
    T getData() const{
        return data;
    }
private:
    T data;
    ListNode<T> *prev, *next;
};

template <class T>
class LinkList{
public:
    LinkList(ListNode<T> *node){
        head = node;
        tail = node;
    }
    void addFromTail(T d){
        ListNode<T> *node = new ListNode<T>(d);
        if(tail != NULL){
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if(head == NULL){
            head = node;
        }
    }
    ListNode<T> *getHead(){
        return head;
    }
    void literal(){
        ListNode<T> *cur = head;
        while(cur){
            cout<<cur->getData()<<" ";
            cur = cur->getNext();
        }
    }
private:
    ListNode<T> *head, *tail;
};

template<class T>
class List{
public:
    List(){
        next = NULL;
        data = NULL;
    }
    List(ListNode<T> *node){
        next = NULL;
        data = new LinkList<T>(node);
    }
    void add(List<T> *cur, ListNode<T> *node){
        List<T> *exist = find(cur, node->getData());
        if(exist){
            exist->_getData()->addFromTail(node->getData());
        }
        else{
            List<T> *NewList = new List<T>(node);
            while(cur->getNext()){
                cur = cur->getNext();
            }
            cur->setNext(NewList);
        }
    }
    List *find(List<T> *cur, T d){
        cur = cur->getNext();
        while(cur){
            if(cur->_getData()->getHead()->getData()==d){
                return cur;
            }
            cur = cur->getNext();
        }
        return NULL;
    }
    void setNext(List<T> *n){
        next = n;
    }
    List<T> *getNext(){
        return next;
    }
    LinkList<T> *_getData(){
        return data;
    }
    void literal(List<T> *cur){
        cur = cur->getNext();
        while(cur){
            cur->_getData()->literal();
            cur = cur->getNext();
            cout<<endl;
        }
    }
private:
    List<T> *next;
    LinkList<T> *data;
};

template<class T>
class TreeNode{
public:
    TreeNode(){
        left = NULL;
        right = NULL;
    }
    TreeNode(T d){
        data = d;
        left = NULL;
        right = NULL;
    }
    int level;
    T data;
    TreeNode<T> *left, *right;
};

template<class T>
class Tree{
public:
    Tree(){
        root = NULL;
    }
    void insert(T d){
        TreeNode<T> *node = new TreeNode<T>(d);
        insert(&root, node, 0);
    }
    void travel(List<T> *list = NULL){ //levelorder
        if(root==NULL) return;
        queue<TreeNode<T> *> q;
        q.push(root);
        while(!q.empty()){ 
            TreeNode<T> *node = q.front();
            ListNode<T> *_node = new ListNode<T>(node->data);
            if(list){
                list->add(list, _node);
            }
            if(!list){
                cout<<"Data:"<<node->data<<","<<"Lev:"<<node->level<<endl;
            }
            q.pop();
            if(node->left){
                q.push(node->left);
            }
            if(node->right){
                q.push(node->right);
            }
        }
    }
    void print(){
        _print(root, 0);
    }
private:
    TreeNode<T> *root;
    void insert(TreeNode<T> **r, TreeNode<T> *n, int lev){
        if(*r==NULL){
            n->level = lev;
            *r = n;
        }
        else if(n->data > (*r)->data){
            insert(&((*r)->right), n, lev+1);
        }
        else{
            insert(&((*r)->left), n, lev + 1);
        }
    }
    void _print(TreeNode<T> *r, int n){
        if(r==NULL) return;
		_print(r->right, n + 1);
		for(int j=0;j<n;j++){
            cout<<"    ";
        }
		cout<<r->data<<endl;
		_print(r->left, n + 1);
    }
};

int main(){
    srand(time(NULL));
    Tree<int> *tree = new Tree<int>();
    for(int i=0;i<10;i++){
        tree->insert(rand()%10);
    }
    tree->travel();
    cout<<endl;
    tree->print();
    cout<<endl;
    List<int> *list = new List<int>();
    tree->travel(list);
    cout<<endl;
    list->literal(list);
    cout<<endl;

    return 0;
}
