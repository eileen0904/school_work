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