#include<iostream>
using namespace std;

class Set
{
  public:
    Set(){
        count = 0;
    }

    Set(const Set &s){

    }

    int add(const int a){
        for(int i=0;i<count;i++){
            if(element[i]==a){
                return 0;
            }
        }
        if(count==0){
            element[0] = a;
            count++;
        }
        else{
            element[count] = a;
            count++;
        }
        return 1;
    }

    int add(const Set &s2){
        int k = 0;
        for(int i=0;i<s2.count;i++){
            k = k + add(s2.element[i]);
        }
        return k;
    }

  	void display(){
      int j;
      for(j=0;j<count;j++){
        cout<<element[j]<<" ";
      }
    }

  private:
  	int element[100];
  	int count;
};

/*int main(){
    Set s1, s2;
    cout << s1.add(1) << endl;
    cout << s1.add(2) << endl;
    cout << s1.add(3) << endl;
    cout << s2.add(3) << endl;
    cout << s2.add(4) << endl;
    cout << s1.add(s2) << endl;
    s1.display();

    return 0;
}*/