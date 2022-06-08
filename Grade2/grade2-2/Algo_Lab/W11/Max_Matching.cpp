#include <bits/stdc++.h>
using namespace std;

const int INF = 1000;
int g[10][10];
int n, m, edge;
int l[10], r[10], vl[10], vr[10];
int mat[10];

int path(int u){
    vl[u] = 1;
    for(int i=0; i < max(n, m); i++){
        if(!vr[i] && l[u] + r[i] == g[u][i]){
            vr[i] = 1;
            if(mat[i] == -1 || path(mat[i])){
                mat[i] = u;
                return 1;
            }
        }
    }
    return 0;
}

int KM(){
    for(int i=0; i < max(n, m); i++){
        r[i] = 0;
        mat[i] = -1;
    }
    for(int i=0; i < max(n, m); i++){
        l[i] = -INF;
        for(int j=0; j < max(n, m); j++){
            if(l[i] < g[i][j]){
                l[i] = g[i][j];
            }
        }
    }
    for(int i=0; i < max(n, m); i++){
        while(1){ 
            for(int j=0; j < max(n, m); j++){
                vl[j] = 0;
                vr[j] = 0;
            }
            if(path(i)) break;

            int d = INF;
            for(int j=0; j < max(n, m); j++){
                if(vl[j]){
                    for(int k=0; k < max(n, m); k++){
                        if(!vr[k]){
                            d = min(d, l[j] + r[k] - g[j][k]);
                        }
                    }
                }
            }
            if(d == INF) return -1;
            for(int j=0; j < max(n, m); j++){ //修改頂標
                if(vl[j]){
                    l[j] = l[j] - d;
                }
                if(vr[j]){
                    r[j] = r[j] + d;
                }
            }
        }
    }
    int ans = 0;
    for(int i=0; i < max(n, m); i++){
        if(g[mat[i]][i] > 0){
            int real = 10 - g[mat[i]][i];
            ans = ans + real;
        }
    }
    return ans;
}

int main(){
    cin >> n >> m >> edge;
    for(int i=0; i < max(n, m); i++){
        for(int j=0; j < max(n, m); j++){
            g[i][j] = 0;
        }
    }
    for(int i=0; i < edge; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g[u][v] = w;
        g[u][v] = 10 - g[u][v];
    }
    cout << KM() << endl;
    return 0;
}
