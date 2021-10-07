#include <iostream>
#include <string>

#define SIZE 100

using namespace std;

class Node
{
public:
	int data;
	Node *next;
};

class Stack
{
public:
    Stack()
    {
        top = NULL;
    }
    int push(int d)
    {
        Node *node = new Node();
        node->data = d;
        node->next = top; //Point next at current top.
        top = node; //Assign top as the new node recently created.
        return 1;
    }

    int *pop()
    {
        if(top==NULL){return NULL;}
        Node *temp = top;
        top = top->next;
        return &(temp->data);
    }
private:
    Node *top;
};

int main()
{
    int data, *temp;
    string command;
    Stack *stack = new Stack();
    while(1)
    {
        cin>>command;
        if(command.compare("exit") == 0)
        {
            break;
        }
        else if(command.compare("push") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(stack->push(data) == 1)
            {
                cout<<"Successfully push data "<<data<<" into stack."<<endl;
            }
            else
            {
                cout<<"Failed to push data into stack.\n";
            }
        }
        else if(command.compare("pop") == 0)
        {
            temp = stack->pop();
            if(temp == NULL)
            {
                cout<<"Failed to pop a data from stack.\n";
            }
            else
            {
                cout<<"Pop data "<<*temp<<" from stack"<<endl;
            }
        }
    }
}

