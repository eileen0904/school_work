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
    void getline(Segment &m){
        m.a = m.p1.getY()-m.p2.getY();
        m.b = m.p2.getX()-m.p1.getX();
        m.c = m.p1.getX()*m.p2.getY()-m.p2.getX()*m.p1.getY();
    }
    Point *getIntersect(Segment s){
        Segment t(p1,p2);
        getline(t);
        getline(s);
        Point *p = new Point();
        double D = t.a*s.b-s.a*t.b;
        if(D==0){
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
        else{return NULL;}
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