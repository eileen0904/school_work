#include <iostream>
using namespace std;

int main(){
    string str;
    int i, j = 0;
    cin>>str;
    int len = str.size();
    if(len < 2){
        cout<<"length < 2"; //c1
    }
    else{
        for(i = 0; i < len/2; i++){ //n/2
            if(str[i] == str[len-i-1]){
                j++; //c2
            }
        }
        if(j==i) cout<<"is a palindrome"; //c3
        else cout<<"is not a palindrome"; //c4
    }
    
    return 0;
}