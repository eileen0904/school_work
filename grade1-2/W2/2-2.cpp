#include<iostream>
using namespace std;

int main(){
    int n,a,b,c,d;
    cin >> n;
    a=n/1000;
    b=n/100-a*10;
    c=n/10-a*100-b*10;
    d=n-a*1000-b*100-c*10;
    cout << d << c << b << a;

    return 0;
}
