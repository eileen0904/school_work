#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid
{
public:
	Grid(): Grid(0){}
	Grid(int s)
	{
		state = s;
		dir[UP] = NULL;
		dir[DOWN] = NULL;
		dir[LEFT] = NULL;
		dir[RIGHT] = NULL;
	}
	Grid *getDir(int d) const { return dir[d]; }
	int getState() const {return state;}
	void setDir(int d, Grid *g) { dir[d] = g; }
	void setState(int s) { state = s;}
private:
	Grid *dir[4];
	int state;
};

class List
{
public:
	List(){
		top = 0;
	}
	/*
	Insert an element from top
	*/
	void addElement(Grid *g)
	{
		data[top] = g;
		top++;
	}
	/*
	remove an element from top and return a pointer point to the element.
	If list is empty, return NULL.
	*/
	Grid *removeElement()
	{
		if(top==NULL){return NULL;}
		top--;
		return data[top+1];
	}
	void printPath() const
	{
		int j;
		for(j=top-1;j>0;j--){
			if(data[j-1] == data[j]->getDir(UP)){
				cout<<"UP\n";
			}
			else if(data[j-1] == data[j]->getDir(DOWN)){
				cout<<"DOWN\n";
			}
			else if(data[j-1] == data[j]->getDir(LEFT)){
				cout<<"LEFT\n";
			}
			else if(data[j-1] == data[j]->getDir(RIGHT)){
				cout<<"RIGHT\n";
			}
		}
	}
	int getTop(){return top;}
private:
	Grid *data[SIZE * SIZE];
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
	Alocate a 2-D link list with s * s sizes as the map of maze.
	Inside the maze enery gird with state 0 represent empty space and 1 represent wall.
	The gird in left top is start point and right bottom is finish point.
	Randomly generate 20% wall in the maze.
	Make sure start point and finish point are 0

	動態配置一個二維的鏈結串列，大小是 s * s，用這個鏈結串列表示迷宮的地圖
	節點中 0 的值表示可以移動的空間， 1 表示牆壁
	左上角的位置表示起點，右下角的位置表示終點
	請在迷宮中加入 20% 的牆壁
	然後確定起點跟終點都是可以移動的位置
	*/
	void initMaze(int s)
	{
		Grid *head = new Grid();
		Grid *cur = head, *temp = head, *left = head, *up = head, *end;
		for(int i=0;i<s;i++){
			for(int j=0;j<s;j++){
				if(j<s-1){
					if(i==0){
						cur->setDir(RIGHT, new Grid());
					}
					else{
						cur->setDir(RIGHT,((up->getDir(RIGHT))->getDir(DOWN)));
						//match to correspond memory
					}
				}
				if(i<s-1){
					cur->setDir(DOWN, new Grid());
				}
				if(j>0){
					cur->setDir(LEFT, left);
					left = left->getDir(RIGHT);
				}
				if(i>0){
					cur->setDir(UP, up);
					up = up->getDir(RIGHT);
				}
				cur->setState(0);
				if(i==s-1 && j==s-1){
                    end = cur;
				}
				cur = cur->getDir(RIGHT);
			}
			if(i>=1){
				up = temp;
			}
			temp = temp->getDir(DOWN);
			cur = temp;
			left = temp;
		}
		end->setState(-1);
		head->setState(-1);
		temp = head;
		int count=0;
		for(int i=0;i<s;i++){
            cur = temp;
            for(int j=0;j<s;j++){
                int random = rand()%100;
                if(random<=20 && cur->getState()==0){
                    cur->setState(1);
                    cur = cur->getDir(RIGHT);
                    count++;
                }
                if(count>=(s*s*0.2)){break;}
            }
            temp = temp->getDir(DOWN);
            if(count>=(s*s*0.2)){break;}
		}
		head->setState(0);
		end->setState(0);
		maze = head;
	}
	/*
	function getPath
	This function will find a path between start point and finish point.
	Return a list content the path information inside.
	If there is no path between two point then the list will be empty.

	這個函數會找到起點到終點間的一條路徑
	回傳一個 list 包含著路徑的資訊
	如果找不到路徑的話 list 就會是空的
	*/
	List *getPath()
	{
		move(maze);
        if(list->getTop()==0){return NULL;}
        return list;
	}
	void move(Grid *m){
        if(m->getDir(RIGHT)==NULL && m->getDir(DOWN)==NULL){
            list->addElement(m);
            flag = false; //don't backtracking
            return;
        }
        int dir[4] = {UP, DOWN, LEFT, RIGHT}; //0,1,2,3
        for(int i=0;i<4;i++){
            int next = dir[i];
            if(m->getDir(next)!=NULL && m->getDir(next)->getState()==0){
                m->setState(2);
                move(m->getDir(next));
                if(flag){
                    m->setState(0);
                }
                if(flag==false){break;}
            }
        }
        if(flag==false){
            list->addElement(m);
        }
        return;
    }
	void printMaze() const
	{
		Grid *j = maze, *k;
		while(j != NULL)
		{
			k = j;
			while(k != NULL)
			{
				cout<<k->getState();
				k = k->getDir(RIGHT);
			}
			cout<<endl;
			j = j->getDir(DOWN);
		}
	}
private:
	Grid *maze;
	List *list = new List();
    bool flag = true;
};

int main()
{
	srand(time(NULL));
	Maze *maze = new Maze();
	maze->printMaze();
	maze->getPath()->printPath();
}
