#include <bits/stdc++.h>
using namespace std;

class Edge{
public:
    Edge(){}
    Edge(int u, int v, int w){
        from = u;
        to = v;
        weight = w;
    }
    int from, to, weight;
};

class WeightComp{
public:
    bool operator()(const Edge &e1, const Edge &e2){
        return e1.weight < e2.weight;
    }
};

class MST{
public:
    MST(int n){
        count = n;
        adjMatrix.resize(n);
        for(int i=0;i<n;i++){
            adjMatrix[i].resize(n);
        }
    }

    void AddEdge(int u, int v, int w){
        adjMatrix[u][v] = w;
    }

    void SortEdge(){
        for(int i=0; i < count; i++){
            for(int j=0; j < count; j++){
                if(adjMatrix[i][j]!=0){
                    SortedWeight.push_back(Edge(i, j, adjMatrix[i][j]));
                }
            }
        }
        sort(SortedWeight.begin(), SortedWeight.end(), WeightComp());

        cout << "Sorted Weight:" << endl;
        for(int i=0; i < count; i++){
            cout << SortedWeight[i].weight << " ";
        }
        cout << endl << endl;
    }

    void Kruskal(){
        class Edge *edgeMST = new Edge();
        int edge_count = 0;
        int subset[count]; //'-':is root & element_count of subtree, '+':root

        for(int i=0; i < count; i++){
            subset[i] = -1;
        }

        SortEdge();  //sorted weight

        for(int i=0; i < SortedWeight.size(); i++){
            if(FindSetCollapsing(subset, SortedWeight[i].from) != FindSetCollapsing(subset, SortedWeight[i].to)){
                edgeMST[edge_count++] = SortedWeight[i];
                UnionSet(subset, SortedWeight[i].from, SortedWeight[i].to);
            }
            show(subset, edgeMST, edge_count);
        }

        cout<<"MST"<<endl;
        for(int i=0; i < count - 1; i++){
            cout << edgeMST[i].from << " - " <<edgeMST[i].to << " : " << edgeMST[i].weight << endl;
        }
    }

    int FindSetCollapsing(int *subset, int i){
        int root;
        for(root = i; subset[root] >= 0; root = subset[root]);
        while (i!=root){
            int parent = subset[i];
            subset[i] = root;
            i = parent;
        }
        return root;
    }

    void UnionSet(int *subset, int x, int y){
        int r1 = FindSetCollapsing(subset, x);
        int r2 = FindSetCollapsing(subset, y);
        if(subset[r1] <= subset[r2]){
            subset[r1] = subset[r1] + subset[r2];
            subset[r2] = r1;
        }
        else{
            subset[r2] = subset[r2] + subset[r1];
            subset[r1] = r2;
        }
    }
    void show(int *subset, class Edge *edgeMST, int edge_count){
        cout << "Subset:" << endl;
        for(int i=0; i < count; i++){
            cout << subset[i] << " ";
        }
        cout << endl << "edgeMST:" << endl;
        for(int i=0; i < edge_count; i++){
            cout << edgeMST[i].from << " - " <<edgeMST[i].to << " : " << edgeMST[i].weight << endl;
        }
        cout << endl << endl;
    }

    friend WeightComp;
private:
    vector<vector<int>> adjMatrix;
    vector<class Edge> SortedWeight;
    int count;
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

    g.Kruskal();

    return 0;
}
