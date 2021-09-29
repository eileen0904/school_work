/*elementAt 這個函數會傳入一個指向整數的指標，以及一個整數 n，回傳該指標後第 n 個整數*/


int elementAt(int *pointer, int n)
{
 return *(pointer+n-1);
}
