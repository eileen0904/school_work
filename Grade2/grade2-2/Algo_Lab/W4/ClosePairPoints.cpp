#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

class Point{
    public:
        double x, y;
};

bool cmpx(Point a, Point b){
    return a.x < b.x;
}

bool cmpy(Point a, Point b){
    return a.y < b.y;
}

double dis(Point a, Point b){
    double X = a.x - b.x;
    double Y = a.y - b.y;
    return sqrt(X*X + Y*Y);
}

double close_pair(Point p[], int l, int r, int n){
    if(r == l+1){ //only two points
        return dis(p[l], p[r]);
    }
    if(r == l+2){ //only three points
        return min(min(dis(p[l],p[l+1]),dis(p[l],p[r])),dis(p[l+1],p[r]));
    }

    int mid = (l + r) / 2;
    double dl = close_pair(p, l, mid, n); //T(n/2)
    double dr = close_pair(p, mid + 1, r, n); //T(n/2)
    double d = min(dl, dr);

    Point cross[n];
    int k = 0;
    for(int i = l; i <= r; i++){ //有沒有在d範圍裡 //n
        if(abs(p[i].x - p[mid].x) <= d){
            cross[k] = p[i];
            k++;
        }
    }

    sort(cross, cross + k, cmpy); //nlogn*logn = nlog^2n
    for(int i = 0; i < k; i++){ //n
        for(int j = i+1; j < k; j++){
            if(cross[j].y - cross[i].y >= d) break;
            d = min(d, dis(cross[i], cross[j]));
        }
    }

    return d;

}

int main(){
    Point p[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(p) / sizeof(p[0]);
    sort(p, p + n, cmpx); //nlogn
    double ans = close_pair(p, 0, n-1, n);
    cout << fixed << setprecision(4) << ans << endl;

    return 0;
}
