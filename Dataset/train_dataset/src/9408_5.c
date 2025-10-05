#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#define SIZE 25
#define BT 1<<20
#define MOD 1000000007
#define MX 205
using namespace std;
typedef long long int ll;
typedef pair <int,int> P;
ll dp[BT],way[BT];
ll fac[MX][MX];
ll C[MX][MX];
vector <P> vec[SIZE];
int cnt[BT],cnt2[BT];
int memo[SIZE][BT];
void make()
{
	for(int i=0;i<MX;i++)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
		{
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		}
	}
	for(int i=1;i<MX;i++)
	{
		fac[i][i-1]=1;
		for(int j=i;j<MX;j++) fac[i][j]=fac[i][j-1]*(ll) j%MOD;
	}
}
int dfs(int v,int p,int goal)
{
	if(v==goal) return 0;
	for(int i=0;i<vec[v].size();i++)
	{
		int to=vec[v][i].first;
		if(to!=p)
		{
			int ret=dfs(to,v,goal);
			if(ret!=-1) return ret|(1<<vec[v][i].second);
		}
	}
	return -1;
}
int main()
{
	make();
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=0;i<n-1;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);a--,b--;
		vec[a].push_back(P(b,i));
		vec[b].push_back(P(a,i));
	}
	for(int i=n-1;i<m;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);a--,b--;
		int S=dfs(a,-1,b);
		cnt[S]++;
	}
	int sz=n-1;
	for(int i=0;i<sz;i++)
	{
		for(int S=0;S<1<<sz;S++) memo[i][S]=cnt[S];
		for(int j=0;j<sz;j++)
		{
			if(j==i) continue;
			for(int S=0;S<1<<sz;S++) if(S>>j&1) memo[i][S]+=memo[i][S-(1<<j)];
		}
	}
	memset(dp,0,sizeof(dp));
	memset(way,0,sizeof(way));
	way[(1<<sz)-1]=1;
	for(int S=(1<<sz)-1;S>=0;S--)
	{
		int nm=0;
		for(int i=0;i<sz;i++) if(!(S>>i&1)) nm++;
		for(int i=0;i<sz;i++)
		{
			if(S>>i&1)
			{
				ll w=way[S],d=dp[S],c=cnt2[S];
				w=w*fac[c+1][c+memo[i][S]]%MOD;
				d=d*fac[c+2][c+memo[i][S]+1]%MOD;
				int T=S-(1<<i);
				cnt2[T]=cnt2[S]+memo[i][S]+1;
				dp[T]+=(d+w*(ll) (nm+1))%MOD;
				if(dp[T]>=MOD) dp[T]-=MOD;
				way[T]+=w;
				if(way[T]>=MOD) way[T]-=MOD;
			}
		}
	}
	printf("%lld\n",dp[0]);
	return 0;
}
