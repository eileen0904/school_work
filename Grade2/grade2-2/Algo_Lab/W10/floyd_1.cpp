#include <bits/stdc++.h>
using namespace std;

const int MaxDistance = 100;

class Graph{
public:
    Graph(int n){
        num_vertex = n;
        Adj = new int *[n];
        pred = new int *[n];
        dis = new int *[n];
        for(int i=0; i < n; i++){
            Adj[i] = new int[n];
            pred[i] = new int[n];
            dis[i] = new int[n];
        }
        for(int i=0; i < n ;i++){
            for(int j=0; j < n; j++){
                if(i == j) Adj[i][j] = 0;
                else Adj[i][j] = MaxDistance;
                pred[i][j] = -1;
            }
        }
    }
    void AddEdge(int from, int to, int weight){
        Adj[from][to] = weight;
    }
    void Init(){
        for(int i=0; i < num_vertex; i++){
            for(int j=0; j < num_vertex; j++){
                dis[i][j] = Adj[i][j];
                if(dis[i][j] != 0  && dis[i][j] != MaxDistance){
                    pred[i][j] = i;
                }
            }
        }
    }
    void Floyd(){
        Init();
        for(int k=0; k < num_vertex; k++){
            for(int s=0; s < num_vertex; s++){
                for(int t=0; t < num_vertex; t++){
                    if(dis[s][t] > dis[s][k] + dis[k][t] && dis[s][k] != MaxDistance){
                        dis[s][t] = dis[s][k] + dis[k][t];
                        pred[s][t] = pred[k][t];
                    }
                }
            }
        }
        Print_Path();
    }
    int *construct_path(int u, int v){
        int *path = new int[num_vertex];
        counter = 0;
        path[counter++] = v;
        while (u != v) {
            v = pred[u][v];
            path[counter] = v;
            counter++;
        }
        return path;
    }
    void Print_Path(){
        for(int i=0; i < num_vertex; i++){
            for(int j=0; j < num_vertex; j++){
                if(i == j || pred[i][j] == -1) continue;
                else{
                    int *path = construct_path(i, j);
                    cout << i << " to " << j << " : ";
                    for(int k = counter - 1; k >= 0; k--){
                        cout << path[k] << " ";
                    }
                    cout << endl;
                }
            }
        }
    }

private:
    int num_vertex, counter;
    int **Adj, **dis, **pred;
};

int main(){

    Graph g(4);
    g.AddEdge(0, 1, 2); g.AddEdge(0, 2, 6); g.AddEdge(0, 3, 8);
    g.AddEdge(1, 2, -2); g.AddEdge(1, 3, 3);
    g.AddEdge(2, 0, 4); g.AddEdge(2, 3, 1);

    g.Floyd();

    return 0;
}