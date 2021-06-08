/*UVa1727*/

#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int i, n;
    cin>>n;
    while(n--)
    {
        string s1, s2;
        cin>>s1>>s2;
        int m=0, d=0;
        if(s1=="FEB"){m = 28;}
        else if(s1=="JAN" || s1=="MAR" || s1=="MAY" || s1=="JUL" || s1=="AUG" || s1=="OCT" || s1=="DEC")
        {
            m = 31;
        }
        else
        {
            m = 30;
        }
        if(s2=="SUN"){d = 1;}
        if(s2=="MON"){d = 2;}
        if(s2=="TUE"){d = 3;}
        if(s2=="WED"){d = 4;}
        if(s2=="THU"){d = 5;}
        if(s2=="FRI"){d = 6;}
        if(s2=="SAT"){d = 7;}

        if(m==28){cout<<"8"<<endl;}
        if((m==30 || m==31) && (d==1 || d==2 || d==3)){cout<<"8"<<endl;}
        if(m==30 && d==4){cout<<"8"<<endl;}
        if(m==31 && d==4){cout<<"9"<<endl;}
        if(m==30 && d==5){cout<<"9"<<endl;}
        if(m==31 && d==5){cout<<"10"<<endl;}
        if((m==30 || m==31) && d==6){cout<<"10"<<endl;}
        if((m==30 || m==31) && d==7){cout<<"9"<<endl;}
    }
    return 0;
}
