#include <iostream>
#include <cstring>
using namespace std;

class Date
{
public:
    Date()
    {
        year = 1;
        month = 1;
        day = 1;
    }
    Date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }
    virtual string toString()
    {
        string mm, dd, yy, mdy;
        if (month < 10)
        {
            mm = '0' + to_string(month);
        }
        else
        {
            mm = to_string(month);
        }
        if (day < 10)
        {
            dd = '0' + to_string(day);
        }
        else
        {
            dd = to_string(day);
        }
        yy = to_string(year);
        mdy = mm + ", " + dd + ", " + yy;
        return mdy;
    }
    void setDay(int d)
    {
        day = d;
    }
    void setMonth(int m)
    {
        month = m;
    }
    void setYear(int y)
    {
        year = y;
    }
    int getDay() const
    {
        return day;
    }
    int getMonth() const
    {
        return month;
    }
    int getYear() const
    {
        return year;
    }
    void addDays(int d)
    {
        int mday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        day = day + d;
        if (isLeapYear(*this))
        {
            mday[2] = 29;
        }
        while (day > mday[month])
        {
            day = day - mday[month];
            month++;
            if (month == 13)
            {
                month = 1;
                year++;
                if (isLeapYear(*this))
                {
                    mday[2] = 29;
                }
                else
                {
                    mday[2] = 28;
                }
            }
        }
    }
    void addMonths(int m)
    {
        month = month + m;
        int tempy = month / 12;
        year = year + tempy;
        month = month % 12;
    }
    void addYears(int y)
    {
        year = year + y;
    }
    static bool isLeapYear(const Date &d)
    {
        if ((d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    int year, month, day;
};
int main()
{
    int n;
    Date d(2021, 1, 1);
    cin >> n;
    d.addDays(n);
    cout << d.toString() << endl;
    cin >> n;
    d.addMonths(n);
    cout << d.toString() << endl;
    cin >> n;
    d.addYears(n);
    cout << d.toString() << endl;
    return 0;
}
