/*Please create a class Fraction represent a fraction number.
Create a default constructor to set the fraction number to 0.
Create a constructor Fraction(int numerator, int denominator)
The class Fraction should include the following function member at least,
int getNumerator(); // return the numerator of the fraction number.
int getDenominator(); // return the denominator of the fraction number.
void setNumerator(int ); // use the parameter to set numerator of the fraction.
void setDenominator(int ); // use the parameter to set denominator of the fraction.
void display(); // display the irreducible fractionas the format "(numerator/denominator)". 
e.g. (5/9). you should not display denominator if denominator is 1.*/


#include <iostream>
using namespace std;

class Fraction
{   
    int fraction;
    int numerator;
    int denominator;
public:
    Fraction(){
        numerator = 0;
        denominator = 0;
    }
    Fraction(int numerator, int denominator){
        this->numerator = numerator;
        this->denominator = denominator;
    }
    int getNumerator(){
        return numerator;
    }
    int getDenominator(){
        return denominator;
    }
    void setNumerator(int a){
        numerator = a;
    }
    void setDenominator(int b){
        denominator = b;
    }
    int reduction(int _n, int _d){
        int r;
        int n = abs(_n);
        int d = abs(_d);
        while(d>0){
            r = n%d;
            n = d;
            d = r;
        }
        return n;
    }
    void display(){
        int c = reduction(numerator, denominator);
        this->numerator = numerator/c;
        this->denominator = denominator/c;
        if(denominator==1){
            cout<<"("<<numerator<<")";
        }
        else{
            cout<<"("<<numerator<<"/"<<denominator<<")";
        }
    }
};