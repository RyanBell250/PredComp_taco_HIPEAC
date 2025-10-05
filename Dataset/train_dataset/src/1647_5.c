#include <bits/stdc++.h>
using namespace std;
const long long N = 5e6 + 5;
vector<bool> vis(N);
void run_case() {
  long long n, m;
  cin >> n >> m;
  long long tot = 0;
  for (long long b = 1; b <= n; b++) {
    tot += 2 * min(b * b, m);
    for (long long c = b - 1; c >= 0 && b * b - c * c <= m; c--) {
      vis[b - c] ? tot-- : vis[b - c] = true;
      vis[b + c] ? tot-- : vis[b + c] = true;
    }
  }
  cout << tot << '\n';
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long long T = 1;
  while (T--) {
    run_case();
  }
  return 0;
}
