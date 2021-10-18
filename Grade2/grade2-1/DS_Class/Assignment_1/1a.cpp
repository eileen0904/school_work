#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int guessB(int low){
    srand(time(NULL));
    int num = (rand() % (100-low)+1) + low;
    return num;
}

int guessH(int high){
    srand(time(NULL));
    int num = (rand() % (high-1)+1) + 1;
    return num;
}

void swap(int *a, int *b){
    int tmp=0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
int main()
{
    int count=0;
    cout<<"Please determine a number between 1~100."<<endl;
    srand(time(NULL));
    int min = (rand() % 100) + 1;
    int max = (rand() % 100) + 1;
    int win=0;
    if(max<min){
        swap(&min, &max);
    }
    while(count<4){
        string s;
        cout<<"The number is between ("<<min<<","<<max<<")"<<endl;
        cin>>s;
        if(s=="above"){
            min = guessB(max);
            max = guessB(min);
        }
        else if(s=="below"){
            max = guessH(min);
            min = guessH(min);
            if(max<min){
                swap(&min, &max);
            }
        }
        else if(s=="within"){
            cout<<"Win"<<endl;
            win = 1;
            break;
        }
        count++;
    }
    if(win==0){
        cout<<"game loss"<<endl;
    }

    return 0;
}
