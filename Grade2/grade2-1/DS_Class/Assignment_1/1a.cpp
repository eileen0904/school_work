#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int guessB(int low){
    srand(time(NULL));
    int num = rand() % (100-low+1) + low;
    return num;
}

int guessH(int high){
    srand(time(NULL));
    int num = rand() % high + 1;
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
    int count=0, ans;
    cout<<"Please input a number between 1~100."<<endl;
    cin>>ans;
    srand(time(NULL));
    int min = rand() % 100 + 1;
    int max = rand() % 100 + 1;
    if(max<min){
        swap(&min, &max);
    }
    int com = rand() % (max-min+1) + min;
    while(count<4){
        int status=0;
        cout<<"The number is between :"<<min<<"~"<<max<<endl;
        cout<<"The number is "<<com<<endl;
        if(com==ans){
            cout<<"Bingo!"<<endl;
        }
        else{
            cout<<"The range is : 1:Below/2:Within/3:Above ?"<<endl;
            cin>>status;
            if(status==1){
                min = guessB(max);
                max = guessB(min);
                srand(time(NULL));
                com = rand() % (max-min+1) + min;
            }
            else if(status==3){
                max = guessH(min);
                min = guessH(min);
                if(max<min){
                    swap(&min, &max);
                }
                srand(time(NULL));
                com = rand() % (max-min+1) + min;
            }
            else if(status==2){
                srand(time(NULL));
                int tmp_max = max, tmp_min = min;
                max = rand() % (tmp_max-tmp_min+1) + tmp_min;
                min = rand() % (tmp_max-tmp_min+1) + tmp_min;
                if(max<min){
                    swap(&min, &max);
                }
                com = rand() % (max-min+1) + min;
            }
        }
        count++;
    }
    cout<<"game loss"<<endl;

    return 0;
}
