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
int n,m;
vector<P> es;
int addnot;
int v1[80010],v2[80010];
int V;
vector<int> g[80010],rg[80010];
vector<int> vs;
bool used[80010];
int cmp[80010];
void add_edge(int from,int to){
  g[from].push_back(to);
  rg[to].push_back(from);
}
void dfs(int v){
  used[v]=true;
  for(int i=0;i<g[v].size();i++){
    if(!used[g[v][i]])dfs(g[v][i]);
  }
  vs.push_back(v);
}
void rdfs(int v,int k){
  used[v]=true;
  cmp[v]=k;
  for(int i=0;i<rg[v].size();i++){
    if(!used[rg[v][i]])rdfs(rg[v][i],k);
  }
}
int scc(){
  memset(used,0,sizeof(used));
  vs.clear();
  for(int v=0;v<V;v++){
    if(!used[v])dfs(v);
  }
  memset(used,0,sizeof(used));
  int k=0;
  for(int i=vs.size()-1;i>=0;i--){
    if(!used[vs[i]])rdfs(vs[i],k++);
  }
  return k;
}
bool ok(int x){
  rep(i,V){
    g[i].clear();
    rg[i].clear();
  }
  rep(i,es.size()){
    if(v1[i]<x&&v2[i]<x)add_edge(es[i].fi,es[i].se);
  }
  scc();
  bool ok=true;
  rep(i,n){
    if(cmp[i]==cmp[i+addnot])ok=false;
  }
  return ok;
}
int main(){
  cin>>n>>m;
  addnot=n;
  V=n*2;
  rep(i,m){
    int a1,a2;
    string d1,d2,c;
    cin>>a1>>d1>>c>>a2>>d2;
    a1--; a2--;
    v1[i*2]=a1; v2[i*2]=a2;
    es.push_back(P(a1+(d1=="left"?addnot:0),a2+(d2=="left"?0:addnot)));
    v1[i*2+1]=a2; v2[i*2+1]=a1;
    es.push_back(P(a2+(d2=="left"?addnot:0),a1+(d1=="left"?0:addnot)));
  }
  int lb=0,ub=n;
  while(ub-lb>1){
    int mid=(lb+ub)/2;
    if(ok(mid))lb=mid;
    else ub=mid;
  }
  cout<<ub<<endl;
  return 0;
}
