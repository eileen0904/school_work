#include<iostream>
#include<stack>
#include<cstring>
using namespace std;

stack<char> bracket;

int main(){
    string str;
    cin>>str;
    for(int i=0;i<str.size();i++){
        if(str[i]=='(' || str[i]=='[' || str[i]=='{'){
            bracket.push(str[i]);
        }
        if(str[i]==')'){
            if(bracket.top()=='('){
                bracket.pop();
            }
        }
        if(str[i]==']'){
            if(bracket.top()=='['){
                bracket.pop();
            }
        }
        if(str[i]=='}'){
            if(bracket.top()=='{'){
                bracket.pop();
            }
        }
    }
    if(bracket.size()==0){
        cout<<"Balanced and properly nested"<<endl;
    }
    else{
        cout<<"No balanced and properly nested"<<endl;
    }

    return 0;
}