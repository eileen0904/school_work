#include<iostream>
using namespace std;

void output(int arr[], int n, char ch) {
    int i,k=0;
    for(i=0;i<n;i++){
        cout<<arr[i];
        if(k<n-1){
            cout<<ch;
            k++;
        }
    }
}