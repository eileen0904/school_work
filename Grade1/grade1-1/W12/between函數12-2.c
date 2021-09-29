/*ㄧ计 between Τㄢ把计 a 蛤 b ㄢ把计常琌俱计夹
ㄧ计 between 穦肚夹 a ぇ夹 b ぇ玡┮Τ俱计㎝*/


int between(int *a, int *b)
{
  int sum=0;
  while(b>a){
  	sum=sum+*a;
  	a++;
  }
  return sum;
}
