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
    Point p1, p2;
    Segment()
    {
        p1.setX(0);
        p1.setY(0);
        p2.setX(0);
        p2.setY(0);
    }
    Segment(Point point1, Point point2)
    {
        p1.setX(point1.getX());
        p1.setY(point1.getY());
        p2.setX(point2.getX());
        p2.setY(point2.getY());
    }
    float getLength()
    {
        return p1.getDistance(p2);
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
    virtual float getArea() = 0;
    int getedgeCount() const
    {
        return edgeCount;
    }
    Segment getSegment(int index) const
    {
        return seg[index];
    }

private:
    Segment seg[10];
    int edgeCount;
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
    bool isCollision(const Rectangle &r)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if ((getSegment(i).p1.getX() == r.getSegment(j).p1.getX()) &&
                    (getSegment(i).p1.getY() == r.getSegment(j).p1.getY()))
                {
                    return true;
                }
            }
        }
        float maxX = getSegment(0).p1.getX();
        float maxY = getSegment(0).p1.getY();
        float minX = getSegment(0).p1.getX();
        float minY = getSegment(0).p1.getY();
        for (int i = 0; i < 4; i++)
        {
            if (getSegment(i).p1.getX() > maxX)
            {
                maxX = getSegment(i).p1.getX();
            }
            if (getSegment(i).p1.getX() < minX)
            {
                minX = getSegment(i).p1.getX();
            }
            if (getSegment(i).p1.getY() > maxY)
            {
                maxY = getSegment(i).p1.getY();
            }
            if (getSegment(i).p1.getY() < minY)
            {
                minY = getSegment(i).p1.getY();
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if ((r.getSegment(i).p1.getX() < maxX) && (r.getSegment(i).p1.getX() > minX) &&
                (r.getSegment(i).p1.getY() < maxY) && (r.getSegment(i).p1.getY() > minY))
            {
                return true;
            }
        }
        return false;
    }
};
