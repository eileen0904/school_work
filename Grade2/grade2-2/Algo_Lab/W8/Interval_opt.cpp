#include <bits/stdc++.h>
using namespace std;

int n;
class Interval{
public:
    Interval(){}
    Interval(int l, int r){
        left = l;
        right = r;
    }
    int left = 0, right = 0;
};

void MinInterval(vector<class Interval> &V, const Interval &target){
    Interval v;
    vector<class Interval> vp;
    int p = target.left;

    while(p <= target.right){
        int max_right = 0;
        for(int i=0; i < n; i++){
            if(V[i].left <= p && V[i].right > max_right){
                v.left = V[i].left;
                v.right = V[i].right;
                max_right = V[i].right;
            }
        }
        p = v.right;
        vp.push_back(Interval(v.left, v.right));
    }
    cout << "Minimum interval cover :" << endl;
    for(int i=0; i < vp.size(); i++){
        cout << "(" << vp[i].left << ", " << vp[i].right << ")" << endl;
    }
}

int main(){
    vector<class Interval> V;
    int a, b;
    cin >> n;
    for(int i=0; i < n; i++){
        cin >> a >> b;
        V.push_back(Interval(a, b));
    }
    cout << "Input target :" << endl;
    cin >> a >> b;
    Interval target(a, b);
    MinInterval(V, target);

    return 0;
}