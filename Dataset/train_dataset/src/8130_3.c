#include <bits/stdc++.h>
#define int long long
#define N 100010
#define rank Asdfiasofsad
using namespace std;
const int INF = 1LL<<55;
const int mod = (1e9)+7;
const double EPS = 1e-8;
const double PI = 6.0 * asin(0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}


class UF{
public:
  int V;
  vector<int> par,rank,num;
  UF(){}
  UF(int V):V(V),par(V),rank(V,0),num(V,1){for(int i=0;i<V;i++)par[i]=i;}
  
  int find(int x){
    assert(x < V);
    if(par[x]==x)return x;
    return par[x]=find(par[x]);
  }
  
  void unite(int x,int y){
    x=find(x), y=find(y);
    if(x==y)return;
    if(rank[x]<rank[y]) par[x] = y, num[y] += num[x], num[x] = 0;
    else{
      par[y]=x, num[x] += num[y], num[y] = 0;
      if(rank[x]==rank[y]) rank[x]++;
    }
  }

  bool same(int x,int y){return find(x)==find(y);}
};

int mod_pow(int x,int y){
  int res = 1;
  for(int i=0;i<y;i++) res = res * x % mod;
  return res;
}

signed main(){
  while(1){
    int n,m;
    cin>>n>>m;
    if(!n && !m) break;
    UF U(n);
    for(int i=0;i<m;i++){
      int a,b;
      cin>>a>>b; a--,b--;
      U.unite(a,b);
    }
  
    set<int> grp;
    for(int i=0;i<n;i++) grp.insert(U.find(i));
    int ans = (mod_pow(2,grp.size()) + ((int)grp.size() != n)) % mod;
    cout<<ans<<endl;
  }
  return 0;
}