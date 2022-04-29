#include <bits/stdc++.h>
using namespace std;

const int Max_Weight = 1000;    //infinity

class MST{
    public:
        MST(int n){
            count = n;
            AdjMatrix.resize(n);
            for(int i=0; i < n; i++){
                AdjMatrix[i].resize(n);
            }
        }

        void AddEdge(int from, int to, int weight){
            AdjMatrix[from][to] = weight;
        }

        int Find_Min_Dis(int *dis, bool *visited){
            int min = Max_Weight, min_idx = 0;
            for(int i=0; i < count; i++){
                if(visited[i] == false && dis[i] < min){
                    min = dis[i];
                    min_idx = i;
                }
            }
            return min_idx;
        }

        void show(int *pre, int *dis, bool *visited){
            cout << "Predecessor:" << endl;
            for(int i=0; i < count; i++){
                cout << pre[i] << " ";
            }
            cout << endl << "Distance:" << endl;
            for(int i=0; i < count; i++){
                cout << dis[i] << " ";
            }
            cout << endl << "Visited:" << endl;
            for(int i=0; i < count; i++){
                cout << visited[i] << " ";
            }
            cout << endl << endl;
        }

        void Prim(int start){
            int dis[count], pre[count];
            bool visited[count];

            for(int i=0; i < count; i++){
                dis[i] = Max_Weight;
                pre[i] = -1;
                visited[i] = false;
            }

            dis[start] = 0;
            for(int i=0; i < count; i++){
                int u = Find_Min_Dis(dis, visited);
                visited[u] = true;
                for(int j=0; j < count; j++){
                    if(visited[j] == false && AdjMatrix[u][j] != 0 && AdjMatrix[u][j] < dis[j]){
                        pre[j] = u;
                        dis[j] = AdjMatrix[u][j];
                    }
                }
                show(pre, dis, visited);
            }

            cout << "MST:" << endl;
            int i = (start + 1) % count;
            while(i != start){
                cout << pre[i] << " - " << i << " : " << AdjMatrix[pre[i]][i] << endl;
                i = (++i) % count;
            }
        }
    private:
        int count;
        vector<vector<int>> AdjMatrix;
};

int main(){
    MST g(10);
    //v1:0, v2:1, v3:2, ... , v10:9
    g.AddEdge(0, 1, 32); g.AddEdge(0, 3, 17);
    g.AddEdge(1, 0, 32); g.AddEdge(1, 4, 45);
    g.AddEdge(2, 3, 18); g.AddEdge(2, 6, 5);
    g.AddEdge(3, 0, 17); g.AddEdge(3, 2, 18); g.AddEdge(3, 7, 3); g.AddEdge(3, 4, 10);
    g.AddEdge(4, 1, 45); g.AddEdge(4, 3, 10); g.AddEdge(4, 5, 28); g.AddEdge(4, 8, 25);
    g.AddEdge(5, 4, 28); g.AddEdge(5, 9, 6);
    g.AddEdge(6, 2, 5); g.AddEdge(6, 7, 59);
    g.AddEdge(7, 3, 3); g.AddEdge(7, 6, 59); g.AddEdge(7, 8, 4);
    g.AddEdge(8, 4, 25); g.AddEdge(8, 7, 4); g.AddEdge(8, 9, 12);
    g.AddEdge(9, 5, 6); g.AddEdge(9, 8, 12);

    g.Prim(0);

    return 0;
}
