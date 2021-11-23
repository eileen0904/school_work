#include<iostream>
#include<climits>
#include<cstring>
using namespace std;

class Set
{
  public:
    Set(){
        count = 0;
    }

    Set(const Set &s){
        this->count = s.count;
        for(int i=0;i<count;i++){
            this->element[i] = s.element[i];
        }
    }

    int add(const char a){
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

    int compareWordSets(const Set &s2){
        int same=0;
        for(int i=0;i<count;i++){
            for(int j=0;j<s2.count;j++){
                if(element[i]==s2.element[j]){
                    same++;
                }
            }
        }
        if(count<s2.count && same==count){
            return -1; //proper subset
        }
        else if(count>s2.count && same==s2.count){
            return 1; //proper superset
        }
        else if(same==count && same==s2.count){
            return 0; //equivalent
        }
        else{
            return INT_MAX; // incomparable
        }
    }

  private:
  	char element[100];
  	int count;
};

int main()
{
    Set s1, s2;
    s1.add('a');
    s1.add('b');
    s1.add('c');
    s1.add('c');
    s1.add('d');
    s1.add('e');
    s2.add('c');
    s2.add('d');
    s2.add('b');
    s2.add('a');
    s1.display();
    cout<<endl;
    s2.display();
    cout<<endl;
    if(s1.compareWordSets(s2)==-1){
        cout<<"proper subset"<<endl;
    }
    else if(s1.compareWordSets(s2)==1){
        cout<<"proper superset"<<endl;
    }
    else if(s1.compareWordSets(s2)==0){
        cout<<"equivalent"<<endl;
    }
    else{
        cout<<"incomparable"<<endl;
    }
}
