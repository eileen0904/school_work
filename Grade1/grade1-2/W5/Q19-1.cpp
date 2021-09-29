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
    int n;
public:
    IntNumber(){
        n = 0;
    }

    Digit digit[10000];
    int k, op;
    char *num;
    IntNumber(char *c){
        num = c;
        string number(c);
        int i, not_zero=0;
        k=0;
        op=0;
        for(i=0;i<number.length();i++){
            if(isalpha(number[i])){
                break;
            }
          	if(number[0]=='+'){
              	op=0;
            }
            if(number[0]=='-'){
                op=1;
            }
            if(number[i]>'0' && number[i]<='9'){
                not_zero=1;
            }
            if(isdigit(number[i]) && not_zero==1){
                digit[k].setDigit(number[i]-48);
                k++;
            }
        }
    }
    
    void display(){
        if(k==0){
            cout<<"0";
            return;
        }
        if(op==1){
            cout<<'-';
            for(int i=0;i<k;i++){
                cout<<digit[i].getDigit();
            }
        }
        if(op==0){
           for(int i=0;i<k;i++){
                cout<<digit[i].getDigit();
            }
        }
    }

    IntNumber *add(const IntNumber *number2)const {
        long long int sum = 0;
        sum = atoll(num) + atoll(number2->num);
        string _sum = to_string(sum);
        char *result = &_sum[0];
        return new IntNumber(result);
    }
        
};

int main()
{
  char num1[10000], num2[10000];
  cin>>num1>>num2;
  IntNumber *number1 = new IntNumber(num1);
  IntNumber *number2 = new IntNumber(num2);
  number1->display();
  cout<<endl;
  number2->display();
  cout<<endl;
  number1->add(number2)->display();
  cout<<endl;
  number2->add(number1)->display();
  return 0;
}