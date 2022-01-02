#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge{
public:
    Edge(){}
    Edge(int u, int v, int w){
        from = u;
        to = v;
        weight = w;
    }
    int getFrom() const{
        return from;
    }
    int getTo() const{
        return to;
    }
    int getWeight() const{
        return weight;
    }
private:
    int from, to, weight;
};

class WeightComp{
public:
     bool operator()(const Edge &e1, const Edge &e2){
        return e1.getWeight() < e2.getWeight();
     }
};

class Graph{
public:
    Graph(){}
    Graph(int n){
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
        for(int i=0;i<count;i++){
            for(int j=0;j<count;j++){
                if(adjMatrix[i][j]!=0){
                    SortedWeight.push_back(Edge(i, j, adjMatrix[i][j]));
                }
            }
        }
        sort(SortedWeight.begin(), SortedWeight.end(), WeightComp());
    }
    void Kruskal(){
        class Edge *edgeMST = new Edge();
        int edge_count = 0;
        int subset[count]; //'-':is root & element_count of subtree, '+':root
        for(int i=0;i<count;i++){
            subset[i] = -1;
        }
        SortEdge();  //sorted weight
        for(int i=0; i<SortedWeight.size(); i++){
            if(FindSetCollapsing(subset, SortedWeight[i].getFrom()) != FindSetCollapsing(subset, SortedWeight[i].getTo())){
                edgeMST[edge_count++] = SortedWeight[i];
                UnionSet(subset, SortedWeight[i].getFrom(), SortedWeight[i].getTo());
            }
        }
        cout<<"Minimum Spanning Tree"<<endl;
        for(int i=0;i<count-1;i++){
            cout<<"V1:"<<edgeMST[i].getFrom()<<" , "<<"V2:"<<edgeMST[i].getTo()<<" , "<<"Weight:"<<edgeMST[i].getWeight()<<endl;
        }
    }
    int FindSetCollapsing(int *subset, int i){
        int root;
        for(root=i; subset[root] >= 0; root = subset[root]);
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
        if(subset[r1]<=subset[r2]){
            subset[r1] = subset[r1] + subset[r2];
            subset[r2] = r1;
        }
        else{
            subset[r2] = subset[r2] + subset[r1];
            subset[r1] = r2;
        }
    }
    void printGraph(){
        cout<<"Graph"<<endl;
        for(int i=0;i<count;i++){
            for(int j=0;j<count;j++){
                if(adjMatrix[i][j]!=0){
                    cout<<"V1:"<<i<<" , "<<"V2:"<<j<<" , "<<"Weight:"<<adjMatrix[i][j]<<endl;
                }
            }
        }
    }
    friend WeightComp;
private:
    vector<vector<int>> adjMatrix;
    vector<class Edge> SortedWeight;
    int count;
};

int main(){
    Graph g(7);
    g.AddEdge(0, 1, 5); g.AddEdge(0, 5, 3);
    g.AddEdge(1, 0, 5); g.AddEdge(1, 2, 10); g.AddEdge(1, 4, 1); g.AddEdge(1, 6, 4);
    g.AddEdge(2, 1, 10); g.AddEdge(2, 3, 5); g.AddEdge(2, 6, 8);
    g.AddEdge(3, 2, 5); g.AddEdge(3, 4, 7); g.AddEdge(3, 6, 9);
    g.AddEdge(4, 1, 1); g.AddEdge(4, 3, 7); g.AddEdge(4, 5, 6); g.AddEdge(4, 6, 2);
    g.AddEdge(5, 0, 3); g.AddEdge(5, 4, 6);
    g.AddEdge(6, 1, 4); g.AddEdge(6, 2, 8); g.AddEdge(6, 3, 9); g.AddEdge(6, 4, 2);
    g.printGraph();
    cout<<endl;
    g.Kruskal();

    return 0;
}
