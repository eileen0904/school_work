#include <iostream>
using namespace std;

template <class T>
class Set
{
public:
    Set()
    {
        count = 0;
    }
    Set(Set &s)
    {
        this->count = s.count;
        for (int i = 0; i < s.count; i++)
        {
            this->element[i] = s.element[i];
        }
    }
    int add(const int a)
    {
        for (int i = 0; i < count; i++)
        {
            if (element[i] == a)
            {
                return 0;
            }
        }
        if (count == 0)
        {
            element[0] = a;
            count++;
        }
        else
        {
            element[count] = a;
            count++;
        }
        return 1;
    }
    int add(const Set &s)
    {
        int k = 0;
        for (int i = 0; i < s.count; i++)
        {
            k = k + add(s.element[i]);
        }
        return k;
    }
    void display()
    {
        int j;
        for (j = 0; j < count; j++)
        {
            cout << element[j] << " ";
        }
    }
    Set &operator+(const Set &s)
    {
        Set *_s = new Set(*this);
        _s->add(s);
        return *_s;
    }
    Set &operator-(const Set &s)
    {
        Set *_s = new Set;
        for (int i = 0; i < this->count; i++)
        {
            for (int j = 0; j < s.count; j++)
            {
                if (this->element[i] == s.element[j])
                {
                    _s->element[_s->count] = this->element[i];
                    _s->count++;
                    break;
                }
            }
        }
        return *_s;
    }

private:
    T element[100];
    int count;
};
