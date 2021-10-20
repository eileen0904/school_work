#include<iostream>
#include<cstdlib>

using namespace std;

struct Node
{
	Node()
	{
		data = 0;
		next = NULL;
	}
	int data;
	Node *next;
};

class Set
{
public:
	Set()
	{
        count = 0;
        top = NULL;
        bot = NULL;
	}

	int addElement(int e)
	{
        Node *node = new Node();
        if(node==NULL){
            return false;
        }
        if(count==0){
            node->data = e;
            top = node;
            bot = node;
            count++;
            return true;
        }
        Node *temp = top;
        for(int i=0;i<count;i++){
            if(temp->data==e){return false;}
            temp = temp->next;
        }
        node->data = e;
        bot->next = node;
        bot = node;
        count++;
        return true;
	}

	Set *unions(const Set *b) const
	{
        Set *us = new Set();
        Node *cur1 = top;
        Node *cur2 = b->top;
        for(cur1; cur1!=NULL; cur1=cur1->next){
            us->addElement(cur1->data);
        }
        for(cur2; cur2!=NULL; cur2=cur2->next){
            us->addElement(cur2->data);
        }
        return us;
	}

	Set *intersections(const Set *b) const
	{
        Set *is = new Set();
        Node *cur1 = top;
        while(cur1!=NULL){
            Node *cur2 = b->top;
            while(cur2!=NULL){
                if(cur1->data==cur2->data){
                    is->addElement(cur1->data);
                }
                cur2 = cur2->next;
            }
            cur1 = cur1->next;
        }
        return is;
	}

	bool equivalent(const Set *b) const
	{
        int same=0;
        for(Node *cur1 = b->top; cur1!=NULL; cur1 = cur1->next){
            for(Node *cur2 = this->top; cur2!=NULL; cur2 = cur2->next){
                if(cur1->data==cur2->data){
                    same++;
                }
            }
        }
        if(this->count==b->count && same==b->count){return true;}
        return false;
	}

	void listAll() const
	{
		Node *cur = this->top;
		while(cur != NULL)
		{
			cout<<cur->data<<" ";
			cur = cur->next;
		}
	}
private:
    Node *top, *bot;
    int count;
};

int main()
{
	Set *a = new Set();
	Set *b = new Set();
	Set *c;

	a->addElement(1);
	a->addElement(2);
	a->addElement(3);
    a->listAll();

	b->addElement(3);
	b->addElement(4);
	b->addElement(5);
    b->addElement(5);
	b->listAll();

	c = a->unions(b);
	c->listAll();

	c = a->intersections(b);
	c->listAll();

	if(a->equivalent(b) == 0)
		cout<<"Not equivalent.\n";
	else
		cout<<"Equivalent!\n";
}
