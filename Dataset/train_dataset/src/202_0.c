#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx2")
#pragma GCC optimize("03")
#pragma GCC target("sse4")
using namespace std;
int n;
bool is_scc(vector<int> degrees) {
  int sum = 0;
  for (int i = 0; i < n - 1; i++) {
    sum += degrees[i];
    if (sum == (i * (i + 1)) / 2 + (i + 1) * (n - i - 1)) return 0;
  }
  return 1;
}
string second[(long long)(2e3 + 5)];
int deg[(long long)(2e3 + 5)];
vector<int> prepare() {
  vector<int> res;
  for (int i = 0; i < n; i++) res.push_back(deg[i]);
  sort((res).rbegin(), (res).rend());
  return res;
}
bool is_ok(vector<int> exchange) {
  for (auto y : exchange) {
    for (int i = 0; i < n; i++) {
      if (i == y) continue;
      if (second[i][y] == '0') {
        deg[i]++;
        second[i][y] = '1';
      } else {
        deg[i]--;
        second[i][y] = '0';
      }
    }
    for (int i = 0; i < n; i++) {
      if (i == y) continue;
      if (second[y][i] == '0') {
        deg[y]++;
        second[y][i] = '1';
      } else {
        deg[y]--;
        second[y][i] = '0';
      }
    }
  }
  bool res = is_scc(prepare());
  for (auto y : exchange) {
    for (int i = 0; i < n; i++) {
      if (i == y) continue;
      if (second[i][y] == '0') {
        deg[i]++;
        second[i][y] = '1';
      } else {
        deg[i]--;
        second[i][y] = '0';
      }
    }
    for (int i = 0; i < n; i++) {
      if (i == y) continue;
      if (second[y][i] == '0') {
        deg[y]++;
        second[y][i] = '1';
      } else {
        deg[y]--;
        second[y][i] = '0';
      }
    }
  }
  return res;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> second[i];
    for (int j = 0; j < n; j++)
      if (second[i][j] == '1') deg[i]++;
  }
  if (is_scc(prepare())) {
    cout << "0 1\n";
    return 0;
  }
  if (n <= 6) {
    int r1 = (long long)(1e9), r2 = 0;
    for (int i = 0; i < (1 << n); i++) {
      vector<int> nodes;
      for (int j = 0; j < n; j++)
        if (i & (1 << j)) nodes.push_back(j);
      if (nodes.size() > r1) continue;
      if (is_ok(nodes)) {
        if (nodes.size() < r1) {
          r1 = nodes.size();
          r2 = 1;
        } else
          r2++;
      }
    }
    if (r1 == (long long)(1e9))
      cout << (-1) << '\n';
    else {
      for (int i = 1; i <= r1; i++) r2 *= i;
      cout << r1 << ' ' << r2 << '\n';
    }
    return 0;
  }
  cout << 1 << ' ';
  int cant = 0;
  for (int i = 0; i < n; i++) cant += is_ok({i});
  cout << cant << '\n';
  return 0;
}
