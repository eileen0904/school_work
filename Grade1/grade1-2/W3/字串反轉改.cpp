#include<iostream>
#include<string.h>
using namespace std;

int main(){
    char str[255];
    int i;
    cin>>str;
    int len=strlen(str);
    for(i=0;i<len;i++){
        if(str[i]>=97 && str[i]<=122){
            str[i]=str[i]-32;
        }
    }
    for(i=len-1;i>=0;i--){
        cout<<str[i];
    }

    return 0;
}