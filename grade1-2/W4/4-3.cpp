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
    void setX(float c){
        x=c;
    }
    void setY(float d){
        y=d;
    }
    float getX(){
        return x;
    }
    float getY(){
        return y;
    }

};
