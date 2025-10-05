#include <bits/stdc++.h>
const int mod=998244353;
#define Rint register int
#define C(n,m) (n<m?0:1ll*fac[n]*invfac[n-m]%mod*invfac[m]%mod)
using namespace std;
int T,n,m,p,k,dp[3][100010],sg[100010],ans=0,ksm_18[100010];
bool vis[1010];
struct edge{
	int to,link,w;
};
struct graph{
	int head[100010],o;
	edge e[2000010];
	void clear(){
		memset(head,0,sizeof(head));
		o=0;
	}
	void add_edge(int u,int v){
		e[++o].to=v,e[o].link=head[u],head[u]=o;
		e[++o].to=u,e[o].link=head[v],head[v]=o;
	}
}g[3];
int main(){
	scanf("%d",&n);
	ksm_18[0]=1,ksm_18[1]=(1000000000000000000ll)%mod;
	for(int i=2;i<=n;i++) ksm_18[i]=1ll*ksm_18[i-1]*ksm_18[1]%mod; 
	for(int t=0;t<3;t++){
		scanf("%d",&m);
		for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),g[t].add_edge(u,v);
		for(int u=n;u>=1;u--){
			sg[u]=0;
			for(int i=g[t].head[u];i;i=g[t].e[i].link) if(g[t].e[i].to>u) vis[sg[g[t].e[i].to]]=true;
			while(vis[sg[u]]) sg[u]++;

			dp[t][sg[u]]=(dp[t][sg[u]]+ksm_18[u])%mod;
			for(int i=g[t].head[u];i;i=g[t].e[i].link) if(g[t].e[i].to>u) vis[sg[g[t].e[i].to]]=false;
		}

	}
	for(int i=0;i<=1000;i++) for(int j=0;j<=1000;j++) ans=(ans+1ll*dp[0][i]*dp[1][j]%mod*dp[2][i^j])%mod;
	printf("%d\n",ans);
}
