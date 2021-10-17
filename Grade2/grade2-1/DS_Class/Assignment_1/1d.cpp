#include <iostream>
#include <exception>
using namespace std;

int calculate(char o, int n1, int n2){
    switch(o){
        case '+': return n1+n2;
        case '-': return n1-n2;
        case '*': return n1*n2;
        case '/': return n1/n2;
    }
}

int main(){
    char op;
    int a, b;
    while(1){
        cout<<"Input operator, integer, integer"<<endl;
        cout<<"Input \"=\" to end the program"<<endl;
        try{
            cin>>op;
            if(op=='='){break;}
            if(op!='+' && op!='-' && op!='*' && op!='/'){
                throw "Operator error";
            }
            cin>>a>>b;
            if(op=='/' && b==0){
                throw "Number error";
            }
            int result = calculate(op, a, b);
            cout<<result<<endl;
        }
        catch(char const* error){
            cout<<error<< endl;
        }
    }

    return 0;
}