/*Please create a class Encode to encode a string.
Create a constructor with a string type(string not char *) parameter to construct the object.
Create a function memberstring encode();return the string after encoding.
For a string like "Hello World!", we first convert it to integer, so 'H' become 72, 'e' become 101, 'l' become 108 and so on.
"Hello World!" become 72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33
We pad '0' in the front if the integer is less than 3 digit.
072, 101, 108, 108, 111, 032, 087, 111, 114, 108, 100, 033
"Hello World!" after encode become "072101108108111032087111114108100033"
You can add any data member or function member you need to the class.*/


#include <iostream>
#include <string>
using namespace std;

class Encode
{
  public:
    string str;
    Encode(string _str){
      str = _str;
    }
    string encode(){
      string encoded;
      for(int i=0; i<str.size();i++){
        if(int(str[i])<10){
          encoded = encoded + '0' + '0' + to_string(int(str[i]));
        }
        else if(int(str[i])<100 && int(str[i])>10){
          encoded = encoded + '0' + to_string(int(str[i]));
        }
        else{
          encoded = encoded + to_string(int(str[i]));
        }
      }
      return encoded;
    }
};
int main() {
  string str;
  getline(cin,str);
  Encode *code = new Encode(str);
  cout<<code->encode();
  return 0;
}
