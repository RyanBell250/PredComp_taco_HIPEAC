#include <stdio.h>

int gcd(int a,int b){
	return b ? gcd(b, a % b) : a;
}
int main()
{
  int k; scanf ("%d",&k); int a =0;
  for (int i=1;i<=k;i++) for (int j=1;j<=k;j++) for (int l=1;l<=k;l++) a += gcd(i,gcd(j,l));
  printf ("%d\n",a);
return 0;
}