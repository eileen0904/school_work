/*請設計一個類別 Point 代表二為平面上的一個點。
Point 這個類別有兩個私有的資料成員 x 跟 y 代表平面上的一個位置，x 跟 y 是浮點數型態的。
建立一個預設建構子，將 x 跟 y 設成 0。
建立一個傳入兩個浮點數參數的建構子，依序用傳入的參數設定 x 跟 y 。
建立一個公開的函數成員 printPoint ，該函數會用 "(x, y)" 這樣的格式做輸出。*/


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