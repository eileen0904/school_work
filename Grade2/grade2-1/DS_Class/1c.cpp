#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
using namespace std;

int main(){
    ifstream file;
    file.open("1cQ.txt");
    string str;
    map<char, int> alpha_count;
    while(getline(file, str)){
        int index=0;
        while((index=str.find(' ', index))!=-1){
            str.erase(index,1);
        }
        for(int i=0;i<str.size();i++){
            alpha_count[str[i]]++;
        }
        str.clear();
    }
    map<char, int>::iterator iter;
    for(iter=alpha_count.begin(); iter!=alpha_count.end(); iter++){
        cout<<iter->first<<" ";
        for(int i=0;i<iter->second;i++){
            cout<<"*";
        }
        cout<<iter->second<<endl;
    }
    file.close();

    return 0;
}
