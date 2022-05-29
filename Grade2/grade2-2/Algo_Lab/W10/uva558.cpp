#include <bits/stdc++.h>
using namespace std;

#define MAX 100000000
struct Edge{
    int s, t, w;
};

int n, m;
Edge E[2005];
long long dis[1005];

bool Bellman(){
    dis[0] = 0;
    for(int i = 1; i < n; i++){
        dis[i] = MAX;
    }
    for(int i=0; i < n - 1; i++){
        for(int j=0; j < m; j++){
            int u = E[j].s;
            int v = E[j].t;
            if(dis[u] > dis[v] + E[j].w){
                dis[u] = dis[v] + E[j].w;
            }
        }
    }
    for(int i=0; i < m; i++){
        if(dis[E[i].s] > dis[E[i].t] + E[i].w){
            return true;  //has negative cycle
        }
    }
    return false;
}
int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        cin >> n >> m;
        int u, v, w;
        for(int i=0; i < m; i++){
            cin >> u >> v >> w;
            E[i].s = u;
            E[i].t = v;
            E[i].w = w;
        }
        if(Bellman()) cout << "possible" << endl;
        else cout << "not possible" << endl;
    }
}