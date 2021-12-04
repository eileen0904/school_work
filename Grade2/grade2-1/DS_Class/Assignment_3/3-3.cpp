#ifndef _IOSTREAM_H
#include <iostream>
#include <queue>
#define _IOSTREAM_H
#endif
using namespace std;

enum Boolean { FALSE, TRUE};

class Tree;

class TreeNode {
friend class Tree;
friend int equal(TreeNode*, TreeNode*);
private:
    TreeNode *LeftChild;
    int data;
    TreeNode *RightChild;
    TreeNode() {LeftChild = RightChild = 0;};
    TreeNode(int d, TreeNode *Lefty, TreeNode *Righty)
    {
	data = d;
	LeftChild = Lefty;
	RightChild = Righty;
    }
};

class Tree {
friend int operator==(const Tree&, const Tree&);
private:
    TreeNode *root;
    void inorder(TreeNode *);
    void preorder(TreeNode *);
    void postorder(TreeNode *);
    TreeNode* copy(TreeNode *);
public:
    void setup(){
        root = new TreeNode(1,0,0);
        root->LeftChild = new TreeNode(2,0,0);
        root->LeftChild->LeftChild = new TreeNode(3, 0, 0);
        root->LeftChild->RightChild = new TreeNode(4, 0, 0);
        root->LeftChild->LeftChild->LeftChild = new TreeNode(5, 0, 0);
    }
    void inorder(){
        inorder(root);
    }
    void preorder(){
        preorder(root);
    }
    void postorder(){
        postorder(root);
    }
    int size(){
        if(root==NULL) return 0;
        queue<TreeNode*> q;
        int count = 0;
        q.push(root);
        while(!q.empty()){
            TreeNode *n = q.front();
            q.pop();
            count++;
            if(n->LeftChild){
                q.push(n->LeftChild);
            }
            if(n->RightChild){
                q.push(n->RightChild);
            }
        }
        return count;
    }
    int height(){ 
        if(root==NULL) return 0;
        queue<TreeNode*> q;
        int depth = 0;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
            TreeNode *temp = q.front();
            q.pop();
            if(temp==NULL) depth++;
            if(temp!=NULL){
                if(temp->LeftChild){
                    q.push(temp->LeftChild);
                }
                if(temp->RightChild){
                    q.push(temp->RightChild);
                }
            }
            else if(!q.empty()) q.push(NULL);
        }
        return depth;
    }
    int sum(){
        if(root==NULL) return 0;
        queue<TreeNode*> q;
        int total = 0;
        q.push(root);
        while(!q.empty()){
            TreeNode *n = q.front();
            q.pop();
            total = total + n->data;
            if(n->LeftChild){
                q.push(n->LeftChild);
            }
            if(n->RightChild){
                q.push(n->RightChild);
            }
        }
        return total;
    }
    Tree(const Tree&);
    Tree() {root = 0;};
};

void Tree::inorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 inorder(CurrentNode->LeftChild);
	 cout << CurrentNode->data;
	 inorder(CurrentNode->RightChild);
     }
}

void Tree::preorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 cout << CurrentNode->data;
	 preorder(CurrentNode->LeftChild);
	 preorder(CurrentNode->RightChild);
     }
}

void Tree::postorder(TreeNode *CurrentNode)
{
     if (CurrentNode) {
	 postorder(CurrentNode->LeftChild);
	 postorder(CurrentNode->RightChild);
	 cout << CurrentNode->data;
     }
}

Tree::Tree(const Tree& s)
{
  root = copy(s.root);
}

TreeNode* Tree::copy(TreeNode *orignode)
{
  if (orignode) {
      TreeNode *temp = new TreeNode;
      temp->data = orignode->data;
      temp->LeftChild = copy(orignode->LeftChild);
      temp->RightChild = copy(orignode->RightChild);
      return temp;
  }
  else return 0;
}

// Driver
int operator==(const Tree& s, const Tree& t){
   return equal(s.root, t.root);
}

// Workhorse
int equal(TreeNode *a, TreeNode *b)
/* This function returns 0 if the subtrees at @a@ and @b@ are not
   equivalent. Otherwise, it will return 1 */
{
 if ((!a) && (!b)) return 1;  // both @a@ and @b@ are 0
 if (a && b &&                // both @a@ and @b@ are non-0
    (a->data == b->data)      // @data@ is the same
    && equal(a->LeftChild, b->LeftChild) // left subtrees are the same
    && equal(a->RightChild, b->RightChild) ) // right subtrees are the same
       return 1;
 return 0;
}

int main()
{
Tree t;
t.setup();
Tree s = t;
s.inorder();
cout << endl;
if (s == t) cout << 1; 
else cout << 0;
cout << endl;
int size = t.size();
cout<<"Size: "<<size<<endl;
int height = t.height();
cout<<"Height: "<<height<<endl;
int sum = t.sum();
cout<<"Sum: "<<sum<<endl;

return 0;
}

