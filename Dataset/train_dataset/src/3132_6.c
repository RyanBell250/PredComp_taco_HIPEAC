#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
#define REP(i,b,n) for(int i=b;i<n;i++)
#define rep(i,n)   REP(i,0,n)
#define ALL(C)     (C).begin(),(C).end()
typedef long long ll;
int dp[100][101];
bool bt(int n,int now,int *inp,int *vol);
set<ll> D[100];
bool distribute(int n,int now,int *inp,int *vol){
  if (vol[now] == 0)return bt(n,now+1,inp,vol);
  ll state = 0;
  REP(i,now,n){
    state=(state<<1);
    if (vol[i] == inp[i])state++;
  }
  if (D[now].find(state) != D[now].end())return false;
  D[now].insert(state);
  if (vol[now] == 0)return false;
  REP(i,now+1,n){
    if (vol[i] != 0)continue;
    if (vol[now]-inp[i] < 0)continue;
    if (i-1 >= now+1 && inp[i-1] == inp[i] && vol[i-1] == 0)continue;
    vol[now]-=inp[i];
    vol[i]=inp[i];
    if (distribute(n,now,inp,vol))return true;
    vol[i]=0;
    vol[now]+=inp[i];
  }
  return false;
}
set<ll> S[100];
bool bt(int n,int now,int *inp,int *vol){
  if (now == n){
    return true;
  }
  ll state = 0;
  REP(i,now,n){
    state=(state<<1);
    if (vol[i] == inp[i])state++;
  }
  if (S[now].find(state) != S[now].end())return false;
  S[now].insert(state);
  if (vol[now] == 0)return false;
  if (bt(n,now+1,inp,vol))return true;
  if (distribute(n,now,inp,vol))return true;
  return false;
}
int main(){
  int n;
  while(cin>>n && n){
    int in[n];
    int vol[n];
    vector<int> a;
    rep(i,n){
      cin>>in[i];vol[i]=0;a.push_back(in[i]);
      S[i].clear();
      D[i].clear();
    }
    sort(in,in+n,greater<int>());
    sort(ALL(a));
    vol[0]=in[0];
    if (bt(n,0,in,vol) == true)puts("YES");
    else puts("NO");
  }
  return false;
}