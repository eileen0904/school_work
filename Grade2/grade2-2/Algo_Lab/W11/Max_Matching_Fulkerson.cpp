#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 1e4 + 5;

struct Edge {
    int to, cap, rev; //rev:反向邊
    Edge(int _to, int _cap, int _rev): to(_to), cap(_cap), rev(_rev) {}
};

vector<Edge> G[MAX_V]; //adjacent list
bool used[MAX_V];

void add_edge(int from, int to, int cap) {
    G[from].push_back(Edge(to, cap, G[to].size()));
    //cout <<"to  " <<"G["<< to <<"].size: " << G[to].size() << endl;
    G[to].push_back(Edge(from, 0, G[from].size() - 1));
    //cout << "from  "<<"G["<< from <<"].size: " << G[from].size() << endl;
}

void print(){
    for(int cur=0; cur < 8; cur++){
        for(int i=0; i < G[cur].size(); i++){
            Edge e = G[cur][i];
            cout <<"V" << cur << ": " << e.to << " " << e.cap << " " << e.rev << endl;
        }
    }
}

//f:當前路徑中的容量最小值
int dfs(int cur, int T, int f) {
    if (cur == T) {
        return f;
    }
    used[cur] = true;
    for (int i = 0; i < G[cur].size(); i++) {
        Edge &e = G[cur][i];
        if (!used[e.to] && e.cap > 0) {
            int d = dfs(e.to, T, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int main() {
    // A, B, C 為節點 0, 1, 2
    // X, Y, Z 為節點 3, 4, 5
    // S, T 為節點 6, 7
    add_edge(0, 1, 1);
    add_edge(0, 2, 1);
    add_edge(0, 3, 1);

    add_edge(1, 4, 1);
    add_edge(1, 5, 1);
    add_edge(2, 4, 1);
    add_edge(2, 6, 1);
    add_edge(3, 5, 1);

    add_edge(4, 7, 1);
    add_edge(5, 7, 1);
    add_edge(6, 7, 1);
    print();
    //求最大流
    int flow = 0;
    while(1){
        memset(used, 0, sizeof(used));
        int f = dfs(0, 7, 1);
        if (f == 0) {
            cout << flow << endl;
            break;
        }
        flow += f;
    }
}