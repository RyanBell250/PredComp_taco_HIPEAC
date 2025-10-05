#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=2e5+10;
struct E{
	int to;
	int next;
}ed[maxn];
int head[maxn];
int tot;
void J(int a,int b){
	ed[++tot].to=b;
	ed[tot].next=head[a];
	head[a]=tot;
}
int a[maxn];
int deep[maxn];
int mx[maxn];
int mn[maxn];
int f[maxn];
long long dp[maxn];
int ydep;
vector<int> ve[maxn];
void Dfs(int x,int fa){
	deep[x]=deep[fa]+1;
	if(x!=1){
		mx[deep[x]]=max(mx[deep[x]],a[x]);
		mn[deep[x]]=min(mn[deep[x]],a[x]);
		ve[deep[x]].push_back(x);
		ydep=max(ydep,deep[x]);
	}
	for(int i=head[x];i;i=ed[i].next)
		Dfs(ed[i].to,x);
}
int main(){
	int t;
	scanf("%d",&t);
	for(int jsjs=1;jsjs<=t;jsjs++){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			ve[i].clear();
			head[i]=0;
			mx[i]=0;
			mn[i]=1e9+10;
			dp[i]=0;
		}
		tot=0;
		ydep=0;
		for(int i=2;i<=n;i++){
			scanf("%d",&f[i]);
			J(f[i],i);
		}
		for(int i=2;i<=n;i++)
			scanf("%d",&a[i]);
		Dfs(1,0);
		long long ans=0;
		for(int i=2;i<=ydep;i++){
			long long mxa=-1e9-10,mxb=-1e9-10;
			for(int j=0;j<ve[i].size();j++){
				int x=ve[i][j];
				mxa=max(mxa,dp[f[x]]+a[x]);
				mxb=max(mxb,dp[f[x]]-a[x]);
			}
			for(int j=0;j<ve[i].size();j++){
				int x=ve[i][j];
				dp[x]=max(dp[x],dp[f[x]]+max(a[x]-mn[i],mx[i]-a[x]));
				dp[x]=max(dp[x],max(mxa-a[x],mxb+a[x]));
				ans=max(ans,dp[x]);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
