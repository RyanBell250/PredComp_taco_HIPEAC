#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) for(int i=0;i<(n);++i)
#define ALL(obj) (obj).begin(),(obj).end()
#define V vector<int>
#define pb(a) push_back(a)
#define mp make_pair
int main(){
  int n,k;scanf("%d%d",&n,&k);
  V a(n);REP(i,n)scanf("%d",&(a[i]));
  sort(ALL(a),greater<int>());
  vector<bitset<5001>> table(n);
  REP(i,n)table[i].set(i);
  vector<bitset<5001>> dp(k,~bitset<5001>());
  dp[0] = ~dp[0];
  REP(i,n)
    for(int j=k-1;j>=a[i];j--)
      if(!dp[j-a[i]][5000])
        dp[j] &= (dp[j-a[i]] | table[i]);
  int cou = n;
  REP(i,n)FOR(j,max(0,k-a[i]),k)if(!dp[j][i]){cou--;break;}
  printf("%d",cou);
	return 0;
}
