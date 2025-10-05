#include <bits/stdc++.h>
using namespace std;
long long mod = 998244353;
long long mod2 = 1e9 + 7;
long long n, m;
vector<int> g[10];
long long maxi;
void per(int d[], int i) {
  if (i == 8) {
    long long count = 0;
    int r[7][7];
    memset(r, 0, sizeof(r));
    for (int j = 1; j <= 7; ++j) {
      for (int x = 0; x < g[j].size(); ++x) {
        int v = g[j][x];
        if (r[d[j]][d[v]] == 0) {
          ++count;
          r[d[j]][d[v]] = 1;
          r[d[v]][d[j]] = 1;
        }
      }
    }
    maxi = max(maxi, count);
    return;
  }
  for (int j = 1; j <= 6; ++j) {
    d[i] = j;
    per(d, i + 1);
  }
}
void solve() {
  cin >> n >> m;
  if (n < 7) {
    cout << m;
    return;
  }
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  maxi = 0;
  int d[8];
  per(d, 1);
  cout << maxi << " ";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t = 1;
  while (t--) {
    solve();
    cout << "\n";
  }
  return 0;
}
