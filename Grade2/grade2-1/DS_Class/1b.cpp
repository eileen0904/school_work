#include <iostream>
using namespace std;

int **disk;
int *top;
int totaln;

void show(){
    int i, j;
    for(i=0;i<3;i++){
        cout<<(char)(65+i);
        for(j=0;j<totaln;j++){
            if(disk[j][i]==0){continue;}
            else{
                cout<<disk[j][i];
            }
        }
        cout<<endl;
    }
}

void moveOne(int n, char A, char C){
    int x=A-'A', y=C-'A';
    int topY = ++top[y]; //current top
    disk[topY][y] = n; //[current top][peg]
    int topX = top[x];
    disk[topX][x] = 0;
    top[x]--;
    cout<< "Move disk " << n << " from peg " << A << " to " << C << endl;
    show();
}

void hanoi(int n, char A, char B, char C) {
    if(n==1) {
        moveOne(n, A, C);
    }
    else{
        hanoi (n-1, A, C, B);
        moveOne(n, A, C);
        hanoi(n-1, B, A, C);
    }
}

int main(){
    cout<<"Please input number of disks"<<endl;
    cin>>totaln;
    top = new int [totaln];
    top[0] = totaln-1;
    top[1] = top[2] = -1;
    disk = new int *[totaln];
    int *row = new int[3*totaln];
    for(int i=0;i<totaln;i++) {
        disk[i] = row + i*3;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<totaln;j++){
            if(i!=0){
                disk[j][i] = 0;
            }
            else{
                disk[j][i] = totaln - j;
            }
        }
    }
    cout<<"Initial pegs"<<endl;
    cout<<"A";
    for(int i=totaln;i>=1;i--){
        cout<<i;
    }
    cout<<endl;
    cout<<"B"<<endl;
    cout<<"C"<<endl;
    hanoi(totaln, 'A', 'B', 'C');

    return 0;
}