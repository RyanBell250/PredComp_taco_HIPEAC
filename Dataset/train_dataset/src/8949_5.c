#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
long long mod = 1000000007;
long long grev[200001];
vector<long long> gr[100005];
long long n;
string s;
long long ans = 0;
long long x;
long long dp[111][55][211][3];
void go(long long pos, long long changes, long long now, long long dir) {
  if (dp[pos][changes][now + 100][dir + 1]) return;
  dp[pos][changes][now + 100][dir + 1] = 1;
  if (pos == x) {
    if (changes == 0) ans = max(ans, abs(now - 0ll));
    return;
  }
  for (long long i = int(0); i < int(changes + 1); i++) {
    int val = (s[pos] == 'F');
    if (i % 2) val ^= 1;
    go(pos + 1, changes - i, now + (val == 1 ? dir : 0),
       dir * (val == 0 ? -1 : 1));
  }
}
void solve() {
  cin >> s >> n;
  x = ((int)s.length());
  go(0, n, 0, 1);
  cout << ans << "\n";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t;
  t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
