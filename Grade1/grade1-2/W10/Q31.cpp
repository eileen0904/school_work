#include <stdio.h>
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
};

class Segment
{
public:
    Point point1, point2;
    Segment()
    {
        point1.setX(0);
        point1.setY(0);
        point2.setX(0);
        point2.setY(0);
    }
    Segment(Point p1, Point p2)
    {
        point1.setX(p1.getX());
        point1.setY(p1.getY());
        point2.setX(p2.getX());
        point2.setY(p2.getY());
    }
    Segment(Segment &s)
    {
        point1.setX(s.point1.getX());
        point1.setY(s.point1.getY());
        point2.setX(s.point2.getX());
        point2.setY(s.point2.getY());
    }
};

class Shape
{
public:
    Shape();
    Shape(Segment *arr, int count)
    {
        edgeCount = count;
        for (int i = 0; i < edgeCount; i++)
        {
            seg[i] = arr[i];
        }
    }

private:
    Segment seg[10];
    int edgeCount;
};