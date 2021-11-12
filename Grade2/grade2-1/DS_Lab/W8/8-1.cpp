#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>

using namespace std;

class Node
{
public:
	int level, data;
	Node *left, *right;
};

class Tree
{
public:
	Tree()
	{
		root = NULL;
	}
	int insert(Node *n)
	{
		insert(&root, n, 0);
	}
	void inorder() //left->root->right
	{
        if(root==NULL){return;}
        inorder(root->left);
        cout<<root->data<<"  "<<root->level<<endl;
        inorder(root->right);
	}
	void preorder() //root->left->right
	{
        if(root==NULL){return;}
        cout<<root->data<<"  "<<root->level<<endl;
        preorder(root->left);
        preorder(root->right);
	}
	void postorder() //left->right->root
	{
        if(root==NULL){return;}
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<"  "<<root->level<<endl;
	}
	void levelorder()
	{
        if(root==NULL){return;}
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node *n = q.front();
            q.pop();
            cout<<n->data<<"  "<<n->level<<endl;
            if(n->left){
                q.push(n->left);
            }
            if(n->right){
                q.push(n->right);
            }
        }
	}
private:
	Node *root;
	void insert(Node **r, Node *n, int lev)
	{
		if(*r == NULL){
            n->level = lev;
			*r = n;
		}
		else if(n->data > (*r)->data)
			insert(&((*r)->right), n, lev+1);
		else
			insert(&((*r)->left), n, lev+1);
	}
    void preorder(Node *r){
        if(r==NULL){return;}
        cout<<r->data<<"  "<<r->level<<endl;
        preorder(r->left);
        preorder(r->right);
    }
    void inorder(Node *r){
        if(r==NULL){return;}
        inorder(r->left);
        cout<<r->data<<"  "<<r->level<<endl;
        inorder(r->right);
    }
    void postorder(Node *r){
        if(r==NULL){return;}
        postorder(r->left);
        postorder(r->right);
        cout<<r->data<<"  "<<r->level<<endl;
    }
};

int main()
{
	Tree *tree = new Tree();
	Node *node;
	int j;
	srand(time(NULL));
	for(j = 0;j < 10;j ++)
	{
		node = new Node();
		node->data = rand()%10;
		node->left = NULL;
		node->right = NULL;
		tree->insert(node);
	}
	tree->inorder();
	printf("\n");
	tree->preorder();
	printf("\n");
	tree->postorder();
	printf("\n");
	tree->levelorder();
	printf("\n");
}
