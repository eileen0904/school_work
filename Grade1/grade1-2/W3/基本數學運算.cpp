#include<iostream>
#include<iomanip>
using std::setprecision;
using std::fixed;

int main(){
    int a,b;
    std::cin>>a>>b;
    std::cout<<a<<"+"<<b<<"="<<a+b<<std::endl;
    std::cout<<a<<"-"<<b<<"="<<a-b<<std::endl;
    std::cout<<a<<"*"<<b<<"="<<a*b<<std::endl;
    std::cout<<fixed<<setprecision(4)<<a<<"/"<<b<<"="<<(float)a/b<<std::endl;
    std::cout<<a<<"%"<<b<<"="<<a%b;

    return 0;
}