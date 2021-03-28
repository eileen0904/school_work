/*Please create a class Digit represent a single digit in base ten.
Class Digit should contain two constructor, one with no parameter and set digit to 0, 
another one with one integer parameter and use the parameter to set the digit.
Create two function member setDigit and getDigit to set and get the digit int integer type. 
You should set digit to 0 if setDigit receive a unreasonable parameter.
Constructor may also get unreasonable parameter too.*/


#include <iostream>
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