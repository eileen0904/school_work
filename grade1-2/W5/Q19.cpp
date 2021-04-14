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
    bool n1_big = false;
    int k, op;
    IntNumber(char *c){
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
    void JudgeBig(IntNumber *s){ //from to high to low
        for(int j=0;j<this->k;j++){
            if(this->digit[j].getDigit() == s->digit[j].getDigit()){
                continue;
            }
            if(this->digit[j].getDigit() > s->digit[j].getDigit()){
                n1_big = true;
                break;
            }
            if(this->digit[j].getDigit() < s->digit[j].getDigit()){
                break;
            }
        }
    }
    void reverse(IntNumber *v, int length){
        for(int j=0;j<length/2;j++){
            int temp = v->digit[j].getDigit();
            v->digit[j].setDigit(v->digit[length-1-j].getDigit());
            v->digit[length-1-j].setDigit(temp);
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

    IntNumber *add(const IntNumber *data2)const {
        IntNumber *n1 = new IntNumber(*this);
        IntNumber *n2 = new IntNumber(*data2);
        IntNumber *result = new IntNumber(*this);
        int len1 = n1->k;
        int len2 = n2->k;
        int len = 0;    //length of result
        int a=0, b=0, carry=0, sum=0, i;
        if(len2 > len1){
            return data2->add(this);
        }
        if((n1->op==0 && n2->op==0) || (n1->op==1 && n2->op==1)){
            if(n1->op==1 && n2->op==1){
                result->op = 1;
            }
            while(len1>0){
                a = n1->digit[len1-1].getDigit();
                if(len2>0){
                    b = n2->digit[len2-1].getDigit();
                }
                else{
                    b = 0;
                }
                sum = a+b+carry;
                if(sum>=10){
                    result->digit[len].setDigit(sum%10);
                    carry = 1;
                }
                else{
                    result->digit[len].setDigit(sum);
                    carry = 0;
                }
                len1--;
                len2--;
                len++;
            }
            if(len == n1->k && carry==0){
                result->k = n1->k;
            }
            else{
                len++;
                result->k = n1->k+1;
                result->digit[len-1].setDigit(1);
            }
        }
        if((n1->op==0 && n2->op==1) || (n1->op==1 && n2->op==0)){
            n1->JudgeBig(n2);
            if(n1->n1_big){
                if(n1->op==1){
                    result->op = 1;
                }
                else{
                    result->op = 0;
                }
                while(len1>0){
                    a = n1->digit[len1-1].getDigit();
                    if(len2>0){
                        b = n2->digit[len2-1].getDigit();
                    }
                    else{
                        b = 0;
                    }
                    sum = a-b-carry;
                    if(sum<0){
                        sum = sum+10;
                        result->digit[len].setDigit(sum);
                        carry = 1;
                    }
                    else{
                        result->digit[len].setDigit(sum);
                        carry = 0;
                    }
                    len1--;
                    len2--;
                    len++;
                }
                for(i=len-1;i>0;i--){
                    if(result->digit[i].getDigit()==0){ //delete 0 from high
                        result->k = n1->k-1;
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                return data2->add(this);
            }
        }
        result->reverse(result, result->k);
        return result;
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
