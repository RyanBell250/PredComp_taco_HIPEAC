#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target( \
    "avx,avx2,fma,sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
int MOD = 1e9 + 7;
vector<int> c;
int kol = 0;
int n;
vector<int> num[25];
void dfs(int m) {
  if (m == n - 1) {
    int kl = kol;
    for (int i = n - 1; i > -1; i--) {
      if (c[i] > 1) {
        int kek = 0;
        int num1 = 0;
        for (auto j : num[i]) {
          kek += c[j];
          num1++;
        }
        num1 += c[i] - 1 - kek;
        if (kek <= c[i] - 1) {
          kl -= c[i] - 1 - kek;
        } else {
          return;
        }
        if (num1 < 2) {
          return;
        }
      }
    }
    if (kl == 0) {
      cout << "YES";
      exit(0);
    }
    return;
  }
  for (int i = m + 1; i < n; i++) {
    num[i].push_back(m);
    dfs(m + 1);
    num[i].pop_back();
  }
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0),
      cout << fixed << setprecision(20);
  cin >> n;
  c.resize(n);
  int sm = 0;
  for (int i = 0; i < n; i++) {
    cin >> c[i];
    sm = max(sm, c[i]);
    if (c[i] == 1) kol++;
  }
  if (n - kol > 11 || sm != n) {
    cout << "NO";
    return 0;
  }
  sort(c.begin(), c.end());
  int nw = 0;
  while (nw < n && c[nw] == 1) nw++;
  if (nw == n) {
    cout << "YES";
    return 0;
  }
  dfs(nw);
  cout << "NO";
}
