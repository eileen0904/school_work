//會把字串 src 接在 dest 後面，然後回傳 dest//
//會把字串 src 的前 n 個字元接在 dest 後面，然後回傳 dest//


#include<string.h>
char *mystrcat(char *dest, char *src)
{
  strcat(dest, src);
  dest[strlen(dest)+strlen(src)] = '\0';
  return dest;
}

char *mystrncat(char *dest, char *src, int n)
{
  char temp[n];
  int i;
  for(i=0;i<n;i++){
    temp[i]=src[i];
  }
  strcat(dest, temp);
  dest[strlen(dest)+strlen(temp)] = '\0';
  return dest;
}
