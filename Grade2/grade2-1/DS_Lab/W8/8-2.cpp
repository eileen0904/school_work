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
		int j, k;
		for(j = 0;j < 20;j ++)
			for(k = 0;k < 4;k ++)
				root[j][k] = -1;
	}
	int insert(int node)
	{
		int f = 0, index = 0;
		while(root[index][0] != -1)
			index ++;
		if(index >= 20)
			return -1;
		if(index == 0)
		{
			root[0][0] = 1;
			root[0][1] = node;
			return 1;
		}
		else
		{
			root[index][0] = 1;
			root[index][1] = node;
			while(1)
			{
				if(root[f][1] < node)
				{
					if(root[f][3] == -1)
					{
						root[f][3] = index;
						return 1;
					}
					else
					{
						f = root[f][3];
					}
				}
				else
				{
					if(root[f][2] == -1)
					{
						root[f][2] = index;
						return 1;
					}
					else
					{
						f = root[f][2];
					}
				}
			}
		}
	}
	void inorder() //left->root->right
	{
		int cur=0;
		if(root[cur][0]==-1){return;}
		inorder(root[cur][2]);
		cout<<root[cur][1]<<" ";
		inorder(root[cur][3]);
	}
	void preorder() //root->left->right
	{
		int cur=0;
		if(root[cur][0]==-1){return;}
		cout<<root[cur][1]<<" ";
		preorder(root[cur][2]);
		preorder(root[cur][3]);
	}
	void postorder() //left->right->root
	{
		int cur=0;
		if(root[cur][0]==-1){return;}
		postorder(root[cur][2]);
		postorder(root[cur][3]);
		cout<<root[cur][1]<<" ";
	}
	void levelorder()
	{
		if(root[0][0]==-1){return;}
		queue<int> q;
		q.push(0);
		while(!q.empty()){
            int pos = q.front();
            q.pop();
            cout<<root[pos][1]<<" ";
            if(root[pos][2]!=-1){
                q.push(root[pos][2]);
            }
            if(root[pos][3]!=-1){
                q.push(root[pos][3]);
            }
        }
	}
private:
	int root[20][4];
	//[0]:exist data->1 or ->-1
	//[1]:data
	//[2]:left position
	//[3]:right position
	void inorder(int cur){
		if(cur==-1){return;}
		inorder(root[cur][2]);
		cout<<root[cur][1]<<" ";
		inorder(root[cur][3]);
	}
	void preorder(int cur){
		if(cur==-1){return;}
		cout<<root[cur][1]<<" ";
		preorder(root[cur][2]);
		preorder(root[cur][3]);
	}
	void postorder(int cur){
		if(cur==-1){return;}
		postorder(root[cur][2]);
		postorder(root[cur][3]);
		cout<<root[cur][1]<<" ";
	}
	void levelorder(int cur){}
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
