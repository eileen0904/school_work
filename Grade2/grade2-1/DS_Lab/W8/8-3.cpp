#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>

using namespace std;

class Tree
{
public:
	Tree()
	{
		int j;
		for(j = 0;j < 2000;j ++)
			root[j] = -1;
	}
	int insert(int node)
	{
		int index = 0;
		while(index < 2000 && root[index] != -1)
		{
			if(root[index] < node)
				index = index * 2 + 2; //right
			else
				index = index * 2 + 1; //left
		}
		root[index] = node;
	}
	void inorder() //left->root->right
	{
		int cur=0;
		if(root[cur]==-1){return;}
		inorder(cur*2+1);
		cout<<root[cur]<<" ";
		inorder(cur*2+2);
	}
	void preorder() //root->left->right
	{
        int cur=0;
		if(root[cur]==-1){return;}
        cout<<root[cur]<<" ";
		preorder(cur*2+1);
		preorder(cur*2+2);
	}
	void postorder() //left->right->root
	{
        int cur=0;
		if(root[cur]==-1){return;}
		postorder(cur*2+1);
		postorder(cur*2+2);
        cout<<root[cur]<<" ";
	}
	void levelorder()
	{
		if(root[0]==-1){return;}
		queue<int> q;
		q.push(0);
		while(!q.empty()){
            int pos = q.front();
            q.pop();
            cout<<root[pos]<<" ";
            if(root[pos*2+1]!=-1){
                q.push(pos*2+1);
            }
            if(root[pos*2+2]!=-1){
                q.push(pos*2+2);
            }
        }
	}
private:
	int root[2000];
    void inorder(int cur)
	{
		if(root[cur]==-1){return;}
		inorder(cur*2+1);
		cout<<root[cur]<<" ";
		inorder(cur*2+2);
	}
    void preorder(int cur)
	{
		if(root[cur]==-1){return;}
        cout<<root[cur]<<" ";
		preorder(cur*2+1);
		preorder(cur*2+2);
	}
    void postorder(int cur)
	{
		if(root[cur]==-1){return;}
		postorder(cur*2+1);
		postorder(cur*2+2);
        cout<<root[cur]<<" ";
	}
};

int main()
{
	Tree *tree = new Tree();
	int j, node;
	srand(time(NULL));
	for(j = 0;j < 10;j ++)
	{
		node = rand();
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
