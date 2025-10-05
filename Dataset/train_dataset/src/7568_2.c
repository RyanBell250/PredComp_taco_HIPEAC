#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
ll read(){
	ll a=0,b=getchar(),c=1;
	while(!isdigit(b))c=b=='-'?-1:1,b=getchar();
	while(isdigit(b))a=a*10+b-'0',b=getchar();
	return a*c;
}
int a[200005];
ll n,ans[200005],b[200005],c[200005];
vector<int> g[200005];
ll gg(ll x){
	return x*(x-1)/2+x;
}
void dfs(int x,int y){
	c[x]=1;
	ll d=a[x],s=b[d];
	for(int i=0;i<g[x].size();i++)
		if(g[x][i]!=y){
			int tmp=b[d];
			dfs(g[x][i],x);
			c[x]+=c[g[x][i]];
			ans[d]-=gg(c[g[x][i]]-(b[d]-tmp));
		}
	b[d]=s+c[x];
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		ans[i]=gg(n);
	dfs(1,0);
	for(int i=1;i<=n;i++){
		ans[i]-=gg(n-b[i]);
		printf("%lld\n",ans[i]);
	}
	return 0;
}
