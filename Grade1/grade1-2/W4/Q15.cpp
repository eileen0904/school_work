/*請設計一個類別 Point 代表二為平面上的一個點。
Point 這個類別有兩個私有的資料成員 x 跟 y 代表平面上的一個位置，x 跟 y 是浮點數型態的。
建立一個預設建構子，將 x 跟 y 設成 0。
建立一個傳入兩個浮點數參數的建構子，依序用傳入的參數設定 x 跟 y 。
建立一個公開的函數成員 printPoint ，該函數會用 "(x, y)" 這樣的格式做輸出。
建立公開的函數成員 getX setX getY setY 用來存取資料成員 x 跟 y 。
請建立一個公開的函數成員 getDistance ，該函數有一個 Point 型態的參數，會回傳一個浮點數代表兩個點的距離。
請設計一個類別 Segment 代表平面上的一個線段。
Segment 這個類別有兩個私有的資料成員 point1 跟 point2 表示線段的兩個端點。
建立一個預設的建構子將兩個端點預設在 (0, 0) 的位置。
建立一個傳入兩個 Point 物件為參數的建構子用來設定 point1 跟 point2 。
請設計下列函數成員
float getLength(); // 沒有參數，回傳線段的長度*/


#include <iostream>
#include <math.h>
using namespace std;
class Point
{
    float x, y;

public:
    Point()
    {
        x = 0;
        y = 0;
    }
    Point(float a, float b)
    {
        x = a;
        y = b;
    }

    void printPoint()
    {
        cout << "(" << x << ", " << y << ")";
    }
    void setX(float c)
    {
        x = c;
    }
    void setY(float d)
    {
        y = d;
    }
    float getX()
    {
        return x;
    }
    float getY()
    {
        return y;
    }
    float getDistance(Point dis)
    {
        return (sqrt(((x - dis.getX()) * (x - dis.getX())) + ((y - dis.getY()) * (y - dis.getY()))));
    }
};

class Segment
{
    Point a, b;

public:
    Segment()
    {
        a.setX(0);
        a.setY(0);
        b.setX(0);
        b.setY(0);
    }
    Segment(Point p1, Point p2)
    {
        a.setX(p1.getX());
        a.setY(p1.getY());
        b.setX(p2.getX());
        b.setY(p2.getY());
    }
    float getLength()
    {
        return a.getDistance(b);
    }
};