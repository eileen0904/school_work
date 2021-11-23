#include<iostream>
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

    Set setUnion(const Set &s){
        Set *_s = new Set(*this);
        _s->add(s);
        return *_s;
    }
    Set setIntersection(const Set &s){
        Set *_s = new Set;
        for(int i=0;i<count;i++){
            for(int j=0;j<s.count;j++){
                if(element[i]==s.element[j]){
                    _s->element[_s->count] = element[i];
                    _s->count++;
                    break;
                }
            }
        }
        return *_s;
    }
    Set setDifference(const Set &s){
        Set *_s = new Set;
        int not_same=0;
        for(int i=0;i<count;i++){
            for(int j=0;j<s.count;j++){
                if(element[i]!=s.element[j]){
                    not_same++;
                }
            }
            if(not_same==s.count){
                _s->element[_s->count] = element[i];
                _s->count++;
            }
            not_same = 0;
        }
        return *_s;
    }

  private:
  	int element[100];
  	int count;
};

int main()
{
    Set s1, s2, s3, s4, s5;
    s1.add(1);
    s1.add(2);
    s1.add(3);
    s1.add(3);
    s1.add(4);
    s1.add(8);
    s2.add(5);
    s2.add(6);
    s2.add(1);
    s2.add(2);
    s1.display();
    cout<<endl;
    s2.display();
    cout<<endl;
    s3 = s1.setUnion(s2);
    s3.display();
    cout<<endl;
    s4 = s1.setIntersection(s2);
    s4.display();
    cout<<endl;
    s5 = s1.setDifference(s2);
    s5.display();
}
