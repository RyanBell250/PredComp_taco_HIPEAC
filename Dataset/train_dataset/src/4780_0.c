#include <stdio.h>
int gcd(int x,int y){if(!y) return x;return gcd(y,x%y);}
int main(){
    int k;long long ans=0;scanf("%d",&k);for(int a=1;a<=k;a++) for(int b=1;b<=k;b++) for(int c=1;c<=k;c++) ans+=gcd(a,gcd(b,c));
    return printf("%lld\n",ans),0;
}