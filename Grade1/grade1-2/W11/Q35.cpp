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
        for (int i = 0; i < count - 1; i++)
        {
            if ((seg[i].point2.getX() != seg[i + 1].point1.getX()) &&
                (seg[i].point2.getY() != seg[i + 1].point1.getY()) &&
                (seg[count - 1].point2.getX() != seg[0].point1.getX()) &&
                (seg[count - 1].point2.getY() != seg[0].point1.getY()))
            {
                throw invalid_argument("");
            }
        }
    }
    virtual float getArea() = 0;
    float getPerimeter()
    {
        float sum = 0;
        for (int i = 0; i < edgeCount; i++)
        {
            sum = sum + seg[i].getLength();
        }
        return sum;
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

class Square : public Shape
{
public:
    Square(Segment *arr) : Shape(arr, 4) {}
    float getArea()
    {
        return getSegment(0).getLength() * getSegment(0).getLength();
    }
};

class Rectangle : public Shape
{
public:
    Rectangle(Segment *arr) : Shape(arr, 4) {}
    float getArea()
    {
        float width = getSegment(0).getLength();
        float height = getSegment(1).getLength();
        return width * height;
    }
};
