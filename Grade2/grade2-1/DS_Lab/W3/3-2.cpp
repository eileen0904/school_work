#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Queue
{
public:
    Queue()
    {
        head = -1;
        tail = -1;
        flag == false;
    }
    bool empty(){
        if(head==tail && flag==false){return true;}
        return false;
    }
    bool full(){
        if(tail%SIZE==head && flag==true){return true;}
        return false;
    }
    int enqueue(int data)
    {
        if((full()) || (tail==(SIZE-1) && head==-1)){return -1;}
        tail = (tail+1) % SIZE;
        this->data[tail] = data;
        if(tail==head){flag = true;} //second full
        return 1;
    }
    int *dequeue()
    {
        if(empty()){return NULL;}
        head = (head+1) % SIZE;
        if(head==tail){flag = false;}
        return &(this->data[head]);
    }
private:
    int data[SIZE];
    int head;
    int tail;
    bool flag;
};

int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while(1)
    {
        cin>>command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(queue->enqueue(data) == 1)
            {
                cout<<"Successfully enqueue data "<<data<<" into queue."<<endl;
            }
            else
            {
                cout<<"Failed to enqueue data into queue."<<endl;
            }
        }
        else if(strcmp(command, "dequeue") == 0) 
        {
            temp = queue->dequeue();
            if(temp == NULL)
            {
                cout<<"Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout<<"Dequeue data "<<*temp<<" from queue."<<endl;
            }
        }
    }
}