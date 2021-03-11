#include<iostream>
#include<iomanip>
using namespace std;

int main(){
    int n, i, j, row=0, spare=0, a=1, num=0;
    cin>>n;
    int v[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            v[i][j]=0;
        }
    }
    for(i=0;i<n;i++){
        v[i][0]=1;
        v[i][i]=1;
    }
    for(i=2;i<n;i++){
        for(j=1;j<i;j++){
            v[i][j]=v[i-1][j]+v[i-1][j-1];
        }
    }
    for(row=1;row<=n;row++){
        for(spare=n-row;spare>=1;spare--){
            cout<<"  ";
        }
        cout<<setw(2)<<a;
        for(num=1;num<row;num++){
            cout<<"  ";
            cout<<setw(2)<<v[row-1][num];
        }
        if(row!=n){
            cout<<endl;
        }
    }

    return 0;
}