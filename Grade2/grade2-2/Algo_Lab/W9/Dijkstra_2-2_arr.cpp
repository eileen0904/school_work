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

class HeapNode{
public:
    int key, element; //weight, vertex
    HeapNode(){
        key = 0;
        element = 0;
    }
    HeapNode(int k, int e){
        key = k;
        element = e;
    }
};

class BinaryHeap{
public:
    BinaryHeap(){
        heap.resize(1);
    }
    BinaryHeap(int n){
        heap.resize(n+1);
    }
    bool IsHeapEmpty(){
        return (heap.size() < 1);
    }
    void swap(class HeapNode &node1, class HeapNode &node2){
        class HeapNode temp = node1;
        node1 = node2;
        node2 = temp;
    }
    void MinHeapify(int node, int length){
        int left = 2 * node;
        int right = 2 * node + 1;
        int minn;
        if(left <= length && heap[left].key < heap[node].key){
            minn = left;
        }
        else{
            minn = node;
        }
        if(right <= length && heap[right].key < heap[minn].key){
            minn = right;
        }   
        if(minn != node) {   //目前node的Key不是三者中的最小
            swap(heap[minn], heap[node]); //swap node與三者中Key最小的node之位置
            MinHeapify(minn, length); //調整新的subtree成Min Heap
        }
    }
    void BuildMinHeap(int *arr, int n){
        for(int i=0; i < n; i++){
            heap[i + 1].element = i;
            heap[i + 1].key = arr[i];
        }
        for(int i = heap.size()/2; i >= 1; i--){
            MinHeapify(i, heap.size() - 1); //length-1，因為heap從1開始存
        }
    }
    int FindPos(int node){
        int index = 0;
        for(int i=1; i < heap.size(); i++){
            if(heap[i].element == node){
                index = i;
            }
        }
        return index;
    }
    int getParent(int node){
        return floor(node/2);
    }
    int ExtractMin(){ //return有最小Key的node之index
        if (IsHeapEmpty()) {
            cout << "Heap is empty" << endl;
            exit(-1);
        }
        int minn = heap[1].element;
        heap[1] = heap[heap.size() - 1]; //把最後一個element放到第一個位置
        heap.erase(heap.begin() + heap.size() - 1); //刪除最後一個element
        MinHeapify(1, heap.size());

        return minn;
    }
    void DecreaseKey(int node, int newKey){
        int idx_node = FindPos(node);
        if(newKey > heap[idx_node].key){
            return;
        }
        heap[idx_node].key = newKey;
        int parent = getParent(idx_node);
        while(idx_node > 1 && heap[parent].key > heap[idx_node].key){
            swap(heap[idx_node], heap[parent]);
            idx_node = getParent(idx_node);
            parent = getParent(idx_node);
        }
    }
private:
    vector<HeapNode> heap;
};

class Graph{
public:
    Graph(int n){
        num_v = n;
        adj = new AdjList [n];
        dis = new int[n];
        pred = new int[n];
        for(int i=0; i < n; i++){
            adj[i].head = NULL;
            dis[i] = Max_Distance;
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
        dis[start] = 0;
        BinaryHeap pq(num_v);
        pq.BuildMinHeap(dis, num_v);

        while(!pq.IsHeapEmpty()){
            int s = pq.ExtractMin();
            Node *cur = adj[s].head;
            while(cur != NULL){
                int t = cur->vertex;
                int w = cur->weight;
                if(dis[t] > dis[s] + w){
                    dis[t] = dis[s] + w;
                    pred[t] = s;
                }
                pq.DecreaseKey(t, dis[t]);
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
