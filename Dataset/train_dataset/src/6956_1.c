#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int V=120;
const int En=2100000;
struct Elf{int u,v;double len;}b[En];
const double oo=1e100;
double ret;
int N,M,Root;
int id[V],pre[V],cnt,vis[V];
double in[V];
bool TreeMST()
{
	ret=0.0;
	int i,u,v;
	while(1)
	{
		for(i=0;i<N;i++)
		in[i]=oo;
		memset(pre,-1,sizeof(pre));
		for(i=0;i<M;i++)
		{
			u=b[i].u;
			v=b[i].v;
			if(b[i].len<in[v]&&u!=v)
			{
				pre[v]=u;
				in[v]=b[i].len;
			}
		}
		for(i=0;i<N;i++)
		{
			if(i==Root)continue;
			if(pre[i]==-1)return false;
		}
		in[Root]=0;
		cnt=0;
		memset(id,-1,sizeof(id));
		memset(vis,-01,sizeof(vis));
		for(i=0;i<N;i++)
		{
			ret+=in[i];v=i;
			while(vis[v]!=i&&id[v]==-1&&v!=Root)
			{vis[v]=i;v=pre[v];}
			if(v!=Root&&id[v]==-1)
			{
				for(u=pre[v];u!=v;u=pre[u])
				id[u]=cnt;
				id[v]=cnt++;
			}
		}
		if(cnt==0)return true;
		for(i=0;i<N;i++)
		if(id[i]==-1)id[i]=cnt++;
		for(i=0;i<M;i++)
		{
			v=b[i].v;
			b[i].u=id[b[i].u];
			b[i].v=id[b[i].v];
			if(b[i].u!=b[i].v)
			b[i].len-=in[v];
		}
		N=cnt;
		Root=id[Root];
	
	
	}
}
double sqr(double x){return x*x;}
int m,n;
double a[120][120];
double Cal(int x,int y,double r)
{
	double ret=0.0;
	for(int i=0;i<m;i++)
	ret+=sqr(a[x][i]-a[y][i]*r);
	return ret;
}
int i,j,k;
double lo,up,mid1,mid2;
int main()
{
	while(~scanf("%d%d",&m,&n))
	{
		for(i=1;i<=n;i++)
		{
			for(j=0;j<m;j++)
			scanf("%lf",&a[i][j]);
		}
		N=n+1;M=0;
		for(i=1;i<=n;i++)
		{
			b[M].u=0;
			b[M].v=i;
			double te=0.0;
			for(j=0;j<m;j++)
			te+=a[i][j]*a[i][j];
			b[M++].len=te;
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				if(i==j)continue;
				lo=-1e10;up=1e10;
				for(k=0;k<100;k++)
				{
					mid1=2.0*lo/3.0+up/3.0;
					mid2=lo/3.0+2.0*up/3.0;
					if(Cal(j,i,mid1)>Cal(j,i,mid2))lo=mid1;
					else up=mid2;
				}
				b[M].u=i;
				b[M].v=j;
				b[M++].len=Cal(j,i,lo);
			}
		}
	
	
		Root=0;
		if(TreeMST())printf("%.8f\n",ret);
		else puts("Obsidian");
	}
}
