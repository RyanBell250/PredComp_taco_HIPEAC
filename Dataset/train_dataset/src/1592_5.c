#include<bits/stdc++.h>
#define L 1301281
using namespace std;
int T,a,b,c,d;
long long n,V,h[L],f[L];
int get(long long x){
	int y=x%L;
	while(h[y]&&h[y]^x)y=(++y==L)?0:y;
	return y;
}
long long calc(long long n){
	if(!n)return 0;
	if(n==1)return d;
	int x=get(n);
	if(h[x]==n)return f[x];
	h[x]=n;
	if(8e18/d<n)f[x]=8e18;else f[x]=n*d;
	f[x]=min(f[x],calc(n>>1)+(n&1)*d+a);
	if(n&1)f[x]=min(f[x],calc(n+1>>1)+d+a);
	f[x]=min(f[x],calc(n/3)+(n%3)*d+b);
	if(n%3)f[x]=min(f[x],calc(n/3+1)+(3-n%3)*d+b);
	f[x]=min(f[x],calc(n/5)+1ll*(n%5)*d+c);
	if(n%5)f[x]=min(f[x],calc(n/5+1)+1ll*(5-n%5)*d+c);
	return f[x];
}
int main(){
	scanf("%d",&T);
	for(;T--;){
		scanf("%lld %d %d %d %d",&n,&a,&b,&c,&d);
		printf("%lld\n",calc(n));
		for(int i=0;i<L;++i)h[i]=f[i]=0;
	}
}
