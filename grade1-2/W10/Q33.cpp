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
    float getDistance(Point p)
    {
        return sqrt((x - p.getX()) * (x - p.getX()) + (y - p.getY()) * (y - p.getY()));
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
    float getLength()
    {
        return point1.getDistance(point2);
    }
};

class Shape
{
public:
    Shape()
    {
        this->edgeCount = 0;
    }
    Shape(Segment *arr, int count)
    {
        this->edgeCount = count;
        for (int i = 0; i < count; i++)
        {
            this->seg[i] = arr[i];
        }
    }
    int getedgeCount()
    {
        return edgeCount;
    }
    Segment getSegment(int index)
    {
        return seg[index];
    }

private:
    Segment seg[10];
    int edgeCount;
};

class Triangle : public Shape
{
public:
    float s = 0, a = 0, b = 0, c = 0;
    Triangle(Segment *arr, int count) : Shape(arr, count) {}
    float getPerimeter()
    {
        a = getSegment(0).getLength();
        b = getSegment(1).getLength();
        c = getSegment(2).getLength();
        float perimemeter = a + b + c;
        return perimemeter;
    }
    float getArea()
    {
        s = (a + b + c) / 2;
        float area = sqrt(s * (s - a) * (s - b) * (s - c));
        return area;
    }
};

/*int main()
{
    Point p1(0, 0), p2(2, 0), p3(2, 1), p4(0, 1);
    Segment L1(p1, p2);
    Segment L2(p2, p3);
    Segment L3(p3, p4);
    Segment L4(p4, p1);
    Segment arr[10];
    arr[0] = L1;
    arr[1] = L2;
    arr[2] = L3;
    arr[3] = L4;
    Segment *seg = &arr[0];
    Triangle tri(seg, 3);
    cout << tri.getPerimeter() << "," << tri.getArea();
    return 0;
}*/