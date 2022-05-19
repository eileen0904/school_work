#include <bits/stdc++.h>
using namespace std;
#define N 100

struct Node{
    int v, len, rl, sl;
    int road[N];
    Node(int _v = 0, int _len = 0, int _rl = 0){
        v = _v;
        len = _len;
        rl = _rl;
    }
    bool operator <(const Node &n1) const{
        return this->sl > n1.sl;
    }
};

int G[N][N];
int best_road[N], minlen[N];
int n, m, best_len, mintotal;

void init(){
    for(int i=0; i <= n; i++){
        minlen[i] = INT_MAX;
        for(int j=0; j <= n; j++){
            G[i][j] = INT_MAX;
        }
    }
}

void bfs(int start){
    priority_queue<Node> pq;
    Node newNode;
    for(int i = 1; i <= n; i++){
        newNode.road[i] = i;
    }
    newNode.v = 2;
    newNode.len = 0;
    newNode.rl = mintotal;
    newNode.sl = mintotal;
    pq.push(newNode);
    while(!pq.empty()){
        Node cur = pq.top();
        pq.pop();
        int floor = cur.v;
        if(cur.v == n + 1){
            if(G[cur.road[floor - 1]][start] != INT_MAX){
                best_len = cur.len + G[cur.road[floor - 1]][start];
                for(int i=1; i <= n; i++){
                    best_road[i] = cur.road[i];
                }
                best_road[n + 1] = start;
                return;
            }
        }
        for(int i=floor; i <= n; i++){
            if(G[cur.road[floor - 1]][cur.road[i]] != INT_MAX && cur.sl < best_len){
                newNode.v = floor + 1;
                newNode.len = cur.len + G[cur.road[floor - 1]][cur.road[i]];
                newNode.rl = newNode.rl - minlen[cur.road[i]];
                newNode.sl = newNode.rl + newNode.len;
                for(int j=1; j <=n; j++){
                    newNode.road[j] = cur.road[j];
                }
                swap(newNode.road[i], newNode.road[floor]);
                pq.push(newNode);
            }
        }
    }
}

int main(){
    int u, v, w;
    cout << "Enter the number of vertex: " << endl;
    cin >> n;
    cout << "Enter the number of edge: " << endl;
    cin >> m;
    init();
    cout << "Enter the vertex vertex weight: " << endl;
    for(int i=0; i < m; i++){
        cin >> u >> v >> w;
        G[u][v] = w;
        minlen[u] = min(minlen[u], G[u][v]);
    }
    for(int i=1; i <= n; i++){
        mintotal = mintotal + minlen[i];
    }
    best_len = INT_MAX;
    bfs(1);
    cout << "The optimal path: " << endl;
    for(int i=1; i <= n ;i++){
        cout << best_road[i] << " --> ";
    }
    cout << "1" << endl;
    cout << "The optimal length: " << best_len << endl;
}

/*
vertex = 8
edge = 14
1 2 5
2 3 4
3 4 2
4 8 7
8 7 4
7 6 8
6 5 2
5 1 1
1 3 8
2 5 4
7 4 3
8 6 5
6 2 6
3 7 5
*/