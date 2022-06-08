#include <bits/stdc++.h>
using namespace std;

int c[10][10];
int flowPassed[10][10];
vector<int> g[10];
int match[10];
int dis[10];

int bfs(int sNode, int eNode){
    memset(match, -1, sizeof(match));
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    q.push(sNode);
    match[sNode] = 0;
    dis[sNode] = 999;
    while(!q.empty()){
        int currNode = q.front();
        q.pop();
        for(int i = 0; i < g[currNode].size(); i++){
            int to = g[currNode][i];
            if(match[to] == -1){
                if(c[currNode][to] - flowPassed[currNode][to] > 0){
                    match[to] = currNode;
                    dis[to] = min(dis[currNode], c[currNode][to] - flowPassed[currNode][to]);
                    if(to == eNode){
                        return dis[eNode];
                    }
                    q.push(to);
                }
            }
        }
    }
    return 0;
}

int edmondsKarp(int sNode, int eNode){
    int maxFlow = 0;
    while(1){
        int flow = bfs(sNode, eNode);
        if(flow == 0){
            break;
        }
        maxFlow += flow;
        int currNode = eNode;
        while(currNode != sNode){
            int prevNode = match[currNode];
            flowPassed[prevNode][currNode] += flow;
            flowPassed[currNode][prevNode] -= flow;
            currNode = prevNode;
        }
    }
    return maxFlow;
}

int main(){
    int nodCount, edCount;
    cout << "enter the number of nodes and edges\n";
    cin >> nodCount >> edCount;
    int source, sink;
    cout << "enter the source and sink\n";
    cin >> source >> sink;
    for (int ed = 0; ed < edCount; ed++) {
        cout << "enter the start and end vertex along with capacity\n";
        int from, to, cap;
        cin >> from >> to >> cap;
        c[from][to] = cap;
        g[from].push_back(to);
        g[to].push_back(from);
    }
    int maxFlow = edmondsKarp(source, sink);
    cout << endl << endl << "Max Flow is:" << maxFlow << endl;
}