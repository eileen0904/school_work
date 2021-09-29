#include<stdio.h>
#include<math.h>

int main(){
    int n,m,i,j,k,tempx=0,tempy=0,a=0;
    scanf("%d",&n);
    float length[a];
    for(i=0;i<n;i++){
        length[i]=0;
    }
    while(a<n){
        scanf("%d",&m);
        int x[m],y[m];
        for(i=0;i<m;i++){
            x[i]=0;
            y[i]=0;
        }
        for(i=0;i<m;i++){
            scanf("%d %d",&x[i],&y[i]);
        }
        for(i=0;i<m;i++){
            for(j=0;j<m-1-i;j++){
                if(x[j]>x[j+1]){
                    tempx=x[j+1];
                    x[j+1]=x[j];
                    x[j]=tempx;
                    tempy=y[j+1];
                    y[j+1]=y[j];
                    y[j]=tempy;
                }
            }
        }
        int counter=0;
        float maxY=m-2;
        float h1=0,h2=0,s1=0,s2=0;
        s2=sqrt(((x[m-1]-x[m-2])*(x[m-1]-x[m-2]))+((y[m-2]-y[m-1])*(y[m-2]-y[m-1])));
        for(i=m-3;i>=0;i--){
            for(j=i;j>=i;j--){
                for(k=m-2;k>j;k--){
                    if(y[j]>y[k]){
                        counter++;
                    }
                    if(maxY<y[k]){
                        maxY=y[k];
                    }
                }
            }
            if(counter==(m-2)-i){
                h1=y[i]-y[i+1];
                h2=y[i]-maxY;
                s1=sqrt(((x[i+1]-x[i])*(x[i+1]-x[i]))+((y[i]-y[i+1])*(y[i]-y[i+1])));
                s2=((s1*h2)/h1)+s2;
            }
            counter=0;
        }
        printf("%.2f",s2);
        if(a<n-1){printf("\n");}
        h1=0;
        h2=0;
        s1=0;
        s2=0;
        a++;
    }
    return 0;
}
