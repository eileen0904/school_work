/*UVa320 Border*/


#include<iostream>
#include<cstring>
using namespace std;

int main(){
    int i, j, k=0, temp=0;
    char s[1000];
    int map[32][32];
    cin>>k;
    while(temp<k){
        int x=0, y=0, len=0;
        cin>>x>>y;
        cin>>s;
        len = strlen(s);
        memset(map,0,sizeof(map));
        for(i=0;i<len;i++){
            if(s[i]=='E'){
                map[y][x+1] = 1;
                x++;
            }
            if(s[i]=='N'){
                map[y+1][x+1] = 1;
                y++;
            }
            if(s[i]=='W'){
                map[y+1][x] = 1;
                x--;
            }
            if(s[i]=='S'){
                map[y][x] = 1;
                y--;
            }
        }
        temp++;
        cout<<"Bitmap "<<"#"<<temp<<endl;
        for(i=32;i>=1;i--){
            for(j=1;j<=32;j++){
                if(map[i][j]==1){
                    cout<<"X";
                }
                else{
                    cout<<".";
                }
            }
            cout<<endl;
        }
        if(temp!=k){
            cout<<endl;
        }
    }

    return 0;
}
