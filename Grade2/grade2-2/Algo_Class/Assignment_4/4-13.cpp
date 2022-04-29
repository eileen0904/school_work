#include <bits/stdc++.h>
using namespace std;

const int Max_Distance = 100;
typedef pair<int, int> P;

class SP{
    public:
        SP(int n){
            count = n;
            AdjList = new list<P> [n];
        }

        void AddEdge(int from, int to, int weight){
            AdjList[from].push_back(make_pair(to, weight));
            AdjList[to].push_back(make_pair(from, weight));
        }

        void Init(int start){
            dis.resize(count);
            for(int i=0; i < count; i++){
                dis[i] = Max_Distance;
            }
        }

        void Dijkstra(int start){
            Init(start);

            dis[start] = 0;
            pq.push(make_pair(0, start));

            while(!pq.empty()){
                int u = pq.top().second;
                pq.pop();
                list<pair<int, int>>::iterator it;
                for(it = AdjList[u].begin(); it != AdjList[u].end(); it++){
                    Relax(u, (*it).first, (*it).second);
                    show(dis, pq);
                }
            }

            cout << "Vertex" << "   "<< "Distance from start" << endl;
            for(int i=0; i < count; i++){
                cout << i << setw(18) << dis[i] << endl;
            }
        }

        void Relax(int f, int t, int w){
            if(dis[t] > dis[f] + w){
                dis[t] = dis[f] + w;
                pq.push(make_pair(dis[t], t));
            }
        }

        void show(vector<int> dis, priority_queue<P, vector<P>, greater<P> > pqq){
            cout << "Distance:" << endl;
            for(int i=0; i < count; i++){
                cout << dis[i] << " ";
            }
            cout << endl << "Priority Queue:" << endl;
            while(!pqq.empty()){
                auto now = pqq.top();
                pqq.pop();
                cout << now.first << ", " << now.second << endl;
            }
            cout << endl << endl;
        }
    private:
        int count;
        list<pair<int, int>> *AdjList;
        //Not yet explore vertex: (Min dis from first to V), (V)
        priority_queue<P, vector<P>, greater<P> > pq;
        vector<int> dis;
};

int main(){
    SP g(10);
    //v1:0, v2:1, v3:2, ... , v10:9
    g.AddEdge(0, 1, 32); g.AddEdge(0, 3, 17);
    g.AddEdge(1, 4, 45);
    g.AddEdge(2, 3, 18); g.AddEdge(2, 6, 5);
    g.AddEdge(3, 7, 3); g.AddEdge(3, 4, 10);
    g.AddEdge(4, 5, 28); g.AddEdge(4, 8, 25);
    g.AddEdge(5, 9, 6);
    g.AddEdge(6, 7, 59);
    g.AddEdge(7, 8, 4);
    g.AddEdge(8, 9, 12);

    g.Dijkstra(3);

    return 0;
}
