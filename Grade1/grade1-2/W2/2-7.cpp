#include<iostream>
using namespace std;

class bar3d
{
public:
    int width;
    int height;
    int depth;
    bar3d(int a, int b, int c){
        if((a<=1000 && a>=0) && (b<=1000 && b>=0) && (c<=1000 && c>=0)){
            width = a;
            height = b;
            depth = c;
        }
        else{
            width = 0;
            height = 0;
            depth = 0;
        }
    }

};


