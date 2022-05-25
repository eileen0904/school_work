#include <bits/stdc++.h>
using namespace std;

const int Max_Distance = 100;

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

class Edge{
public:
    int sb, tb, wb;
    Edge(int u, int v, int w){
        sb = u;
        tb = v;
        wb = w;
    }

};

class Graph{
public:
    Graph(int n){
        num_v = n;
        adj = new AdjList [n];
        dis = new int[n];
        visited = new bool[n];
        for(int i=0; i < n; i++){
            adj[i].head = NULL;
            dis[i] = Max_Distance;
            visited[i] = false;
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
    }
    void Dijkstra(int start){
        Node *cur = adj[start].head;
        while(cur != NULL){
            int t = cur->vertex;
            int w = cur->weight;
            dis[t] = w;
            cur = cur->next;
        }

        dis[start] = 0;
        visited[start] = true;

        for(int i=0; i < num_v; i++){
            int s = -1, minn = Max_Distance;
            for(int j=0; j < num_v; j++){
                if (visited[j] == false && dis[j] < minn){
                    s = j;
                    minn = dis[j];
                }
            }
            if(s == -1) break;
            else{
                if(i == 0){
                    path.push_back(Edge(0, s, minn));
                }
                visited[s] = true;
                Node *cur = adj[s].head;
                while(cur != NULL){
                    int t = cur->vertex;
                    int w = cur->weight;
                    if(visited[t] == false && dis[t] > dis[s] + w){
                        dis[t] = dis[s] + w;
                        AddT(s, t, dis[t]);
                    }
                    cur = cur->next;
                }
            }
        }
        DeleteCycle();
        PrintPath();
    }

    void AddT(int s, int t, int w){
        bool same = false;
        for(int i = 0; i < path.size(); i++){
            if(path[i].sb == s && path[i].tb == t){
                same = true;
            }
        }
        if(!same){
            path.push_back(Edge(s, t, w));
        }
    }

    void DeleteCycle(){
        for(int i = 0; i < path.size(); i++){
            for(int j = 0; j < path.size(); j++){
                if(path[i].tb == path[j].tb){
                    if(path[i].wb < path[j].wb){
                        path.erase(path.begin() + j);
                    }
                    else if(path[i].wb > path[j].wb){
                        path.erase(path.begin() + i);
                    }
                }
            }
        }
    }

    void PrintPath(){
        vector<class Edge>::iterator it;
        cout << "S" << "  " << "T" << "  " << "W" << endl;
        for(it = path.begin(); it != path.end(); it++){
            cout << it->sb << ", " << it->tb << ", " << it->wb << endl;
        }
    }

private:
    int num_v;
    AdjList *adj;
    vector<class Edge> path;
    int *dis;
    bool *visited;
};

int main(){
    Graph g(6);
    g.AddEdge(0, 1, 8); g.AddEdge(0, 5, 1);
    g.AddEdge(1, 0, 3); g.AddEdge(1, 2, 1);
    g.AddEdge(2, 0, 5); g.AddEdge(2, 3, 2); g.AddEdge(2, 4, 2);
    g.AddEdge(3, 1, 4); g.AddEdge(3, 2, 6); g.AddEdge(3, 4, 7); g.AddEdge(3, 5, 3);
    g.AddEdge(5, 3, 2); g.AddEdge(5, 4, 8);

    g.Dijkstra(0);

    return 0;
}
