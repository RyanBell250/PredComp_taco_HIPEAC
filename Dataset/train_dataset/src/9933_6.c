#include <bits/stdc++.h>
using namespace std;
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
  cerr << name << " : " << arg1 << "\n";
}
template <typename Arg1, typename... Args>
void __f(const char* na, Arg1&& arg1, Args&&... args) {
  const char* c = strchr(na + 1, ',');
  cerr.write(na, c - na) << " : " << arg1 << " , ";
  __f(c + 1, args...);
}
const int MOD = 1e9 + 7;
const int inf = 1e9;
const double EPS = 1e-9;
const double PI = acos(-1.0);
const long long INF = 1e18;
const int N = 2e5 + 5;
int n, k, a[N];
vector<int> val[N];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) {
    int cur = a[i];
    int op = 0;
    while (cur) {
      val[cur].push_back(op);
      cur /= 2;
      op++;
    }
    val[0].push_back(op);
  }
  for (int i = 0; i <= 2e5; i++) {
    sort(val[i].begin(), val[i].end());
  }
  for (int i = 0; i <= 2e5; i++) {
    for (int j = 0; j < val[i].size(); j++) {
      if (j) val[i][j] += val[i][j - 1];
    }
  }
  int ans = inf;
  for (int i = 0; i <= 2e5; i++) {
    if (val[i].size() < k) continue;
    ans = min(ans, val[i][k - 1]);
  }
  cout << ans << "\n";
  return 0;
}
