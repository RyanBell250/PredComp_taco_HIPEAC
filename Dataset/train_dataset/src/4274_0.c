#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define FOR(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#define FORR(i,a,b) for(int i=(int)(b)-1;i>=(int)(a);i--)
#define CHMIN(a,b) (a)=min((a),(b))
#define CHMAX(a,b) (a)=max((a),(b))
#define MOD 1000000007
int n,m,ss,gg;
vector<pair<int,pll>> g[252521];
ll dist[252521];
ll calc(ll d, ll a, ll b){
  ll da = d-a;
  double D2 = (double)da*da - 4.0*b + 4.0*d*a;
  if(D2 < 0)return -1;
  double D = sqrt(D2);
  double x = (da+D)/2.0;
  if(x<0)return -1;
  return min((ll)x,d-1);
}
bool check(ll x){
  REP(i,n)dist[i] = -(1ll<<60);
  priority_queue<pll> Q;
  dist[gg] = x;
  Q.push(pll(x,gg));
  while(!Q.empty()){
    pll P = Q.top(); Q.pop();
    int p = P.second;
    ll d = P.first;
    if(dist[p] != d)continue;
    for(pair<int,pll> PP : g[p]){
      int to = PP.first;
      ll a = PP.second.first;
      ll b = PP.second.second;
      ll t = calc(d,a,b);
      if(t<0)continue;
      if(t<=dist[to])continue;
      dist[to] = t;
      Q.push(pll(t,to));
    }
  }
  return dist[ss]>=0;
}
int main(){
  scanf("%d%d%d%d",&n,&m,&ss,&gg);
  --ss;--gg;
  REP(_,m){
    int u,v; ll a,b;
    scanf("%d%d%lld%lld",&u,&v,&a,&b);
    --u;--v;
    g[u].push_back(make_pair(v,pll(a,b)));
    g[v].push_back(make_pair(u,pll(a,b)));
  }
  ll low = 0, high = 1ll<<60;
  while(low+1<high){
    ll x = (low+high)/2ll;
    bool ok = check(x);
    if(ok){
      high = x;
    }else{
      low = x;
    }
  }
  if(high == (1ll<<60))high = -1;
  printf("%lld\n",high);
  return 0;
}
