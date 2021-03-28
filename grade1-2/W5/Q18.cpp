/*Please create a class IntNumber using Digit that you create in Q17 represent a very huge number in integer.
The class IntNumber can handle an integer number up to 1000 digit and both positive and negative number.
Create two constructor for this class, one with no parameter and set number to 0, 
another one with a string type(char * not string) parameter and set number to what the string represent.
Create a function member display to display the number.*/


#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;

class Digit
{
    int digit;
public:
    Digit(){
        digit = 0;
    }
    Digit(int a){
        if(a>=0 && a<=9){
            digit = a;
        }
        else{
            digit = 0;
        }
    }
    void setDigit(int b){
        if(b>=0 && b<=9){
            digit = b;
        }
        else{
            digit = 0;
        }
    }
    int getDigit(){
        return digit;
    }
};

class IntNumber
{
    int num;
public:
    IntNumber(){
        num = 0;
    }

    Digit digit[10000];
    int k, m, op;
    IntNumber(char *c){
        string number(c);
        int i, n=0, not_zero=0;
        k=0;
        op=0;
        m=0;
        for(i=0;i<number.length();i++){
            if(isalpha(number[i])){
                break;
            }
            if(number[0]=='-'){
                op=1;
            }
            if(number[i]>'0' && number[i]<='9'){
                not_zero=1;
            }
            if(isdigit(number[i]) && not_zero==1 && op!=0){
                digit[m].setDigit(number[i]-48);
                m++;
            }
            if(isdigit(number[i]) && not_zero==1 && op==0){
                digit[k].setDigit(number[i]-48);
                k++;
            }
        }
    }

    void display(){
        if(k==0 && m==0){
            cout<<"0";
            return;
        }
        if(op==1){
            cout<<'-';
            for(int i=0;i<m;i++){
                cout<<digit[i].getDigit();
            }
        }
        if(op==0){
           for(int i=0;i<k;i++){
                cout<<digit[i].getDigit();
            }
        }
    }
};

int main()
{
  char num[10000];
  cin>>num;
  IntNumber *number = new IntNumber(num);
  number-> display();
  return 0;
}