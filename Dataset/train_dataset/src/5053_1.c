#include <bits/stdc++.h>
using namespace std;


#define REP(i,n) for(int i=0;i<(int)(n);i++)

int n;
vector<int> g[125252];

bool used[125252];
stack<int> hist;
int po = -1;

bool namo[125252];

void dfs(int p, int bef){
  if(used[p]){
    po = p;
    return;
  }
  used[p] = true;
  hist.push(p);
  for(int to : g[p])if(to != bef){
    dfs(to,p);
    if(po != -1)return;
  }
  hist.pop();
  used[p] = false;
}

int main(){
  scanf("%d",&n);
  REP(i,n){
    int u,v;
    scanf("%d%d",&u,&v);
    u--;v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(0,-1);
  assert(po != -1);
  namo[po] = true;
  while(hist.top() != po){
    namo[hist.top()] = true;
    hist.pop();
  }
  int q;
  scanf("%d",&q);
  while(q--){
    int a,b;
    scanf("%d%d",&a,&b);
    a--;b--;
    if(namo[a] && namo[b]){
      puts("2");
    }else{
      puts("1");
    }
  }
  return 0;
}
