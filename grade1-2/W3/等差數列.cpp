#include<iostream>
using namespace std;

int main(){
    int a1,d,n;
    cin>>a1>>d>>n;
    int k=1,an=a1;
    while(k<=n){
        cout<<"a["<<k<<"]"<<"="<<an<<endl;
        k++;
        an=a1+((k-1)*d);
    }

    return 0;
}