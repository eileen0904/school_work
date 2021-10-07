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

class Queue
{
public:
	Queue()
	{
        top = NULL;
        bot = NULL;
	}
	int enqueue(int data)
	{
        Node *node = new Node();
        node->data = data;
        node->next = NULL;
        if(top==NULL){
            top = node;
            bot = node;
            return 1;
        }
        else{
            bot->next = node;
            bot = node;
            return 1;
        }
	}
	int *dequeue()
	{
        if(top==NULL){return NULL;}
        Node *temp = top;
        top = top->next;
        if(top==NULL){
            bot = NULL;
        }
        return &(temp->data);
	}
private:
	Node *top, *bot;
};

int main()
{
	int data, *temp;
	string command;
	Queue *queue = new Queue();
	while(1)
	{
		cin>>command;
		if(command.compare("exit") == 0)
		{
			break;
		}
		else if(command.compare("enqueue") == 0)
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
		else if(command.compare("dequeue") == 0) 
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
