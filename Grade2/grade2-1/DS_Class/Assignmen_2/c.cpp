#include<iostream>
using namespace std;

template <class T>
class Node{
    public:
        Node(){
            prev = NULL;
            next = NULL;
        }
        Node(T d){
            prev = NULL;
            next = NULL;
            data = d;
        }
        void setPrev(Node *p){
            prev = p;
        }
        void setNext(Node *n){
            next = n;
        }
        Node *getPrev() const{
            return prev;
        }
        Node *getNext() const{
            return next;
        }
        T getData() const{
            return data;
        }

    private:
        T data;
        Node *prev, *next;
};

template <class T>
class deq{
    public:
        deq(){
            head = NULL;
            tail = NULL;
        }
        ~deq() {
            cout<<"Destructor"<<endl;
        }
        bool IsEmpty(){
            if(head==NULL && tail==NULL){return true;}
            else{return false;}
        }
        bool IsFull(){}
        void AddHead(T d){
            Node<T> *node = new Node<T>(d);
            if(head==NULL){
                head = node;
            }
            else{
                head->setPrev(node);
                node->setNext(head);
                head = node;
            }
            if(tail==NULL){
                tail = node;
            }
        }
        void AddTail(T d){
            Node<T> *node = new Node<T>(d);
            if(tail==NULL){
                tail = node;
            }
            if(head==NULL){
                head = node;
            }
            tail->setNext(node);
            node->setPrev(tail);
            tail = node;
        }
        void DeleteHead(){
            Node<T> *temp = head;
            if(head!=NULL){
                head = head->getNext();
                if(head!=NULL){
                    head->setPrev(NULL);
                }
                else{
                    tail = NULL;
                }
                temp->setNext(NULL);
            }
        }
        void DeleteTail(){
            Node<T> *temp = tail;
            if(tail!=NULL){
                tail = tail->getPrev();
                if(tail!=NULL){
                    tail->setNext(NULL);
                }
                else{
                    head = NULL;
                }
                temp->setPrev(NULL);
            }
        }
        bool CheckHead(){
            if(head->getNext()){return true;}
            return false;
        }
        bool CheckTail(){
            if(tail->getPrev()){return true;}
            return false;
        }
        void reverse(){
            Node<T> *cur = head;
            Node<T> *n, *p;
            while(cur!=NULL){
                p = cur->getPrev();
                cur->setPrev(cur->getNext());
                cur->setNext(p);
                cur = cur->getPrev();
            }
            if(p!=NULL){
                tail = head;
                head = p->getPrev();
            }
        }
        void print(){
            Node<T> *start = head;
            while(start!=NULL){
                cout<<start->getData()<<" ";
                start = start->getNext();
            }
            cout<<endl;
        }
    private:
        Node<T> *head, *tail;
};

int main(){
    deq<int> *q = new deq<int>();
    q->AddTail(1);
    q->AddTail(2);
    q->AddTail(3);
    q->print();
    q->AddHead(4);
    q->AddHead(5);
    q->AddHead(6);
    q->print();
    q->DeleteTail();
    q->print();
    q->DeleteHead();
    q->print();
    q->reverse();
    q->print();
    return 0;
}
