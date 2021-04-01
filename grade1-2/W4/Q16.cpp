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
float getLength(); // 沒有參數，回傳線段的長度
Point *getIntersect(Segment s);//傳入另一個線段，回傳兩個線段的交點，如果不存在交點，回傳 NULL*/

 
#include <iostream>
#include <math.h>
using namespace std;

class Point
{
    float x, y;
public:
    Point(){
        x = 0;
        y = 0;
    }
    Point(float a, float b){
        x = a;
        y = b;
    }
    void printPoint(){
        cout << "(" << x << ", " << y << ")";
    }
    void setX(float c){
        x = c;
    }
    void setY(float d){
        y = d;
    }
    float getX(){
        return x;
    }
    float getY(){
        return y;
    }
    float getDistance(Point dis){
        return (sqrt(((x - dis.getX()) * (x - dis.getX())) + ((y - dis.getY()) * (y - dis.getY()))));
    }
};

class Segment
{
    Point p1, p2;
public:
    Segment(){
        p1.setX(0);
        p1.setY(0);
        p2.setX(0);
        p2.setY(0);
    }
    Segment(Point a, Point b){
        p1.setX(a.getX());
        p1.setY(a.getY());
        p2.setX(b.getX());
        p2.setY(b.getY());
    }

    float getLength(){
        return p1.getDistance(p2);
    }

    double a=0, b=0, c=0;
    void getline(Segment &m){ //&=>copy constractor
        m.a = m.p1.getY()-m.p2.getY();
        m.b = m.p2.getX()-m.p1.getX();
        m.c = m.p1.getX()*m.p2.getY()-m.p2.getX()*m.p1.getY();
    }

    Point *getIntersect(Segment s){ //s=>L2, t=>L1
        Segment t(p1,p2);
        getline(t);
        getline(s);
        Point *p = new Point();
        double D = t.a*s.b-s.a*t.b;
        if(D==0){ //parallel
            if (t.p1.getX()==s.p1.getX() && t.p1.getY()==s.p1.getY()){
                p -> setX(t.p1.getX());
                p -> setY(t.p1.getY());
                return p;
            }
            if(t.p1.getX()==s.p2.getX() && t.p1.getY()==s.p2.getY()){
                p -> setX(t.p1.getX());
                p -> setY(t.p1.getY());
                return p;
            }
            if(t.p2.getX()==s.p1.getX() && t.p2.getY()==s.p1.getY()){
                p -> setX(t.p2.getX());
                p -> setY(t.p2.getY());
                return p;
            }
            if(t.p2.getX()==s.p2.getX() && t.p2.getY()==s.p2.getY()){
                p -> setX(t.p2.getX());
                p -> setY(t.p2.getY());
                return p;
            }
            return NULL;
        }
        float insX = (t.b*s.c-s.b*t.c)/D;
        float insY = (s.a*t.c-t.a*s.c)/D;
        if(insX==-0){insX = 0;}
        if(insY==-0){insY = 0;}
        if(ins(t.p1.getX(),t.p2.getX(),insX) && ins(s.p1.getX(),s.p2.getX(),insX) && 
            ins(t.p1.getY(),t.p2.getY(),insY) && ins(s.p1.getY(),s.p2.getY(),insY)){
            p -> setX(insX);
            p -> setY(insY);
            return p;
        }
        else{
            return NULL;
        }
    }

bool ins(float n1, float n2, float pt){
        if(pt>=n1 && pt<=n2){return true;}
        if(pt<=n1 && pt>=n2){return true;}
        return false;
    }
};

int main(){
  Point p1(1, 1);
  Point p2(3, 1);
  Point p3(2, 1);
  Point p4(3, 1);
  Segment L1(p1,p2);
  Segment L2(p3,p4);
  Point *intersect = L1.getIntersect(L2);
  cout<<intersect -> getX() << " " << intersect -> getY();

  return 0;
}