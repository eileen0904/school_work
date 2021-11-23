#include <bits/stdc++.h>
using namespace std;

vector<string> alpha;
void decode(string s){
    int n=0, num[100];
    for(int i=0;i<s.size();i++){
        if(s[i]>=49 && s[i]<=57){
            int temp = i+2;
            while(isalpha(s[temp])){
                temp++;
            }
            string s1;
            s1.assign(s, i+2, temp-i-2);
            alpha.push_back(s1);
            num[n] = s[i] - 48;
            n++;
        }
    }
    string s1, s2;
    for(int i=n-1;i>=0;i--){
        int j = num[i];
        s1 = alpha[i] + s2;
        s2.clear();
        while(j--){
            s2 = s2 + s1;
        }
    }
    cout<<"Decode:"<<s2<<endl;
}

char *encode(char *str)
{
    char *front = new char[1000] ;
    char *end = new char[1000] ;
    char *target = new char[1000] ;
    char *ans = new char[1000] ;
    int l, i, c ;
    char *t ;
    l = strlen(str) / 2 ;
    while(l > 0){
        for(i=0;i+l*2-1<strlen(str);i++){
            strncpy(target, str + i, l) ;
            target[l] = '\0' ;
            t = str + l + i ;
            c = 1 ;
            while(strncmp(target, t, l) == 0){
                c++ ;
                t += l ;
            }
            if(c > 1){
                strncpy(front, str, i) ;
                strcpy(front, encode(front)) ;
                front[i] = '\0' ;
                char buf[100] ;
                strcpy(buf, encode(target)) ;
                char *a = buf ;
                int base = 0 ;
                while((*a + 2) / 10 == 5){
                    base = base * 10 + *a - '0' ;
                    a++ ;
                }
                if(*a == '[' && buf[strlen(buf) - 1] == ']'){
                    c = c * base ;
                    strcpy(target, a + 1) ;
                    target[strlen(target) - 1] = '\0' ;
                    l = strlen(target) ;
                    while(strncmp(target, t, l) == 0){
                        c++ ;
                        t += l ;
                    }
                }
                else strcpy(target, buf) ;
                strcpy(end, t) ;
                strcpy(end, encode(end)) ;
                sprintf(ans, "%s%d[%s]%s", front, c, target, end) ;
                return ans ;
            }
        }
        l-- ;
    }
    strcpy(ans, str) ;
    return ans ;
}

int main(){
    string str1, str2;
    str1 = "2[rt2[sr3[pt]]]";
    str2 = "abcdeecdeecdeeabcdeecdeecdee";
    decode(str1);
    char *c = &str2[0] ;
    cout <<"Encode:"<<encode(c)<<endl ;
    return 0;
}
