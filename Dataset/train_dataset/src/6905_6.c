#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007LL;
const long long MAX = 100010LL;
template <class T>
T abs(T x) {
  return x > 0 ? x : -x;
}
template <typename T>
T gcd(T a, T b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
template <typename T>
T power(T x, T y, long long m = MOD) {
  T ans = 1;
  x %= m;
  while (y > 0) {
    if (y & 1LL) ans = (ans * x) % m;
    y >>= 1LL;
    x = (x * x) % m;
  }
  return ans % m;
}
int n;
vector<long long> adj[MAX];
long long x[MAX];
long long res = 0;
unordered_map<long long, long long> ump[MAX];
void dfs(long long u, long long p) {
  ump[u][x[u]]++;
  for (auto g : ump[p]) {
    ump[u][gcd(x[u], g.first)] += ump[p][g.first];
  }
  for (auto g : ump[u]) {
    res += ((g.first % MOD) * (g.second % MOD)) % MOD;
    res %= MOD;
  }
  for (auto it : adj[u]) {
    if (it != p) {
      dfs(it, u);
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i(0); i <= ((n)-1); i++) cin >> x[i + 1];
  for (int i(0); i <= ((n - 1) - 1); i++) {
    long long x, y;
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(1, 0);
  cout << res;
  return 0;
}
