#include<iostream>
using namespace std;
class Point
{
   float x,y;
   public:
   	Point(){
        x=0;
        y=0;
    }
    Point(float a, float b){
        x=a;
        y=b;
    }
   
    void printPoint(){
    	cout<<"("<< x <<", "<< y <<")";
    }
};