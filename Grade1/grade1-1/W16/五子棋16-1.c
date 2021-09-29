#include<stdio.h>

int main(){
    char str[100][100]={0};
    int i,j,k,a,b,c,d,e,f,g,h,l,m,n,p,q,r,s,t;
     for(i=0;i<19;i++){
         scanf("%s", str[i]);
    }
    for(i=0;i<19;i++){
        for(j=0;j<19;j++){
            if(str[i][j]=='O'){
                for(k=1;k<5;k++){
                    if(str[i][j+k]=='O' && j+k<=18){//right
                        a++;
                    }
                    if(str[i][j-k]=='O' && j-k>=0){//left
                        b++;
                    }
                    if(str[i+k][j]=='O' && i+k<=18){//down
                        c++;
                    }
                    if(str[i-k][j]=='O' && i-k>=0){//up
                        d++;
                    }
                    if(str[i-k][j-k]=='O' && i-k>=0 && j-k>=0){//leftup
                        e++;
                    }
                    if(str[i+k][j+k]=='O' && i+k<=18 && j+k<=18){//rightdown
                        f++;
                    }
                    if(str[i-k][j+k]=='O' && i-k>=0 && j+k<=18){//rightup
                        g++;
                    }
                    if(str[i+k][j-k]=='O' && i+k<=18 && j-k>=0){//leftdown
                        h++;
                    }
                }
                if(a==4 || b==4 || c==4 || d==4 || e==4 || f==4 || g==4 || h==4){
                    printf("White");
                    return 0;
                }
                else {a=0; b=0; c=0; d=0; e=0; f=0; g=0; h=0;}
            }
            else if(str[i][j]=='X'){
                for(k=1;k<5;k++){
                    if(str[i][j+k]=='X' && j+k<=18){//right
                        l++;
                    }
                    if(str[i][j-k]=='X' && j-k>=0){//left
                        m++;
                    }
                    if(str[i+k][j]=='X' && i+k<=18){//down
                        n++;
                    }
                    if(str[i-k][j]=='X' && i-k>=0){//up
                        p++;
                    }
                    if(str[i-k][j-k]=='X' && i-k>=0 && j-k>=0){//leftup
                        q++;
                    }
                    if(str[i+k][j+k]=='X' && i+k<=18 && j+k<=18){//rightdown
                        r++;
                    }
                    if(str[i-k][j+k]=='X' && i-k>=0 && j+k<=18){//rightup
                        s++;
                    }
                    if(str[i+k][j-k]=='X' && i+k<=18 && j-k>=0){//leftdown
                        t++;
                    }
                }
                if(l==4 || m==4 || n==4 || p==4 || q==4 || r==4 || s==4 || t==4){
                    printf("Black");
                    return 0;
                }
                else{l=0; m=0; n=0; p=0; q=0; r=0; s=0; t=0;}
            }
        }
    }
    printf("No winner");
    return 0;
}
