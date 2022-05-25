#include <bits/stdc++.h>
using namespace std;
const int N = 20001;
#define Max_Distance 0x3F3F3F3F3F3F3F3F
long long dis[20001];

struct Edge{
    int V, W;
    Edge(){}
    Edge(int v, int w){
        V = v;
        W = w;
    }
    bool operator<(const Edge &e) const{
        return (e.W < W);  //小的在最前面
    }
};

class Node{
public:
    int vertex, weight;
    Node *next;
    Node(){}
    Node(int v, int w){
        vertex = v;
        weight = w;
    }
};

class AdjList{
public:
    Node *head;
    AdjList(){}
};

priority_queue<Edge> pq;

class Graph{
public:
    Graph(int n){
        num_v = n;
        adj = new AdjList [n];
        for(int i=0; i < n; i++){
            adj[i].head = NULL;
            dis[i] = Max_Distance;
        }
    }
    Node *newNode(int v, int w){
        Node *node = new Node;
        node->vertex = v;
        node->weight = w;
        node->next = NULL;
        return node;
    }
    void AddEdge(int s, int t, int w){
        Node *node = newNode(t, w);
        node->next = adj[s].head;
        adj[s].head = node;
        node = newNode(s, w);
        node->next = adj[t].head;
        adj[t].head = node;
    }
    void dijkstra(int start){
        dis[start] = 0;
        pq.push(Edge(start, 0));

        while(!pq.empty()){
            Edge edge = pq.top();
            pq.pop();
            int s = edge.V;
            Node *cur = adj[s].head;
            while(cur != NULL){
                int t = cur->vertex;
                int w = cur->weight;
                if(dis[t] > dis[s] + w){
                    dis[t] = dis[s] + w;
                    pq.push({t, dis[t]});
                }
                cur = cur->next;
            }
        }
    }
private:
    int num_v;
    AdjList *adj;
};

int main(){
    int testcase;
    cin >> testcase;
    for(int c = 1; c <= testcase; c++){
        int n, m, s, t, u, v, w;
        cin >> n >> m >> s >> t;
        class Graph G(n);
        for(int i=0; i < m; i++){
            cin >> u >> v >> w;
            G.AddEdge(u, v, w);
        }
        cout << "Case #" << c << ": ";
        if(m == 0){
            cout << "unreachable" << endl;
        }
        else{
            G.dijkstra(s);
            if(dis[t] == Max_Distance){
                cout << "unreachable" << endl;
            }
            else{
                cout << dis[t] <<endl;
            }
        }
    }
    return 0;
}
