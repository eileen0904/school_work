/*該函數會傳入三個整數指標 a ， b ， c ，
然後會將指標 a 之後的五個整數以及指標 b 後的五個整數依照由小到大的順序放入指標 c 之後*/


int merger(int *a, int *b, int *c)
{
  int v[10],i,j,temp=0;
  for(i=0;i<5;i++){
    v[i]=*a;
    a++;
  }
  for(i=5;i<10;i++){
    v[i]=*b;
    b++;
  }
  for(i=0;i<10;i++){
    for(j=0;j<9-i;j++){
      if(v[j]>v[j+1]){
        temp=v[j+1];
        v[j+1]=v[j];
        v[j]=temp;
      }
    }
  }
  for(i=0;i<10;i++){
    *c=v[i];
    c++;
  }
}
