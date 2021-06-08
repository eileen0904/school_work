#include <iostream>
using namespace std;

template <class T>
void exange(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}