#include<bits/stdc++.h>
#define long long long
using namespace std;
struct edge
{
	int u,v,l;
	bool operator<(const edge &p)const{return l<p.l;}
}e[2000009];
int n,m;
vector<int> g[200009],h[200009];
int lz[800009],ft[800009];
int pf[200009],esm[200009];
int vis[2009][2009];
void build(int a,int l,int r)
{
	if(l==r)
		return ft[a]=l,void();
	int mid=(l+r)/2;
	build(a*2,l,mid);
	build(a*2+1,mid+1,r);
}
void dn(int a)
{
	if(!lz[a])
		return;
	int la=a*2,ra=a*2+1,vl=lz[a];
	lz[la]=ft[la]=lz[ra]=ft[ra]=vl;
	lz[a]=0;
}
void setv(int a,int l,int r,int ll,int rr,int v)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
	{
		ft[a]=lz[a]=v;
		return;
	}
	dn(a);
	int mid=(l+r)/2;
	setv(a*2,l,mid,ll,rr,v);
	setv(a*2+1,mid+1,r,ll,rr,v);
}
int askv(int a,int l,int r,int p)
{
	if(l==r)
		return ft[a];
	dn(a);
	int mid=(l+r)/2;
	if(p<=mid)
		return askv(a*2,l,mid,p);
	return askv(a*2+1,mid+1,r,p);
}
int fnd(int x)
{
	return x==pf[x]?x:pf[x]=fnd(pf[x]);
}
int main()
{
	scanf("%d%d",&n,&m);
	int sm=0;
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		g[a].push_back(b),g[b].push_back(a);
		if(a>b)
			swap(a,b);
		e[i]=edge{a,b,c};
		sm^=c;
	}
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		g[i].push_back(n+1);
		int lp=1;
		sort(g[i].begin(),g[i].end());
		int f=askv(1,1,n,i);
		for(int v:g[i])
		{
			if(v-1>=lp)
				setv(1,1,n,lp,v-1,f);
			lp=v+1;
		}
	}
	for(int i=1;i<=n;i++)
		pf[i]=askv(1,1,n,i),h[pf[i]].push_back(i);
	for(int i=1;i<=m;i++)
		if(pf[e[i].u]==pf[e[i].v])
			esm[pf[e[i].u]]++;
	long ans=0;
	sort(e+1,e+m+1);
	for(int i=1;i<=m;i++)
	{
		int x=e[i].u,y=e[i].v;
		if(fnd(x)==fnd(y))
			continue;
		ans+=e[i].l;
		pf[fnd(x)]=fnd(y);
	}
	for(int i=1;i<=n;i++)
		if(h[i].size())
		{
			int l=h[i].size();
			if((long)l*(l-1)/2-esm[i]>=l)
				return printf("%lld",ans),0;
		}
	ans+=sm;
	for(int i=1;i<=m;i++)
		vis[e[i].u][e[i].v]=vis[e[i].v][e[i].u]=1;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(!vis[i][j])
				e[++m]=edge{i,j,0};
	sort(e+1,e+m+1);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(!vis[i][j])
			{
				for(int k=1;k<=n;k++)
					pf[k]=k;
				long tans=0;
				for(int k=1;k<=m;k++)
					if(!(e[k].u==i&&e[k].v==j))
					{
						int x=e[k].u,y=e[k].v;
						if(fnd(x)==fnd(y))
							continue;
						tans+=e[k].l;
						pf[fnd(x)]=fnd(y);
					}
				ans=min(ans,tans);
			}
	printf("%lld",ans);
	return 0;
}