#include <bits/stdc++.h>
using namespace std;
#define INF 9999999999999
#define eps 0.00000000001

int n, m, S, T;
vector<int> edge[50];
int cap[50][50], flow[50][50], pre[50];
double cost[50][50], dis[50];

void init(){
    for(int i = S; i <= T; i++){
        edge[i].clear();
    }
    memset(cap, 0, sizeof(cap));
    memset(flow, 0, sizeof(flow));
    memset(cost, 0, sizeof(cost));
    for(int i = 1; i <= n; i++){
        cap[S][i] = 1;      
        edge[S].push_back(i);
    }
    for(int i = n + 1; i <= n + m; i++){
        cap[i][T] = 1;      
        edge[i].push_back(T);
    }
    for(int i = 1; i <= n; i++){
        for(int j = n + 1; j <= n + m; j++){
            cap[i][j] = 1;  
            edge[i].push_back(j);
            edge[j].push_back(i);
        }
    }
}

bool SPFA(){
    for(int i=0; i < 50; i++){
        dis[i] = INF;
    }
    queue<int> Q;
    bool inQ[50] = {false};
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

double MCMF(){
    double min_cost = 0;
    while(SPFA()){
        UpdateFlow(1);
        min_cost += dis[T];
    }
    return min_cost;
}

int main(){
    while(scanf("%d%d", &n, &m)){
        if(n == 0 && m == 0) break;
        S = 0;
        T = n + m + 1;
        init();
        double temp;
        for(int i = 1; i <= n; i++){
            for(int j = n + 1; j <= n + m; j++){
                scanf("%lf", &temp);
                cost[i][j] = temp;
            }
        }
        double ans = MCMF() ;
        printf("%.2f\n", ans / n + eps);
    }
}