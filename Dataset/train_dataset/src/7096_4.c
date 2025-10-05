#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;

#define fi first
#define se second
#define repl(i,a,b) for(ll i=(ll)(a);i<(ll)(b);i++)
#define rep(i,n) repl(i,0,n)
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout<<#x"="<<x<<endl
#define mmax(x,y) (x>y?x:y)
#define mmin(x,y) (x<y?x:y)
#define maxch(x,y) x=mmax(x,y)
#define minch(x,y) x=mmin(x,y)
#define uni(x) x.erase(unique(all(x)),x.end())
#define exist(x,y) (find(all(x),y)!=x.end())
#define bcnt __builtin_popcount

#define INF 1e16
#define mod 1000000007

ll n,q;
ll w[100001];
vector<ll> g[100001];
ll d[100001];
ll p[20][100001];
vector<ll> s[100001];
ll br[20][100001];

void dfs(ll v,ll pre,ll dist){
  p[0][v]=pre;
  d[v]=dist;
  for(ll nv : g[v]){
    if(nv==pre)continue;
    dfs(nv,v,dist+1);
    w[v]+=w[nv];
    if(s[v].size()>=3&&s[v].back()<w[nv]){
      s[v].pop_back();
      s[v].push_back(w[nv]);
      sort(all(s[v]));
      reverse(all(s[v]));
    }else if(s[v].size()<=2){
      s[v].push_back(w[nv]);
      sort(all(s[v]));
      reverse(all(s[v]));
    }
  }
}

int lca(int u,int v){
  if(d[u]>d[v])swap(u,v);
  for(int k=0;k<20;k++){
    if((d[v]-d[u])>>k&1){
      v=p[k][v];
    }
  }
  if(u==v)return u;
  for(int k=20-1;k>=0;k--){
    if(p[k][u]!=p[k][v]){
      u=p[k][u];
      v=p[k][v];
    }
  }
  return p[0][u];
}

int main(){
  cin>>n;
  rep(i,n)cin>>w[i];
  rep(i,n-1){
    ll a,b;
    cin>>a>>b;
    a--;b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs(0,-1,0);

  rep(v,n){
    for(ll ch : g[v]){
      if(d[ch]<d[v])continue;
      if(w[ch]==s[v][0]){
        if(s[v].size()>=2)br[0][ch]=s[v][1];
        else br[0][ch]=-INF;
      }else{
        if(s[v].size()>=1)br[0][ch]=s[v][0];
        else br[0][ch]=-INF;
      }
    }
  }

  rep(k,19){
    rep(i,n){
      if(p[k][i]!=-1) p[k+1][i]=p[k][p[k][i]];
      else p[k+1][i]=-1;
    }
  }

  rep(k,19){
    rep(i,n){
      if(p[k][i]!=-1) br[k+1][i]=max(br[k][i],br[k][p[k][i]]);
      else br[k+1][i]=-INF;
    }
  }

  cin>>q;
  while(q--){
    ll a,b;
    cin>>a>>b;
    a--;b--;
    if(d[a]>d[b])swap(a,b);
    ll lc=lca(a,b);
    ll res=w[0]-w[lc];

    if(lc==a){
      ll nb=b,pb=b;
      while(p[0][pb]!=lc&&pb!=lc){
        ll i=0;
        while(p[i][pb]!=-1&&d[p[i][pb]]>d[lc])i++;
        i--;
        pb=p[i][pb];
      }
      while(nb!=lc){
        ll i=0;
        while(p[i][nb]!=-1&&d[p[i][nb]]>=d[lc])i++;
        i--;
        maxch(res,br[i][nb]);
        nb=p[i][nb];
      }

      if(s[b].size()>0)maxch(res,s[b][0]);

      multiset<ll> rest;
      rep(k,s[a].size())rest.insert(s[a][k]);
      if(rest.find(w[pb])!=rest.end())rest.erase(rest.find(w[pb]));
      if(rest.size()>0)maxch(res,*rest.rbegin());
    }else{
      ll na=a,pa=a;
      while(p[0][pa]!=lc){
        ll i=0;
        while(p[i][pa]!=-1&&d[p[i][pa]]>d[lc])i++;
        i--;
        pa=p[i][pa];
      }
      while(na!=pa){
        ll i=0;
        while(p[i][na]!=-1&&d[p[i][na]]>=d[pa])i++;
        i--;
        maxch(res,br[i][na]);
        na=p[i][na];
      }

      ll nb=b,pb=b;
      while(p[0][pb]!=lc){
        ll i=0;
        while(p[i][pb]!=-1&&d[p[i][pb]]>d[lc])i++;
        i--;
        pb=p[i][pb];
      }
      while(nb!=pb){
        ll i=0;
        while(p[i][nb]!=-1&&d[p[i][nb]]>=d[pb])i++;
        i--;
        maxch(res,br[i][nb]);
        nb=p[i][nb];
      }

      if(s[a].size()>0)maxch(res,s[a][0]);
      if(s[b].size()>0)maxch(res,s[b][0]);
      multiset<ll> rest;
      rep(k,s[lc].size())rest.insert(s[lc][k]);
      if(rest.find(w[pa])!=rest.end())rest.erase(rest.find(w[pa]));
      if(rest.find(w[pb])!=rest.end())rest.erase(rest.find(w[pb]));
      if(rest.size()>0)maxch(res,*rest.rbegin());
    }
    cout<<res<<endl;
  }

  return 0;
}

