#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=2E5+100,mod=1E9+7;
int T,n,l,r;
int a[N],fac[N],inv[N];
inline int ksm(int x,int y){return y==1?x:1ll*ksm(1ll*x*x%mod,y>>1)*((y&1)?x:1)%mod;}
inline void init(const int lim=2E5){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[lim]=ksm(fac[lim],mod-2);
	for(int i=lim;i;i--) inv[i-1]=1ll*inv[i]*i%mod;
}
inline int C(int x,int y){return x<y?0:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main(){
	init();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&l,&r);
		int L=l-1,R=r-n;
		int ans=(1ll+(n&1))*C(n,n/2)*min(-L,R)%mod;
		L=-L;if(L>R) swap(L,R);
		int s1=0,s2=0;
		for(int i=1;i<=n;i++){
			s1++;
			if(L+i>R) s2++;
			if(n&1) ans=(ans+C(n-s1-s2,n/2-s1+1))%mod;
			if(s1+s2>n||s1>n/2) break;
			ans=(ans+C(n-s1-s2,n/2-s1))%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}