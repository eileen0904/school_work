#include <bits/stdc++.h>
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
    double xx = a.x - b.x;
    double yy = a.y - b.y;
    return sqrt(xx*xx + yy*yy);
}

Point close[2];

double close_pair(Point p[], int l, int r, int n){
    if(l >= r) return (double)INT_MAX;
    
    int mid = (l + r) / 2;
    double dl = close_pair(p, l, mid, n);
    double dr = close_pair(p, mid + 1, r, n);
    double d = min(dl, dr);
    
    Point cross[n];
    int k = 0;
    for(int i = l; i <= r; i++){ //有沒有在d範圍裡
        if(abs(p[i].x - p[mid].x) <= d){
            cross[k] = p[i];
            k++;
        }
    }

    sort(cross, cross + k, cmpy);
    for(int i = 0; i < k; i++){ 
        for(int j = i+1; j < k; j++){
            if(cross[j].y - cross[i].y < d){
                if(dis(cross[i], cross[j]) < d){
                    d = dis(cross[i], cross[j]);
                    close[0].x = cross[i].x;
                    close[0].y = cross[i].y;
                    close[1].x = cross[j].x;
                    close[1].y = cross[j].y;
                }
            }
            else break;
        }
    }

    return d;

}

int main(){
    Point p[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(p) / sizeof(p[0]);
    sort(p, p + n, cmpx);
    double ans = close_pair(p, 0, n-1, n);
    cout << "The close pair are: ";
    cout << "(" << fixed << setprecision(4) << close[0].x << "," << close[0].y << ")" << ",";
    cout << "(" << fixed << setprecision(4) << close[1].x << "," << close[1].y << ")" << endl;
    cout << fixed << setprecision(4) << ans << endl;

    return 0;
}
