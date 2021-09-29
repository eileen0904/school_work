/*Please create a class Decode to encode a string.
Create a constructor with a string type(string not char *) parameter to construct the object.
Create a function memberstring decode();return the string after decoding.
The coding method are the same as Q20.
You can add any data member or function member you need to the class.*/


#include <iostream>
#include <string>
using namespace std;

class Decode
{
  public:
    string str;
    Decode(string _str){
      str = _str;
    }
    string decode(){
      string decoded;
      char s[3];
      int num=0, temp=0;
      while(temp<str.size()){
        for(int i=0;i<3;i++){
          s[i] = str[i+temp];
        }
        temp = temp + 3;
        num = atoi(s);
        decoded = decoded + (char)num;
      }
      return decoded;
    }
};
int main() {
  string str;
  cin>>str;
  Decode *code = new Decode(str);
  cout<<code->decode();
  return 0;
}