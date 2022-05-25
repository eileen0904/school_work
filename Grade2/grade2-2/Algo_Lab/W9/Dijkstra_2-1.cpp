#include <bits/stdc++.h>
using namespace std;

const int Max_Distance = 100;
class Node{
public:
    int V, W;
    Node *NEXT;
    Node(){}
    Node(int v, int w){
        V = v;
        W = w;
    }
};

class AdjList{
public:
    Node *HEAD;
    AdjList(){}
};

class PQ_Node{
public:
    int weight, vertex;
    PQ_Node *prev, *next;
    PQ_Node(){
        prev = NULL;
        next = NULL;
    }
    PQ_Node(int w, int v){
        prev = NULL;
        next = NULL;
        weight = w;
        vertex = v;
    }
};

class Priority_Queue{
public:
    Priority_Queue(int n){
        head = NULL;
        tail = NULL;
        len = n;
    }
    bool IsEmpty(){
        if(head==NULL && tail==NULL){return true;}
        else{return false;}
    }
    void enqueue(int w, int v){ //from max-min
        PQ_Node *node = new PQ_Node(w, v);
        if(tail == NULL){
            tail = node;
            head = node;
        }
        else{
            PQ_Node *cur = head;
            if(w >= cur->weight){
                cur->prev = node;
                node->next = cur;
                head = node;
            }
            else{
                while(cur->next != NULL && cur->next->weight >= w){
                    cur = cur->next;
                }
                if(cur->next == NULL){
                    tail = node;
                    cur->next = node;
                    node->prev = cur;
                }
                else{
                    PQ_Node *cur_next = cur->next;
                    cur_next->prev = node;
                    node->next = cur_next;
                    cur->next = node;
                    node->prev = cur;
                }
            }
        }
    }
    PQ_Node *dequeue(){ //take min
        if(head->next == NULL){
            PQ_Node *cur = tail;
            tail = NULL;
            head = NULL;
            return cur;
        }
        else{
            tail = tail->prev;
            PQ_Node *cur = tail->next;
            tail->next = NULL;
            cur->prev = NULL;
            return cur;
        }
    }

private:
    PQ_Node *head, *tail;
    int len;
};

class Graph{
public:
    Graph(int n){
        num_v = n;
        adj = new AdjList [n];
        pq = new Priority_Queue(n);
        dis = new int[n];
        pred = new int[n];
        for(int i=0; i < n; i++){
            adj[i].HEAD = NULL;
            dis[i] = Max_Distance;
            pred[i] = -1;
        }
    }
    Node *newNode(int v, int w){
        Node *node = new Node;
        node->V = v;
        node->W = w;
        node->NEXT = NULL;
        return node;
    }
    void AddEdge(int s, int t, int w){
        Node *node = newNode(t, w);
        node->NEXT = adj[s].HEAD;
        adj[s].HEAD = node;
    }

    void Dijkstra(int start){
        dis[start] = 0;
        pq->enqueue(0, start);

        while(!pq->IsEmpty()){
            int s = pq->dequeue()->vertex;
            Node *cur = adj[s].HEAD;
            while(cur != NULL){
                int t = cur->V;
                int w = cur->W;
                if(dis[t] > dis[s] + w){
                    dis[t] = dis[s] + w;
                    pq->enqueue(dis[t], t);
                    pred[t] = s;
                }
                cur = cur->NEXT;
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
    Priority_Queue *pq;
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
