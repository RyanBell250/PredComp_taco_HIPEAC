
#include "bits/stdc++.h"
using namespace std;
#define MOD 1000000007
#define INF (1LL<<60)
#define fs first
#define sc second
#define int long long
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define RFOR(i,a,b) for(int i = (b-1);i>=(a);--i)
#define REP(i,n)  FOR(i,0,(n))
#define RREP(i,n) RFOR(i,0,(n))
#define ITR(itr,mp) for(auto itr = (mp).begin(); itr != (mp).end(); ++itr)
#define RITR(itr,mp) for(auto itr = (mp).rbegin(); itr != (mp).rend(); ++itr)
#define range(i,a,b) ((a)<=(i) && (i)<(b))
#define debug(x)  cout << #x << " = " << (x) << endl;
#define SP << " " << 
#define MSB(x) (63-__builtin_clzll(x))
#define pcnt(x) (__builtin_popcountll(x))
#define parity(i,j) (i&(1LL<<j))
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vector<int>> mat;
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> x(n),y(n);
  REP(i,n) cin >> x[i] >> y[i];
  set<int> st;
  FOR(i,19,301){
    bool flag = true;
    FOR(j,2,i) if(i%j==0) flag = false;
    if(flag) st.insert(i);
  }
  int ans = 0;
  vec a = {2,3,5,7,11,13,17}, b = {0,0,0,0,0,0,0};
  while(1){
    b[0]++; int cnt = 0;
    if(b[0]==9) b[0] = 0, b[1]++, cnt++;
    if(b[1]==6) b[1] = 0, b[2]++, cnt++;
    if(b[2]==4) b[2] = 0, b[3]++, cnt++;
    if(b[3]==3) b[3] = 0, b[4]++, cnt++;
    if(b[4]==3) b[4] = 0, b[5]++, cnt++;
    if(b[5]==3) b[5] = 0, b[6]++, cnt++;
    if(b[6]==3) break;
    map<int,int> mp;
    int cur = 0;
    REP(i,n){
      int z = x[i];
      REP(j,7) REP(k,b[j]) if(z%a[j]==0) z /= a[j];
      if(z==1) cur += y[i];
      else if(st.find(z)!=st.end()) mp[z] += y[i];
    }
    ITR(itr,mp) if(itr->sc > 0) cur += itr->sc;
    ans = max(ans,cur);
  }
  cout << ans << endl;
  return 0;
}