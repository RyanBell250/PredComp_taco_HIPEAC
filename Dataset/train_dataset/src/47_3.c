#include<algorithm>
#include<cstdio>
using namespace std;
const int mod=1e9+7;
int n,m,sum,ans,fac[2010],ifc[2010];
int pow(int k,int i)
{
	int t=1;
	while(i)
	{
		if(i&1) t=1ll*t*k%mod;
		k=1ll*k*k%mod;i>>=1;
	}
	return t;
}
int C(int x,int y)
{
	if(x<y) return 0;
	return 1ll*fac[x]*ifc[y]%mod*ifc[x-y]%mod;
}
int main()
{
	scanf("%d%d",&n,&m);fac[0]=1;int x,y,mxn=max(n,m);ans=n+1;
	for(int i=1;i<=mxn+1;++i) fac[i]=1ll*fac[i-1]*i%mod;
	ifc[mxn+1]=pow(fac[mxn+1],mod-2);
	for(int i=mxn;~i;--i) ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m-i;++j)
		{
			x=m-i;y=x-j;
			sum=1ll*C(x+i-1,x)*C(y+j-1,y)%mod;
			sum=1ll*sum*C(n-x-y+2,2)%mod;
			ans+=sum;if(ans>=mod) ans-=mod;
		}
	printf("%d\n",ans);
	return 0;
}