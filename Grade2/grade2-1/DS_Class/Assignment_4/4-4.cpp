#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <iomanip>
using namespace std;

class Graph{
public:
    Graph(int n){
        count = n;
        adjList.resize(n);
        ve.resize(n);
        vl.resize(n);
    }
    void addEdge(int u, int v, int w){
        adjList[u].push_back(make_pair(v,w));
        edge_count++;
    }
    void Critical_Path(){
        list<pair<int,int> >::iterator iter;
        //ve
        for(int i=0;i<count;i++){
            for(iter=adjList[i].begin();iter!=adjList[i].end();iter++){
                if(ve[(*iter).first] < ve[i] + (*iter).second){
                    ve[(*iter).first] = ve[i] + (*iter).second;
                }
            }
        }
        //vl
        vl[count-1] = ve[count-1];
        for(int i=count-2;i>0;i--){
            vl[i] = ve[count-1];
            for(iter=adjList[i].begin();iter!=adjList[i].end();iter++){
                if(vl[i] > vl[(*iter).first] - (*iter).second){
                    vl[i] = vl[(*iter).first] - (*iter).second;
                }
            }
        }
        //ae, al
        cout<<"Critical Path:"<<endl;
        cout<<setw(4)<<"V1"<<setw(4)<<"V2"<<endl;
        for(int i=0;i<count;i++){
            for(iter=adjList[i].begin();iter!=adjList[i].end();iter++){
                ae = ve[i];
                al = vl[(*iter).first] - (*iter).second;
                if(ae==al){
                    cout<<setw(4)<<i<<setw(4)<<(*iter).first<<endl;
                }
            }
        }
    }
    void Print_Graph(){
        cout<<"Graph:"<<endl;
        cout<<setw(8)<<"From"<<setw(4)<<"To"<<setw(8)<<"Weight"<<endl;
        list<pair<int,int> >::iterator iter;
        for(int i=0;i<count;i++){
            for(iter=adjList[i].begin();iter!=adjList[i].end();iter++){
                cout<<setw(6)<<i<<setw(6)<<(*iter).first<<setw(6)<<(*iter).second<<endl;
            }
        }
    }
private:
    vector<list<pair<int,int>>> adjList;
    int count = 0; //number of vertex
    int edge_count = 0;
    vector<int> ve, vl; //early_start & latest_start event time
    int ae = 0, al = 0; //early_start & latest_start activity time
};

int main(){
    Graph g(9);
    g.addEdge(0,1,6); g.addEdge(0,2,4); g.addEdge(0,3,5);
    g.addEdge(1,4,1);
    g.addEdge(2,4,1);
    g.addEdge(3,5,2);
    g.addEdge(4,6,9); g.addEdge(4,7,7);
    g.addEdge(5,7,4);
    g.addEdge(6,8,2);
    g.addEdge(7,8,4);
    g.Print_Graph();
    cout<<endl;
    g.Critical_Path();
}
