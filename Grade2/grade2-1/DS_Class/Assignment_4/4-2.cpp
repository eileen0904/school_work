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

class Subset
{
public:
    int rank;
    int parent;
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
        edge.push_back(Edge(u, v, w));
        edge_count++;
    }

    void Boruvka(){
        Subset *subset = new Subset();
        int *cheapest = new int[count];
        int MST_weight = 0;

        for(int i=0;i<count;i++){
            subset[i].parent = i;
            subset[i].rank = 0;
            cheapest[i] = -1;
        }

        int numtree = count;

        while(numtree>1){
            for(int i=0;i<edge_count;i++){

                int s1 = find(subset, edge[i].getFrom());
                int s2 = find(subset, edge[i].getTo());

                if(s1==s2) continue;
                else{
                    if(cheapest[s1]==-1 || edge[cheapest[s1]].getWeight() > edge[i].getWeight()){
                        cheapest[s1] = i;
                    }
                    if(cheapest[s2]==-1 || edge[cheapest[s2]].getWeight() > edge[i].getWeight()){
                        cheapest[s2] = i;
                    }
                }
            }

            cout<<"Minimum Spanning Tree"<<endl;
            for(int i=0;i<count;i++){
                if(cheapest[i] != -1){
                    int s1 = find(subset, edge[cheapest[i]].getFrom());
                    int s2 = find(subset, edge[cheapest[i]].getTo());

                    if(s1==s2) continue;
                    MST_weight = MST_weight + edge[cheapest[i]].getWeight();
                    cout<<"V1:"<<edge[cheapest[i]].getFrom()<<" , "<<"V2:"<<edge[cheapest[i]].getTo()
                    <<" , "<<"Weight:"<<edge[cheapest[i]].getWeight()<<endl;

                    UnionSet(subset, s1, s2);
                    numtree--;
                }
            }
        }
        cout<<"Weight of MST:"<<MST_weight<<endl;
    }

    int find(class Subset subset[], int i){ //find root
        if(subset[i].parent != i){
            subset[i].parent = find(subset, subset[i].parent);
        }
        return subset[i].parent;
    }

    void UnionSet(class Subset subset[], int x, int y){
        int r1 = find(subset, x);
        int r2 = find(subset, y);
        if(subset[r1].rank < subset[r2].rank){
            subset[r1].parent = r2;
        }
        else if(subset[r1].rank > subset[r2].rank){
            subset[r2].parent = r1;
        }
        else{
            subset[r2].parent = r1;
            subset[r1].rank++;
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
private:
    vector<vector<int>> adjMatrix;
    vector<class Edge> edge;
    int count = 0, edge_count = 0;
};

int main(){
    Graph g(4);
    g.AddEdge(0, 1, 10); g.AddEdge(0, 2, 6); g.AddEdge(0, 3, 5);
    g.AddEdge(1, 0, 10); g.AddEdge(1, 3, 15);
    g.AddEdge(2, 0, 6); g.AddEdge(2, 3, 4);
    g.AddEdge(3, 0, 5); g.AddEdge(3, 2, 4); g.AddEdge(3, 1, 15);
    g.printGraph();
    cout<<endl;
    g.Boruvka();

    return 0;
}