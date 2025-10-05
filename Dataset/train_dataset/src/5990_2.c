#include <bits/stdc++.h>
using namespace std;
#define N 55
#define S 5005
#define ll long long
#define set(a,v) memset(a,v,sizeof(a))
int n,m,s,lim=5e3,c[N],d[N];bool vs[N];ll dp[N][S];
struct Edge {int v,a,b;};vector<Edge> e[N];queue<int> q;
void addE(int u,int v,int a,int b)
{
	e[u].push_back((Edge) {v,a,b});
	e[v].push_back((Edge) {u,a,b});
}
void SPFA()
{
	set(dp,0x3f);dp[1][s]=0;vs[1]=1;q.push(1);
	while(!q.empty())
	{
		int u=q.front();q.pop();vs[u]=0;
		for(int i=c[u];i<=lim;++i)
			dp[u][i]=min(dp[u][i],dp[u][i-c[u]]+d[u]);
		for(int i=0,v,a,b,fl;i<e[u].size();++i)
		{
			v=e[u][i].v;a=e[u][i].a;b=e[u][i].b;fl=0;
			for(int j=a;j<=lim;++j) if(dp[u][j]+b<dp[v][j-a])
				dp[v][j-a]=dp[u][j]+b,fl=1;
			if(fl && !vs[v]) vs[v]=1,q.push(v);
		}
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&s);s=min(s,lim);
	for(int i=1,u,v,a,b;i<=m;++i)
		scanf("%d %d %d %d",&u,&v,&a,&b),addE(u,v,a,b);
	for(int i=1;i<=n;++i) scanf("%d %d",&c[i],&d[i]);SPFA();
	for(int i=2;i<=n;++i)
	{
		ll res=1e18;
		for(int j=0;j<=lim;++j) res=min(res,dp[i][j]);
		printf("%lld\n",res);
	}return 0;
}