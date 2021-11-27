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
class TEQ{
    public:
        TEQ(){
            head = NULL;
            tail = NULL;
        }
        ~TEQ() {
            cout<<"Destructor"<<endl;
        }
        bool isFull(){}
        bool IsEmpty(){
            if(head==NULL && tail==NULL){return true;}
            else{return false;}
        }
        void addFront(T d){
            Node<T> *node = new Node<T>(d);
            if(IsEmpty()){
                head = node;
                tail = node;
                count++;
            }
            else{
                head->setPrev(node);
                node->setNext(head);
                head = node;
                count++;
            }
        }
        void addRear(T d){
            Node<T> *node = new Node<T>(d);
            if(IsEmpty()){
                head = node;
                tail = node;
                count++;
            }
            else{
                tail->setNext(node);
                node->setPrev(tail);
                tail = node;
                count++;
            }
        }
        void addMiddle(T d){
            Node<T> *node = new Node<T>(d);
            if(IsEmpty()){
                head = node;
                tail = node;
                count++;
            }
            else{
                int mid = (count+1) / 2;
                Node<T> *cur = head;
                if(count==1){
                    cur->setNext(node);
                    node->setPrev(cur);
                    tail = node;
                    count++;
                }
                else{
                    int temp = 1;
                    while(temp<mid){
                        cur = cur->getNext();
                        temp++;
                    }
                    cur->getNext()->setPrev(node);
                    node->setNext(cur->getNext());
                    cur->setNext(node);
                    node->setPrev(cur);
                    count++;
                }
            }
        }
        void deleteFront(){
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
                count--;
            }
        }
        void deleteRear(){
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
                count--;
            }
        }
        void deleteMiddle(){
            if(!IsEmpty()){
                int mid = (count+1) / 2;
                Node<T> *cur = head;
                int temp = 1;
                while(temp<mid){
                    cur = cur->getNext();
                    temp++;
                }
                if(count>1){
                    cur->getPrev()->setNext(cur->getNext());
                    cur->getNext()->setPrev(cur->getPrev());
                }
                cur->setPrev(NULL);
                cur->setNext(NULL);
                count--;
                if(count==0){
                    head = NULL;
                    tail = NULL;
                }
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
        int count;
};

int main(){
    TEQ<int> *q = new TEQ<int>();
    q->addRear(1);
    q->addFront(4);
    q->addMiddle(6);
    q->print();
    q->deleteRear();
    q->print();
    q->deleteFront();
    q->print();
    q->deleteMiddle();
    q->print();
    q->addMiddle(7);
    q->addMiddle(8);
    q->addMiddle(9);
    q->print();
    return 0;
}
