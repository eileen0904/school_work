/*UVa890 Maze*/

#include<iostream>
#include <string.h>
#include <stack>
#include <queue>
using namespace std;

stack<int> X, Y;
queue<int> qx, qy;
int maze[40][4][40];
int visited[40][40];
int check(int r, int c){
    int i, tx, ty;
    int dx[] = {1, -1, 0, 0}; //上下左右
    int dy[] = {0, 0, -1, 1};
    if(X.empty()){
        return 0;
    }
    for(i=0;i<4;i++){  //check unvisited
        tx = X.top() + dx[i];
        ty = Y.top() + dy[i];
        if(tx<0 || ty<0 || tx>=r || ty>=c){
            continue;
        }
        if(visited[tx][ty]==0){
            return 0;
        }
    }
    return 1;
}
void output(int r, int c){
    for(int i=0;i<c;i++){
        cout<<" ";
        cout<<"_";
    }
    cout<<endl;
    for(int i=r-1;i>=0;i--){
        cout<<"|";
        for(int j=0;j<c;j++){
            if(maze[i][3][j]==1){
                cout<<"_";
            }
            if(maze[i][3][j]==0){
                cout<<" ";
            }
            if(maze[i][2][j]==1){
                cout<<"|";
            }
            if(maze[i][2][j]==0){
                cout<<" ";
            }
        }
        cout<<endl;
    }
}

int main(){
    int a, temp=0;
    cin>>a;
    while(temp<a){
        int n=0, m=0, i, j, sx=0, sy=0;
        cin>>n>>m;
        cin>>sx>>sy;
        sx--;
        sy--;
        memset(visited, 0, sizeof(visited));
        X.push(sx); 
        Y.push(sy);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                maze[i][0][j] = maze[i][1][j] = maze[i][2][j] = maze[i][3][j] = 1; //all 1
            }
        }
        visited[sx][sy] = 1;
        char path[10];
        int dir=0, dx=0, dy=0, f=0;
        while(!X.empty()){
            cin>>path[0];
            if(path[0]=='F'){
                cin>>f;
                int flip = X.size()-f+1;
                for(i=0;i<flip;i++){
                    qx.push(X.top());
                    qy.push(Y.top());
                    X.pop(); 
                    Y.pop();
                }
                while(!qx.empty()) {
                    X.push(qx.front());
                    Y.push(qy.front());
                    qx.pop();
                    qy.pop();
                } 
            }
            else{
                if(path[0] == 'U') {dir = 0, dx = 1, dy = 0;}
                if(path[0] == 'D') {dir = 3, dx = -1, dy = 0;}
                if(path[0] == 'L') {dir = 1, dx = 0, dy = -1;}
                if(path[0] == 'R') {dir = 2, dx = 0, dy = 1;}
                int tx, ty; 
                tx = X.top() + dx;
                ty = Y.top() + dy;
                if(tx>=0 && tx<n && ty>=0 && ty<m){
                    if(visited[tx][ty]==0){
                        maze[X.top()][dir][Y.top()] = 0; //last one
                        maze[tx][3-dir][ty] = 0; //now
                        visited[tx][ty] = 1;
                        X.push(tx);
                        Y.push(ty);
                    }
                }
            }
            while(check(n, m)){
                X.pop(); 
                Y.pop();
            }
        }
        output(n, m);
        cout<<endl;
        temp++;
    }
    return 0;
}