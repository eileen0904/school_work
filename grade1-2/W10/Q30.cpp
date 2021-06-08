//UVa508

#include <iostream>
#include <cstring>
#include <vector>
#include <math.h>
using namespace std;

char ch[100];            //charater
vector<string> morse;    //對應的moscode
vector<string> dict;     //word
vector<string> encode;   //undecode
vector<string> dictcode; //dict->moscode

string decode(string s)
{
    string result;
    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 0; j < 36; j++)
        {
            if (s[i] == ch[j])
            {
                result = result + morse[j];
                break;
            }
        }
    }
    return result;
}
string solve(string qs)
{
    int i, j, dictcode_len = 0, match = 0;
    int abs_match_n = 0, abs_match = 0;
    int rel_match_len = 100, rel_match_n = 0, rel_match = 0;
    int qs_len = qs.size();
    for (i = 0; i < dictcode.size(); i++)
    {
        dictcode_len = dictcode[i].size();
        match = 0;
        for (j = 0; j < dictcode_len && j < qs_len; j++)
        {
            if (qs[j] == dictcode[i].at(j))
            {
                match++;
            }
            else
            {
                break;
            }
        }
        if (match == qs_len && qs_len == dictcode_len) //accurate
        {
            if (abs_match_n < 1)
            {
                abs_match = i;
            }
            abs_match_n++;
        }
        else if ((match == dictcode_len && match < qs_len) || (match < dictcode_len && match == qs_len)) //indistinct
        {
            if (rel_match_len > abs(dictcode_len - qs_len))
            {
                rel_match_len = abs(dictcode_len - qs_len);
                rel_match = i;
                rel_match_n++;
            }
        }
    }
    if (abs_match_n > 0)
    {
        if (abs_match_n > 1)
        {
            return dict[abs_match] + "!";
        }
        else
        {
            return dict[abs_match];
        }
    }
    if (rel_match_n > 0)
    {
        return dict[rel_match] + '?';
    }
}

int main()
{
    char c;
    int i, j, count = 0;
    while (cin >> c && c != '*')
    {
        string str; //對應的morse
        cin >> str;
        ch[count] = c; //charater
        count++;
        morse.push_back(str);
    }
    string temp;
    while (cin >> temp && temp[0] != '*')
    {
        dict.push_back(temp); //dictionary
        temp.clear();
    }
    while (cin >> temp && temp[0] != '*')
    {
        encode.push_back(temp); //question
        temp.clear();
    }
    for (i = 0; i < dict.size(); i++)
    {
        string tmp = decode(dict[i]); //dict->moscode
        dictcode.push_back(tmp);
    }
    for (i = 0; i < encode.size(); i++)
    {
        cout << solve(encode[i]) << endl;
    }
    return 0;
}
