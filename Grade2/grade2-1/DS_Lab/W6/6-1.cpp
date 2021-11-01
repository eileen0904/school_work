#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 10

using namespace std;

class Node
{
public:
	Node(): Node(0, 0){}
	Node(int r, int c)
	{
		row = r;
		col = c;
	}
	int getRow() const { return row; }
	int getCol() const { return col; }
	void setRow(int r){
		if(r >= 0 && r < SIZE)
			row = r;
	}
	void setCol(int c){
		if(c >= 0 && c < SIZE)
			col = c;
	}
private:
	int col, row;
};

class List
{
public:
	List(){
		top = 0;
	}
	/*
	function addElement
	Insert an element into list
	*/
	void addElement(int r, int c)
	{
        data[top].setRow(r);
        data[top].setCol(c);
        top++;
	}
	/*
	function removeElement
	remove an element from list and return a pointer point to the element.
	If list is empty, return NULL.
	*/
	Node *removeElement()
	{
        if(top==0){return NULL;}
        top--;
        return &data[top+1];
	}
	void printList()
	{
		int j;
		for(j=top;j>=0;j--){
			cout<<"("<<data[j].getRow()<<", "<<data[j].getCol()<<")"<<endl;
		}
	}
    int getTop(){return top;}
private:
	Node data[SIZE * SIZE];
	int top;
};

class Maze
{
public:
	Maze(){
		initMaze(SIZE);
	}
	/*
	function initMaze
	Alocate a 2-D array with s * s sizes as the map of maze.
	Inside the maze where 0 represent empty space and 1 represent wall.
	[0][0] is start point and [s - 1][s - 1] is finish point.
	Randomly generate 20% wall in the maze.
	Make sure [0][0] and [s - 1][s - 1] are 0

	動態配置一個二維的陣列，大小是 s * s ，用這個陣列表示迷宮的地圖
	陣列中 0 的值表示可以移動的空間， 1 表示牆壁
	[0][0] 的位置表示起點 [s - 1][s - 1] 的位置表示終點
	請在迷宮中加入20% 的牆壁
	然後確定起點跟終點都是可以移動的位置
	*/
	void initMaze(int s)
	{
        maze = new int *[s];
        int *row = new int [s*s];
        for(int i=0;i<s;i++){
            maze[i] = row + i*s;
        }
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                maze[i][j] = 0;
            }
        }
        maze[0][0] = -1;
        maze[s-1][s-1] = -1;
        int count=0;
        while(1){
            int random_r = rand()%10;
            int random_c = rand()%10;
            if(maze[random_r][random_c]==0){
                maze[random_r][random_c] = 1;
                count++;
            }
            if(count==20){break;}
        }
        maze[0][0] = 0;
        maze[s-1][s-1] = 0;
	}
	/*
	function getPath
	This function will find a path between start point and finish point.
	Return a list content the path information inside.
	If there is no path between two point then the list will be empty.

	這個函數會找到起點到終點間的一條路徑
	回傳一個 list， List 包含路徑的資訊
	如果找不到路徑的話 list 就會是空的
	*/
	List *getPath()
	{
        move(0,0);
        if(list->getTop()==0){return NULL;}
        return list;
	}
    void move(int x, int y){
        if(x==SIZE-1 && y==SIZE-1){
            list->addElement(x,y);
            flag = false; //don't backtracking
            return;
        }
        int dirx[4] = {0, 1, 0, -1}; //right,down,left,up
        int diry[4] = {1, 0, -1, 0};
        for(int i=0;i<4;i++){
            int nx = x + dirx[i];
            int ny = y + diry[i];
            if(nx>=0 && nx<=SIZE-1 && ny>=0 && ny<=SIZE-1 && maze[nx][ny]==0){
                maze[x][y] = 2;
                move(nx,ny);
                if(flag){
                    maze[x][y] = 0;
                }
                if(flag==false){break;}
            }
        }
        if(flag==false){
            list->addElement(x,y);
        }
        return;
    }
	void printMaze()
	{
		int j, k;
		for(j = 0;j < SIZE;j ++){
			for(k = 0;k < SIZE;k ++){
				if(maze[j][k] == 0)
					cout<<" ";
				else if(maze[j][k] == 1)
					cout<<"*";
			}
			cout<<"\n";
		}
	}
private:
	int **maze;
    List *list = new List();
    bool flag = true;
};

int main()
{
	srand(time(NULL));
	Maze *maze = new Maze();
	maze->printMaze();
	maze->getPath()->printList();
}
