#include <bits/stdc++.h>
using namespace std;
void solve();
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  bool HAST = 0;
  if (HAST) {
    int t;
    cin >> t;
    for (int tt = 0, _tt = (t); tt < _tt; ++tt) {
      solve();
      cout << '\n';
      cout.flush();
    }
  } else {
    solve();
  }
}
vector<int> prime_factors_vi(int n) {
  vector<int> factors;
  if (n % 2 == 0) {
    factors.push_back(2);
    while (n % 2 == 0) n = n / 2;
  }
  for (int i = 3; (i <= sqrt(n)) && (n > 1); i = i + 2) {
    if (n % i == 0) {
      factors.push_back(i);
      while (n % i == 0) n = n / i;
    }
  }
  if (n > 2) factors.push_back(n);
  return factors;
}
void dfs(vector<int> &a_group, vector<vector<int>> &d,
         map<int, vector<int>> &ps, set<int> &up, int node, int group_i) {
  a_group[node] = group_i;
  for (int div : d[node]) {
    if (!((up).find(div) != (up).end())) {
      up.insert(div);
      for (int child : ps[div]) {
        if (a_group[child] == -1) {
          dfs(a_group, d, ps, up, child, group_i);
        }
      }
    }
  }
}
bool one(int group1, int group2, vector<vector<int>> &group_a,
         vector<set<int>> &group_div) {
  for (int ai : group_a[group1]) {
    for (int di : group_div[group2]) {
      if ((ai + 1) % di == 0) return 1;
    }
  }
  return 0;
}
void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0, _i = (n); i < _i; ++i) cin >> a[i];
  vector<vector<int>> d(n);
  map<int, vector<int>> ps;
  for (int i = 0, _i = (n); i < _i; ++i) {
    d[i] = prime_factors_vi(a[i]);
    for (int di : d[i]) {
      ps[di].push_back(i);
    }
  }
  vector<int> a_group(n, -1);
  int group_count = 0;
  set<int> up;
  for (int i = 0, _i = (n); i < _i; ++i) {
    if (a_group[i] == -1) {
      dfs(a_group, d, ps, up, i, group_count);
      group_count++;
    }
  }
  int MAX_DIV = 1e6;
  vector<int> div_group(MAX_DIV, -1);
  for (int i = 0, _i = (n); i < _i; ++i) {
    for (int di : d[i]) {
      div_group[di] = a_group[i];
    }
  }
  vector<set<int>> group_g(group_count);
  for (int i = 0, _i = (n); i < _i; ++i) {
    int a1 = a[i] + 1;
    vector<int> a1_div = prime_factors_vi(a1);
    for (int d1 : a1_div) {
      for (int d2 : a1_div) {
        if (div_group[d1] != -1 && div_group[d2] != -1 &&
            div_group[d1] != div_group[d2]) {
          group_g[div_group[d1]].insert(div_group[d2]);
        }
      }
      for (int d2 : d[i]) {
        if (div_group[d1] != -1 && div_group[d2] != -1 &&
            div_group[d1] != div_group[d2]) {
          group_g[div_group[d1]].insert(div_group[d2]);
        }
      }
    }
  }
  for (int qi = 0, _qi = (q); qi < _qi; ++qi) {
    int a1, a2;
    int g1, g2;
    cin >> a1 >> a2;
    g1 = a_group[a1 - 1];
    g2 = a_group[a2 - 1];
    int sol = 2;
    if (g1 == g2)
      sol = 0;
    else if (((group_g[g2]).find(g1) != (group_g[g2]).end()) ||
             ((group_g[g1]).find(g2) != (group_g[g1]).end()))
      sol = 1;
    cout << sol << '\n';
    cout.flush();
  }
  cout.flush();
}
