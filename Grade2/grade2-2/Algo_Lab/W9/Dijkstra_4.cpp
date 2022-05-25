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

class Graph{
public:
    Graph(int n){
        num_v = n;
        adj = new AdjList [n];
        dis = new int[n];
        pred = new int[n];
        visited = new bool[n];
        for(int i=0; i < n; i++){
            adj[i].head = NULL;
            dis[i] = Max_Distance;
            visited[i] = false;
            pred[i] = -1;
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
            pred[t] = start;
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
                visited[s] = true;
                Node *cur = adj[s].head;
                while(cur != NULL){
                    int t = cur->vertex;
                    int w = cur->weight;
                    if(visited[t] == false && dis[t] > dis[s] + w){
                        dis[t] = dis[s] + w;
                        pred[t] = s;
                    }
                    cur = cur->next;
                }
            }
        }
        cout << "Vertex" << "   "<< "Distance from start" << endl;
        for(int i=0; i < num_v; i++){
            cout << i << setw(18) << dis[i] << endl;
        }
        cout << "Vertex" << "   "<< "Predecessor" << endl;
        for(int i=0; i < num_v; i++){
            cout << i << setw(13) << pred[i] << endl;
        }
    }

private:
    int num_v;
    AdjList *adj;
    int *dis, *pred;
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
