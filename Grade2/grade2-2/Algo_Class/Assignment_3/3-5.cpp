#include <bits/stdc++.h>
using namespace std;

const int MaxDistance = 100;

class Graph{
    public:
        Graph(int n){
            num_vertex = n;
            for(int i=0; i < n ;i++){
                for(int j=0; j < n; j++){
                    if(i == j) AM[i][j] = 0;
                    else AM[i][j] = MaxDistance;
                    P[i][j] = -1;
                }
            }
        }

        void Add(int from, int to, int weight){
            AM[from][to] = weight;
        }

        void Init(){
            for(int i=0; i < num_vertex; i++){
                for(int j=0; j < num_vertex; j++){
                    D[i][j] = AM[i][j];
                    if(D[i][j] != 0  && D[i][j] != MaxDistance){
                        P[i][j] = i;
                    }
                }
            }
        }

        void Floyd(){
            Init();

            cout << "Initial Distance:" << endl;
            Print(D);
            cout << endl;
            cout << "Initial P:" << endl;
            Print(P);

            for(int i=0; i < num_vertex; i++){
                cout << endl << "Including vertex: " << i << endl << endl;
                for(int j=0; j < num_vertex; j++){
                    for(int k=0; k < num_vertex; k++){
                        if ((D[j][k] > D[j][i] + D[i][k]) && (D[j][i] != MaxDistance)){
                            D[j][k] = D[j][i] + D[i][k];
                            P[j][k] = P[i][k];
                        }
                    }
                }
                cout << "Distance:" << endl;
                Print(D);
                cout << endl;
                cout << "P:" << endl;
                Print(P);
                cout << endl;
            }
        }

        void Print(int arr[7][7]){
            for(int i=0; i < num_vertex; i++){
                for(int j=0; j < num_vertex; j++){
                    cout << arr[i][j] << " ";
                }
                cout << endl;
            }
        }

    private:
        int num_vertex;
        int AM[7][7], D[7][7], P[7][7];
};

int main(){
    Graph g(7);
    g.Add(0, 1, 4); g.Add(0, 5, 10);
    g.Add(1, 0, 3); g.Add(1, 3, 18);
    g.Add(2, 1, 6);
    g.Add(3, 1, 5); g.Add(3, 2, 15); g.Add(3, 4, 2); g.Add(3, 5, 19); g.Add(3, 6, 8);
    g.Add(4, 2, 12); g.Add(4, 3, 1); g.Add(0, 1, 4);
    g.Add(5, 6, 10);
    g.Add(6, 3, 5);

    g.Floyd();
}
