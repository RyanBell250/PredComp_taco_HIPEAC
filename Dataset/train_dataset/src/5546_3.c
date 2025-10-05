#include<bits/stdc++.h> 
using namespace std;
namespace Sakurajima_Mai{
	#define ms(a) memset(a,0,sizeof(a))
	#define repi(i,a,b) for(int i=a,bbb=b;i<=bbb;++i)
	#define repd(i,a,b) for(int i=a,bbb=b;i>=bbb;--i)
	#define reps(s) for(int i=head[s],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
	#define ce(i,r) i==r?'\n':' '
	#define pb push_back 
	#define all(x) x.begin(),x.end()
	#define gmn(a,b) a=min(a,b)
	#define gmx(a,b) a=max(a,b)
	#define fi first
	#define se second   					  
	typedef long long ll;
	typedef unsigned long long ull;
	typedef double db;
	const int infi=2e9;
	const ll infl=4e18;
	inline ll ceil_div(ll a,ll b){ return (a+b-1)/b; }
}
using namespace Sakurajima_Mai;
namespace Fast_Read{
	inline int qi(){
	    int f=0,fu=1; char c=getchar();
	    while(c<'0'||c>'9'){ if(c=='-')fu=-1; c=getchar(); }
	    while(c>='0'&&c<='9'){ f=(f<<3)+(f<<1)+c-48; c=getchar(); }
	    return f*fu;
	}
	inline ll ql(){
		ll f=0;int fu=1; char c=getchar();
	    while(c<'0'||c>'9'){ if(c=='-')fu=-1; c=getchar(); }
	    while(c>='0'&&c<='9'){ f=(f<<3)+(f<<1)+c-48; c=getchar(); }
	    return f*fu;
	}
	inline db qd(){
	    char c=getchar();int flag=1;double ans=0;
	    while((!(c>='0'&&c<='9'))&&c!='-') c=getchar();
	    if(c=='-') flag=-1,c=getchar();
	    while(c>='0'&&c<='9') ans=ans*10+(c^48),c=getchar();
	    if(c=='.'){c=getchar();for(int Bit=10;c>='0'&&c<='9';Bit=(Bit<<3)+(Bit<<1)) ans+=(double)(c^48)*1.0/Bit,c=getchar();}
	    return ans*flag;
	}
}
namespace Read{
	#define si(a) scanf("%d",&a)
	#define sl(a) scanf("%lld",&a)
	#define sd(a) scanf("%lf",&a)
	#define ss(a) scanf("%s",a)
	#define rai(x,a,b) repi(i,a,b) x[i]=qi()
	#define ral(x,a,b) repi(i,a,b) x[i]=ql()
}
namespace Out{
	#define pi(x) printf("%d",x)
	#define pl(x) printf("%lld",x)
	#define ps(x) printf("%s",x)
	#define pc(x) printf("%c",x)
	#define pe() puts("")
}
namespace DeBug{
	#define MARK false
	#define DB if(MARK) 
	#define pr(x) cout<<#x<<": "<<x<<endl
	#define pra(x,a,b) cout<<#x<<": "<<endl; \
			repi(i,a,b) cout<<x[i]<<" ";	 \
			puts("");   
	#define FR(a) freopen(a,"r",stdin)
	#define FO(a) freopen(a,"w",stdout)
}
using namespace Fast_Read;
using namespace Read;
using namespace Out;
using namespace DeBug;
const int MAX_N=1e5+5;
int n,x;
vector<int> g[MAX_N];
int mxdep=0,deep[MAX_N];
map<int,int> h;
int htot=0;
vector<int> rec[MAX_N],rec2[MAX_N];
int val[MAX_N];
void dfs(int u)
{
	gmx(mxdep,deep[u]),rec[deep[u]].pb(u);
	for(auto v:g[u]) deep[v]=deep[u]+1,dfs(v);
}
bitset<MAX_N> dp[500];
bool ans[MAX_N];
void Reduction(int num,int left)
{
	if(!num) return ;
	for(auto x:rec2[num]){
		if(dp[num-1][left]) break;
		left-=val[num];
		for(auto v:rec[x]) ans[v]=true;
	}
	Reduction(num-1,left);
}
int main()
{
	n=qi(),x=qi();
	repi(i,2,n) g[qi()].pb(i); 
	deep[1]=1; dfs(1);
	repi(i,1,mxdep){
		int siz=rec[i].size();
		if(!h[siz]) h[siz]=++htot,val[htot]=siz;
		rec2[h[siz]].pb(i);
	}
	dp[0][0]=1;
	repi(i,1,htot){
		dp[i]=dp[i-1];
		int siz=rec2[i].size();
		for(int j=1;j<=siz;j<<=1) dp[i]|=dp[i]<<(j*val[i]),siz-=j;
		if(siz) dp[i]|=dp[i]<<(siz*val[i]);
	}
	if(dp[htot][x]) pi(mxdep),pe(),Reduction(htot,x);
	else{
		pi(mxdep+1),pe();
		int undetermined=n;
		repi(i,1,mxdep){
			if(rec[i].size()<=x){
				for(auto v:rec[i]) ans[v]=true;
				x-=rec[i].size();
			}
			else if(rec[i].size()<=undetermined-x) ;
			else{
				int mn=min(x,undetermined-x);
				bool mark=x>(undetermined-x);
				vector<int> leaf;
				for(auto v:rec[i]){
					if(!g[v].size()&&mn){
						ans[v]=!mark,mn--;
						if(!mark) x--;
					} 
					else{
						 ans[v]=mark;
						 if(mark) x--;
					}
				}
			}
			undetermined-=rec[i].size();
		}
	}
	repi(i,1,n) pc(ans[i]?'a':'b'); pe();
	return 0;
}
