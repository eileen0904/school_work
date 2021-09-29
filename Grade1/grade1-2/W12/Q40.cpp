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

class TimeSpan
{
public:
    TimeSpan()
    {
        day = 0;
        hour = 0;
        minute = 0;
        second = 0;
    }
    TimeSpan(int d, int hh, int mm, int ss)
    {
        day = d;
        hour = hh;
        minute = mm;
        second = ss;
    }
    void setDay(int d)
    {
        day = d;
    }
    void setHour(int h)
    {
        hour = h;
    }
    void setMin(int m)
    {
        minute = m;
    }
    void setSec(int s)
    {
        second = s;
    }
    int getDay()
    {
        return day;
    }
    int getHour()
    {
        return hour;
    }
    int getMin()
    {
        return minute;
    }
    int getSec()
    {
        return second;
    }
    int toTotalDays();
    int toTotalHours();
    int toTotalMinutes();
    int toTotalSeconds()
    {
        return second;
    }
    string toString()
    {
        return "no";
    }

private:
    int day, hour, minute, second;
};

class DateTime : public Date
{
public:
    virtual string toString()
    {
        string mm, dd, yy;
        string HH, MM, SS;
        string mdyHMS;
        if (getMonth() < 10)
        {
            mm = '0' + to_string(getMonth());
        }
        else
        {
            mm = to_string(getMonth());
        }
        if (getDay() < 10)
        {
            dd = '0' + to_string(getDay());
        }
        else
        {
            dd = to_string(getDay());
        }
        yy = to_string(getYear());
        if (hour < 10)
        {
            HH = '0' + to_string(hour);
        }
        else
        {
            HH = to_string(hour);
        }
        if (minute < 10)
        {
            MM = '0' + to_string(minute);
        }
        else
        {
            MM = to_string(minute);
        }
        if (second < 10)
        {
            SS = '0' + to_string(second);
        }
        else
        {
            SS = to_string(second);
        }
        mdyHMS = mm + "/" + dd + "/" + yy + " " + HH + ":" + MM + ":" + SS;
        return mdyHMS;
    }
    DateTime() : Date()
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
    DateTime(int y, int m, int d, int hh = 0, int mm = 0, int ss = 0) : Date(y, m, d)
    {
        hour = hh;
        minute = mm;
        second = ss;
    }
    void setHour(int h)
    {
        hour = h;
    }
    void setMinute(int m)
    {
        minute = m;
    }
    void setSecond(int s)
    {
        second = s;
    }
    int getHour() const
    {
        return hour;
    }
    int getMinute() const
    {
        return minute;
    }
    int getSecond() const
    {
        return second;
    }
    void addHours(int h)
    {
        hour = hour + h;
        if (hour >= 24)
        {
            int aday = hour / 24;
            addDays(aday);
            hour = hour % 24;
        }
    }
    void addMinutes(int m)
    {
        minute = minute + m;
        if (minute >= 60)
        {
            int ahour = minute / 60;
            addHours(ahour);
            minute = minute % 60;
        }
    }
    void addSeconds(int s)
    {
        second = second + s;
        if (second >= 60)
        {
            int amin = second / 60;
            addMinutes(amin);
            second = second % 60;
        }
    }
    TimeSpan operator-(const DateTime &dt) const
    {
        TimeSpan *ts = new TimeSpan();
        DateTime d = (*this);
        int addsec = 0;
        while (true)
        {
            if (d.getYear() == dt.getYear() && d.getMonth() == dt.getMonth() && d.getDay() == dt.getDay() &&
                d.getHour() == dt.getHour() && d.getMinute() == dt.getMinute() && d.getSecond() == dt.getSecond())
            {
                break;
            }
            addsec++;
            d.addSeconds(1);
        }
        ts->setSec(addsec);
        return *ts;
    }

private:
    int hour, minute, second;
};

int main()
{
    int y, m, d, hh, mm, ss;
    cin >> y >> m >> d >> hh >> mm >> ss;
    DateTime d1(y, m, d, hh, mm, ss);
    cin >> y >> m >> d >> hh >> mm >> ss;
    DateTime d2(y, m, d, hh, mm, ss);
    cout << (d1 - d2).toTotalSeconds();
    return 0;
}
