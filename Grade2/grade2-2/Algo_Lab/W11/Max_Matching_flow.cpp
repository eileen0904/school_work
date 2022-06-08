#include <bits/stdc++.h>
using namespace std;
const int INF = 100;
const int N = 20;

vector<int> edge[N];
int cap[N][N], flow[N][N], pre[N];
int cost[N][N], dis[N];
int n, m, E, S, T;

void init(){
    for(int i = S; i <= T; i++){
        edge[i].clear();
    }
    memset(cap, 0, sizeof(cap));
    memset(flow, 0, sizeof(flow));
    memset(cost, 0, sizeof(cost));
}

bool SPFA(){
    for(int i=0; i < N; i++){
        dis[i] = INF;
    }
    queue<int> Q;
    bool inQ[N] = {false};
    dis[S] = 0;
    Q.push(S);
    inQ[S] = true;

    while(!Q.empty()){
        int cur = Q.front();
        inQ[cur] = false;
        Q.pop();

        vector<int>::iterator it;
        for(it = edge[cur].begin(); it != edge[cur].end(); it++){
            int v = *it;
            if(flow[v][cur] > 0 && dis[cur] - cost[v][cur] < dis[v]){
                dis[v] = dis[cur] - cost[v][cur];
                pre[v] = cur;
                if(!inQ[v]){
                    inQ[v] = true; 
                    Q.push(v);
                }
            }
            else if(cap[cur][v] > flow[cur][v] && dis[cur] + cost[cur][v] < dis[v]){
                dis[v] = dis[cur] + cost[cur][v];
                pre[v] = cur;
                if(!inQ[v]){
                    inQ[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    if(dis[T] == INF) return false;
    else return true;
}

void UpdateFlow(int bottleneck){
    for(int cur = T; cur != S; cur = pre[cur]){
        flow[pre[cur]][cur] += bottleneck;
        flow[cur][pre[cur]] -= bottleneck;
    }
}

int MCMF(){
    int min_cost = 0;
    while(SPFA()){
        UpdateFlow(1);
        min_cost += dis[T];
    }
    return min_cost;
}

int main(){
    cin >> n >> m >> E;
    S = 0;
    T = n + m + 1;
    init();
    for(int i=0; i < E; i++){
        int u, v, w;
        cin >> u >> v >> w;
        cost[u][v] = w;
        cap[u][v] = 1;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    printf("%.d\n", MCMF());
}